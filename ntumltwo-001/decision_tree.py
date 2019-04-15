import numpy as np


def gini(y):
    uniq_y = np.unique(y)
    return 1.0 - sum([(np.sum(y == k) * 1.0 / len(y)) ** 2 for k in uniq_y])


class DecisionTree(object):

    def __init__(self, impurity=gini, depth=None):
        self.impurity = gini
        self.depth = depth

    def __branching__(self, X, y):
        """return (i, theta, min_impurity_val)"""
        N, d = X.shape
        result = None
        for i in xrange(d):
            Xi = X[:, i]
            x = np.sort(np.unique(X[:, i]))
            thetas = [(xi + xj) / 2.0 for xi, xj in zip(x, x[1:])]
            for theta in thetas:
                c1 = Xi > theta
                c2 = Xi < theta
                impurity_val = np.sum(c1) * self.impurity(y[c1]) + \
                    np.sum(c2) * self.impurity(y[c2])
                if result is None or impurity_val < result[-1]:
                    result = (i, theta, impurity_val)
        return result

    def __make_leaf__(self, y):
        self.is_leaf = True
        self.node_count = 0
        uniq_y = np.unique(y)
        y_counts = [(k, np.sum(y == k)) for k in uniq_y]
        self.y = max(y_counts, key=lambda e: e[1])[0]

    def fit(self, X, y):
        if (self.impurity(y) < 1e-4 or
                (self.depth is not None and self.depth <= 1)):
            return self.__make_leaf__(y)
        self.is_leaf = False
        branch_cond = self.__branching__(X, y)
        if branch_cond is None:
            return self.__make_leaf__(y)
        self.i, self.theta, min_impurity_val = branch_cond
        left_cond = X[:, self.i] < self.theta
        right_cond = X[:, self.i] > self.theta
        new_depth = self.depth - 1 if self.depth is not None else None
        self.left = DecisionTree(self.impurity, new_depth)
        self.left.fit(X[left_cond], y[left_cond])
        self.right = DecisionTree(self.impurity, new_depth)
        self.right.fit(X[right_cond], y[right_cond])
        self.node_count = self.left.node_count + self.right.node_count + 1
        self.ein = np.sum(self.predict(X) != y) * 1.0 / len(y)

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
                  [2, 1], [2, 2], [2, 2],
                  [3, 1], [3, 2], [3, 3]])
    y = np.array([-1, 1, -1, -1, 1, -1, 1, 1, 1])
    dt = DecisionTree()
    dt.fit(X, y)
    print dt.predict(X)
    print dt.node_count
    print dt.__prepr__()
    print dt.ein
