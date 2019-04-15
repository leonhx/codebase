import numpy as np
from common import *


class AdaBoost(object):

    def __init__(self, T, get_hypo, hypo_err):
        self.T = T
        self.hypo = get_hypo
        self.err = hypo_err


    def fit(self, X, y):
        N, d = X.shape
        self.u = np.zeros((N,)) + 1.0 / N
        self.alpha = []
        self.g = []
        self.U = []
        self.e = []
        self.E = []
        for t in xrange(self.T):
            self.U.append(np.sum(self.u))
            # obtain g
            g = self.hypo(self.u.copy())
            g.fit(X, y)
            e = self.err(g)
            self.e.append(e)
            self.g.append(g)
            # check if get the best g
            if abs(e) < 1e-5:
                e = 1e-5
            dt = np.sqrt((1.0 - e) / e)
            # update u
            for i in range(N):
                if g.predict(X[i]) != y[i]:
                    self.u[i] = self.u[i] * dt
                else:
                    self.u[i] = self.u[i] / dt
            # compute alpha
            self.alpha.append(np.log(dt))
            self.E.append(self.score(X, y))


    def predict(self, x):
        return sign(np.sum([a * g.predict(x)
                            for a, g in zip(self.alpha, self.g)]))


    def score(self, X, y):
        y_ = np.apply_along_axis(lambda x: self.predict(x), axis=1, arr=X)
        return np.sum(y != y_) * 1.0 / len(y)


if __name__ == '__main__':
    X = np.array([[ 1. ,  2.1],
                  [ 2. ,  1.1],
                  [ 1.3,  1. ],
                  [ 1. ,  1. ],
                  [ 2. ,  1. ]])
    y = np.array([1.0, 1.0, -1.0, -1.0, 1.0])
    T = 5
    from decision_stump import DecisionStump
    clf = AdaBoost(T, lambda u: DecisionStump(u), lambda dd: dd.err_)
    clf.fit(X, y)
    print clf.score(X, y)
    print clf.E
    for a, g in zip(clf.alpha, clf.g):
        print a, g
    for i in range(len(X)):
        print clf.predict(X[i])
