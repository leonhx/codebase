from cvxopt import matrix, solvers
import numpy as np


def __identity__(x):
    return x


class PrimalSVM(object):

    def __init__(self, transform=None):
        if transform:
            self.t = transform
        else:
            self.t = __identity__


    def fit(self, X, y):
        assert X.shape[0] == y.shape[0]
        X = np.apply_along_axis(self.t, 1, X)
        N, d = X.shape
        P = np.r_[np.zeros((1, d+1)), np.c_[np.zeros((d,)), np.eye(d)]]
        q = np.zeros((d+1,))
        G = -y.repeat(d+1).reshape((N, d+1)) * np.c_[np.ones((N,)), X]
        h = -np.ones((N,))
        self.sol = solvers.qp(matrix(P), matrix(q), matrix(G), matrix(h))
        self.w = np.array(self.sol['x'])

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
    clf = PrimalSVM()
    clf.fit(X, y)
    print clf.w
