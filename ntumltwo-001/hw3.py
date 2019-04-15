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


def q16_bag(param):
    def get_decision_tree():
        return DecisionTree()
    X, y = param
    bagging = Bagging(get_decision_tree, T=300)
    bagging.fit(X, y)
    return bagging


def q16_print_ein(param):
    bagging = q16_bag(param)
    eins = [1 - m.score(*param) for m in bagging.models]
    ein_g = sum(eins) * 1.0 / len(eins)
    ein_G = 1 - bagging.score(*param)
    eout_G = 1 - bagging.score(*load_test())
    print '-' * 6
    print 'q16:', ein_g
    print 'q17:', ein_G
    print 'q18:', eout_G
    return (ein_g, ein_G, eout_G)


def q16():
    X, y = load_train()
    import multiprocessing as par
    pool = par.Pool(processes=par.cpu_count())
    R = 3
    res = pool.map(q16_print_ein, [(X, y)] * R)
    print '-' * 6
    print '- q16:', sum([e[0] for e in res]) * 1.0 / len(res)
    print '- q17:', sum([e[1] for e in res]) * 1.0 / len(res)
    print '- q18:', sum([e[2] for e in res]) * 1.0 / len(res)


def q19_bag(param):
    def get_decision_tree():
        return DecisionTree(depth=1)
    X, y = param
    bagging = Bagging(get_decision_tree, T=300)
    bagging.fit(X, y)
    return bagging


def q19_print_ein(param):
    bagging = q19_bag(param)
    ein_G = 1 - bagging.score(*param)
    eout_G = 1 - bagging.score(*load_test())
    print '-' * 6
    print 'q19:', ein_G
    print 'q20:', eout_G
    return (ein_G, eout_G)


def q19():
    X, y = load_train()
    import multiprocessing as par
    pool = par.Pool(processes=par.cpu_count())
    R = 3
    res = pool.map(q19_print_ein, [(X, y)] * R)
    print '-' * 6
    print '- q19:', sum([e[0] for e in res]) * 1.0 / len(res)
    print '- q20:', sum([e[1] for e in res]) * 1.0 / len(res)


def run(func):
    print '=' * 3 + func.__name__ + '=' * 3
    func()


if __name__ == '__main__':
    qs = [q16, q19]
    for q in qs:
        run(q)
