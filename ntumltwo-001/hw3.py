import numpy as np

from sklearn.tree import DecisionTreeClassifier
from sklearn.ensemble import BaggingClassifier

from decision_tree import DecisionTree
from bagging import Bagging


def load(filename):
    dataset = np.loadtxt(filename)
    return dataset[:, :-1], dataset[:, -1]


def load_train():
    return load('hw3_train.dat')


def load_test():
    return load('hw3_test.dat')


def q13():
    tree = DecisionTree()
    tree.fit(*load_train())
    print tree.__prepr__()
    print tree.node_count


def _q13():
    X, y = load_train()
    tree = DecisionTreeClassifier(criterion='gini')
    tree.fit(X, y)
    print tree.tree_.node_count


def q14():
    tree = DecisionTree()
    tree.fit(*load_train())
    print tree.ein


def _q14():
    X, y = load_train()
    tree = DecisionTreeClassifier(criterion='gini')
    tree.fit(X, y)
    print 1 - tree.score(X, y)


def q15():
    tree = DecisionTree()
    tree.fit(*load_train())
    print tree.error(*load_test())


def _q15():
    X, y = load_train()
    tree = DecisionTreeClassifier(criterion='gini')
    tree.fit(X, y)
    print 1 - tree.score(*load_test())


def q16():
    def get_decision_tree():
        return DecisionTree()
    T = 300
    X, y = load_train()
    bagging = Bagging(get_decision_tree, T=T)
    bagging.fit(X, y)
    print bagging.ein


def _q16():
    T = 300
    X, y = load_train()
    bagging = BaggingClassifier(DecisionTreeClassifier(), n_estimators=T,
                                n_jobs=-1)
    bagging.fit(X, y)
    print 1 - bagging.score(X, y)


def q17():
    pass


def _q17():
    pass


def q18():
    pass


def _q18():
    pass


def q19():
    pass


def _q19():
    pass


def q20():
    pass


def _q20():
    pass


def run(func):
    print '=' * 3 + func.__name__ + '=' * 3
    func()


if __name__ == '__main__':
    qs = [q13, _q13, q14, _q14, q15, _q15, q16, _q16, q17, _q17, q18, _q18,
          q19, _q19, q20, _q20]
    for q in qs:
        run(q)
