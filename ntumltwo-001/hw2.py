import numpy as np
from svm.lssvm import LSSVM, rbf
from ada_boost import AdaBoost
from decision_stump import DecisionStump
from common import *
from sklearn.ensemble import AdaBoostClassifier
from sklearn.tree import DecisionTreeClassifier


def load_dataset():
    dataset = np.loadtxt('/Users/leon/Developer/codebase/ntumltwo-001/hw2_lssvm_all.dat')
    Nt = 400
    D_train = dataset[:Nt]
    D_test = dataset[Nt:]
    return D_train[:, :-1], D_train[:, -1], D_test[:, :-1], D_test[:, -1]


def load(filename):
    dataset = np.loadtxt(filename)
    return dataset[:, :-1], dataset[:, -1]


def load_ada_boost_train():
    return load('hw2_adaboost_train.dat')


def load_ada_boost_test():
    return load('hw2_adaboost_test.dat')


def q12():
    clf = DecisionStump()
    X, y = load_ada_boost_train()
    clf.fit(X, y)
    print 'Ein:', clf.score(X, y)
    X, y = load_ada_boost_test()
    print 'Eout:', clf.score(X, y)


def q13():
    T = 300
    clf = AdaBoost(T, lambda u: DecisionStump(u), lambda dd: dd.err_)
    X, y = load_ada_boost_train()
    clf.fit(X, y)
    print clf.e
    print 'Ein:', clf.score(X, y)
    print '%f <= U_T <= %f' % (np.min(clf.U), np.max(clf.U))
    print 'e_t >= %f' % np.min(clf.e)
    X, y = load_ada_boost_test()
    print 'Eout:', clf.score(X, y)
    print 'U(2):', clf.U[1]


def q14():
    T = 1
    clf = AdaBoost(T, lambda u: DecisionStump(u), lambda dd: dd.err_)
    X, y = load_ada_boost_train()
    clf.fit(X, y)
    print clf.u
    print np.sum(clf.u)
    print 'AND SEE q13'


def q15():
    print 'SEE q13'


def q16():
    print 'SEE q13'


def q17():
    print 'SEE q12'


def q18():
    print 'SEE q13'


def q19():
    X_train, y_train, X_test, y_test = load_dataset()
    for gamma in [32, 2, 0.125]:
        for lamda in [0.001, 1, 1000]:
            clf = LSSVM(lamda, rbf(gamma))
            # from sklearn import svm
            # clf = svm.SVR(kernel='rbf', gamma=gamma, C=1./lamda, epsilon=0,
            #               shrinking=False)
            clf.fit(X_train, y_train)
            err = 0.0
            for i in xrange(len(X_train)):
                if sign(clf.predict(X_train[i])) != y_train[i]:
                    err += 1.0
            print gamma, lamda, err / len(X_train)


def q20():
    X_train, y_train, X_test, y_test = load_dataset()
    for gamma in [32, 2, 0.125]:
        for lamda in [0.001, 1, 1000]:
            clf = LSSVM(lamda, rbf(gamma))
            # from sklearn import svm
            # clf = svm.SVR(kernel='rbf', gamma=gamma, C=1./lamda, epsilon=0,
            #               shrinking=False)
            clf.fit(X_train, y_train)
            err = 0.0
            for i in xrange(len(X_test)):
                if sign(clf.predict(X_test[i])) != y_test[i]:
                    err += 1.0
            print gamma, lamda, err / len(X_test)


if __name__ == '__main__':
    # print '===q12==='
    # q12()
    # print '===q13==='
    # q13()
    # print '===q14==='
    # q14()
    # print '===q15==='
    # q15()
    # print '===q16==='
    # q16()
    # print '===q17==='
    # q17()
    # print '===q18==='
    # q18()
    print '===q19==='
    q19()
    print '===q20==='
    q20()

