import numpy as np
import multiprocessing as par


def fit_one(param):
    bag, X, y = param
    return bag.__fit_one__(X, y)


class Bagging(object):

    def __init__(self, get_model, size, T):
        self.get_model = get_model
        self.size = size
        self.T = T

    def __fit_one__(self, X, y):
        model = self.get_model()
        indices = np.random.random_integers(0, len(X) - 1, self.size)
        model.fit(X[indices], y[indices])
        return model

    def fit(self, X, y):
        pool = par.Pool(processes=par.cpu_count())
        self.models = pool.map(fit_one, ((self, X, y),) * self.T)

    def __predict__(self, x):
        results = [m.__predict__(x) for m in self.models]
        r_counts = [(r, np.sum(results == r)) for r in np.unique(results)]
        return max(r_counts, key=lambda e: e[1])[0]

    def predict(self, X):
        return np.apply_along_axis(lambda x: self.__predict__(x),
                                   axis=1, arr=X)
