import numpy as np
from random import randint


class Bagging(object):

    def __init__(self, get_model, sample_size=1.0, T=10):
        self.get_model = get_model
        self.sample_size = sample_size
        self.T = T

    def __fit_one__(self, X, y):
        model = self.get_model()
        indices = [randint(0, len(X) - 1)
                   for _ in xrange(int(self.sample_size * len(X)))]
        model.fit(X[indices], y[indices])
        return model

    def fit(self, X, y):
        self.models = [self.__fit_one__(X, y) for _ in xrange(self.T)]
        self.ein = sum([m.ein for m in self.models]) / self.T

    def __predict__(self, x):
        results = [m.__predict__(x) for m in self.models]
        r_counts = [(r, np.sum(results == r)) for r in np.unique(results)]
        return max(r_counts, key=lambda e: e[1])[0]

    def predict(self, X):
        return np.apply_along_axis(lambda x: self.__predict__(x),
                                   axis=1, arr=X)

    def score(self, X, y):
        return np.sum(self.predict(X) == y) * 1.0 / len(y)


def get_dt():
    return DecisionTree()


if __name__ == '__main__':
    from decision_tree import DecisionTree
    X = np.array([[1, 1], [1, 2], [1, 3],
                  [2, 1], [2, 2], [2, 2],
                  [3, 1], [3, 2], [3, 3]])
    y = np.array([-1, 1, -1, -1, 1, -1, 1, 1, 1])
    bagging = Bagging(get_dt, T=10)
    bagging.fit(X, y)
    print bagging.ein
