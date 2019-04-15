from cvxopt import matrix, solvers
import numpy as np


def linear():
    return lambda x1, x2: x1.T.dot(x2)


def poly(order, ksi, gamma):
    def kernel(x1, x2):
        return (ksi + gamma * x1.T.dot(x2)) ** order
    return kernel


def rbf(gamma):
    def kernel(x1, x2):
        diff = x1 - x2
        return np.e ** (-gamma * diff.T.dot(diff))
    return kernel


class KernelSVM(object):

    def __init__(self, kernel=linear()):
        self.kernel = kernel


    def fit(self, X, y):
        assert X.shape[0] == y.shape[0]
        N, d = X.shape
        P = np.zeros((N, N))
        for i in xrange(N):
            for j in xrange(N):
                P[i, j] = y[i] * y[j] * self.kernel(X[i], X[j])
        q = -np.ones((N,))
        G = -np.eye(N)
        h = np.zeros((N,))
        A = np.array([y])
        b = np.array([0.0])
        self.sol = solvers.qp(matrix(P), matrix(q), matrix(G),
                              matrix(h), matrix(A, tc='d'), matrix(b))
        self.alpha = np.array(self.sol['x'])
        w = np.zeros((d,))
        sv_i = None
        for i in xrange(len(self.alpha)):
            a = self.alpha[i]
            if a > 10e-5:
                sv_i = i
                w += a * y[i] * X[i]
        self.b = y[sv_i]
        for i in xrange(len(self.alpha)):
            a = self.alpha[i]
            if a > 10e-5:
                self.b -= self.alpha[i] * y[i] * self.kernel(X[i], X[sv_i])
        # self.w = np.r_[self.b, w]
        self.X = X
        self.y = y


    def predict(self, x):
        y = self.b
        for i in xrange(len(self.alpha)):
            a = self.alpha[i]
            if a > 10e-5:
                y += a * self.y[i] * self.kernel(X[i], x)
        if y >= 0:
            return 1
        else:
            return -1


if __name__ == '__main__':
    X = np.array([[0, 0],
                  [2, 2],
                  [2, 0],
                  [3, 0]])
    y = np.array([-1, -1, 1, 1])
    clf = KernelSVM()
    clf.fit(X, y)
    print clf.alpha
    print clf.w
