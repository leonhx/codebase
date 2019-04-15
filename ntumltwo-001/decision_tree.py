import numpy as np


def gini(y):
    if len(y) == 0:
        return 0.0
    uniq_y = np.unique(y)
    most_k_count = max([np.sum(y == k) for k in uniq_y])
    return 1.0 - 1.0 * most_k_count / len(y)


class DecisionTree(object):

    def __init__(self, impurity=gini, pruning=False):
        self.impurity = gini
        self.pruning = pruning

    def __branching__(self, X, y):
        """return (i, theta)"""
        N, d = X.shape
        best_i = 0
        best_theta = 0.0
        min_impurity_val = N + 1
        for i in xrange(d):
            Xi = X[:, i]
            x = np.sort(np.unique(X[:, i]))
            thetas = [(xi + xj) / 2.0 for xi, xj in zip(x, x[1:])]
            for theta in thetas:
                c1 = Xi > theta
                c2 = Xi < theta
                impurity_val = np.sum(c1) * self.impurity(y[c1]) + \
                    np.sum(c2) * self.impurity(y[c2])
                if impurity_val < min_impurity_val:
                    best_i = i
                    best_theta = theta
                    min_impurity_val = impurity_val
        return (best_i, best_theta)

    def fit(self, X, y):
        if self.impurity(y) < 1e-5:
            self.is_leaf = True
            uniq_y = np.unique(y)
            y_counts = [(k, np.sum(y == k)) for k in uniq_y]
            self.y = max(y_counts, key=lambda e: e[1])[0]
            return
        self.is_leaf = False
        self.i, self.theta = self.__branching__(X, y)
        left_cond = X[:, self.i] < self.theta
        right_cond = X[:, self.i] > self.theta
        self.left = DecisionTree(self.impurity, self.pruning)
        self.left.fit(X[left_cond], y[left_cond])
        self.right = DecisionTree(self.impurity, self.pruning)
        self.right.fit(X[right_cond], y[right_cond])

    def __predict__(self, x):
        if self.is_leaf:
            return self.y
        if x[self.i] < self.theta:
            return self.left.__predict__(x)
        elif x[self.i] > self.theta:
            return self.right.__predict__(x)
        raise UserWarning('no such condition')

    def __prepr__(self, indent=0):
        class_name = self.__class__.__name__
        if self.is_leaf:
            return ' ' * indent + '{}(y={})'.format(class_name, self.y)
        else:
            left = self.left.__prepr__(indent + 2)
            right = self.right.__prepr__(indent + 2)
            return ' ' * indent + '{}(i={}, theta={})'.format(
                class_name, self.i, self.theta) + '\n' + left + '\n' + right

    def __repr__(self):
        if self.is_leaf:
            return '{}(y={})'.format(self.__class__.__name__, self.y)
        return '{}(i={}, theta={}, left={}, right={})'.format(
            self.__class__.__name__, self.i, self.theta, self.left, self.right)

    def predict(self, X):
        return np.apply_along_axis(lambda x: self.__predict__(x),
                                   axis=1, arr=X)


if __name__ == '__main__':
    X = np.array([[1, 1], [1, 2], [1, 3],
                  [2, 1], [2, 2], [2, 3],
                  [3, 1], [3, 2], [3, 3]])
    y = np.array([1, 1, 1, 1, 1, 1, 1, 1, -1])
    dt = DecisionTree()
    dt.fit(X, y)
    print dt.predict(X)
    print dt.__prepr__()
