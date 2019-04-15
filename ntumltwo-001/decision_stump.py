import numpy as np
from common import *


def err(s, theta, x, y, u):
    e = 0
    for i in range(len(x)):
        if s * sign(x[i] - theta) != sign(y[i]):
            e += u[i]
    return e * 1.0 / np.sum(u)


class DecisionStump(object):

    def __init__(self, u=None):
        self.u = u
        self.s = None
        self.i = None
        self.theta = None
        self.err_ = None

    def __repr__(self):
        return 'DecisionDump(u=%s, s=%s, i=%s, theta=%s, err_=%s)' % (
            self.u, self.s, self.i, self.theta, self.err_)

    def fit(self, X, y):
        N, d = X.shape
        if self.u is None:
            self.u = np.ones(N)
        self.i = 0
        self.s = 1
        self.theta = 0
        self.err_ = 1.0
        for i in xrange(d):
            xi = X[:, i].copy()
            indices = np.argsort(xi)
            nx = xi[indices]
            ny = y[indices]
            nu = self.u[indices]
            thetas = np.zeros_like(nx, dtype=np.float)
            thetas[0] = nx[0] - 1
            for j in range(1, len(nx)):
                if nx[j] != nx[j-1]:
                    thetas[j] = (nx[j] + nx[j-1]) / 2.0
            ss = [1, -1]
            for theta in thetas:
                for s in ss:
                    e = err(s, theta, nx, ny, nu)
                    if e < self.err_:
                        self.err_ = e
                        self.i = i
                        self.s = s
                        self.theta = theta

    def predict(self, x):
        return self.s * sign(x[self.i] - self.theta)

    def score(self, X, y):
        x = X[:, self.i]
        e = 0.0
        for i in range(len(x)):
            if self.s * sign(x[i] - self.theta) != sign(y[i]):
                e += 1.0
        return e * 1.0 / len(x)


if __name__ == '__main__':
    X = np.array([[1, 2, 3],
                  [2, 1, 1],
                  [3, 1, 3],
                  [4, 3, 2]])
    y = np.array([1, 1, -1, 1])
    clf = DecisionStump([1, 1, 1, 1])
    clf.fit(X, y)
    print clf.i, clf.s, clf.theta, clf.err_, clf.score(X, y)
    for i in range(len(X)):
        print clf.predict(X[i])
