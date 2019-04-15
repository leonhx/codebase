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


class LSSVM(object):

    def __init__(self, lamda, kernel=linear()):
        self.kernel = kernel
        self.lamda = lamda


    def fit(self, X, y):
        assert X.shape[0] == y.shape[0]
        N, d = X.shape

        K = np.zeros((N, N))
        for i in xrange(N):
            for j in xrange(N):
                K[i, j] = self.kernel(X[i], X[j])

        self.beta = np.linalg.pinv(K + self.lamda).dot(y)
        self.X = X


    def predict(self, x):
        y = 0
        for i in xrange(len(self.beta)):
            b = self.beta[i]
            if b > 10e-5:
                y += b * self.kernel(self.X[i], x)
        return y


    def score(self, X, y):
        y_ = np.apply_along_axis(lambda x: self.predict(x), axis=1, arr=X)
        return np.sum((y - y_) ** 2)


if __name__ == '__main__':
    X = np.array([[1],
                  [2],
                  [3],
                  [4]])
    y = np.array([2.5, 4.5, 6.5, 8.5])
    clf = LSSVM(lamda=0, kernel=poly(order=1, ksi=0, gamma=1.0))
    clf.fit(X, y)
    for i in range(len(X)):
        print clf.predict(X[i])
