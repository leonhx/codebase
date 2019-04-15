from cvxopt import matrix, solvers
import numpy as np


def __identity__(x):
    return x


class DualSVM(object):

    def __init__(self, transform=None):
        if transform:
            self.t = transform
        else:
            self.t = __identity__


    def fit(self, X, y):
        assert X.shape[0] == y.shape[0]
        X = np.apply_along_axis(self.t, 1, X)
        N, d = X.shape
        P = np.zeros((N, N))
        for i in xrange(N):
            for j in xrange(N):
                P[i, j] = y[i]*y[j]*X[i].T.dot(X[j])
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
        b = y[sv_i] - w.T.dot(X[sv_i])
        self.w = np.r_[b, w]


    def predict(self, x):
        y = self.w.dot(self.t(x))
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
    clf = DualSVM()
    clf.fit(X, y)
    print clf.alpha
    print clf.w
