import numpy as np


def q2():
    from svm import primal
    def t(x):
        x1, x2 = x
        return np.array([x2 ** 2 - 2 * x1 + 3, x1 ** 2 - 2 * x2 - 3])
    clf = primal.PrimalSVM(t)
    X = np.array([[1, 0],
                  [0, 1],
                  [0, -1],
                  [-1, 0],
                  [0, 2],
                  [0, -2],
                  [-2, 0]])
    y = np.array([-1, -1, -1, 1, 1, 1, 1])
    clf.fit(X, y)
    print clf.w


def q3():
    from svm import kernel
    clf = kernel.KernelSVM(kernel.poly(2, 1, 1))
    X = np.array([[1, 0],
                  [0, 1],
                  [0, -1],
                  [-1, 0],
                  [0, 2],
                  [0, -2],
                  [-2, 0]])
    y = np.array([-1, -1, -1, 1, 1, 1, 1])
    clf.fit(X, y)
    print clf.alpha
    print sum(clf.alpha)


def q4():
    from svm import kernel
    clf = kernel.KernelSVM(kernel.poly(2, 1, 1))
    X = np.array([[1, 0],
                  [0, 1],
                  [0, -1],
                  [-1, 0],
                  [0, 2],
                  [0, -2],
                  [-2, 0]])
    y = np.array([-1, -1, -1, 1, 1, 1, 1])
    clf.fit(X, y)
    print clf.alpha
    print clf.w
    print clf.b


def load_data(filename, x):
    data = np.loadtxt(filename)
    X = data[:, 1:]
    y = data[:, 0]
    y[y != x] = -1
    y[y >= 0] = 1
    return X, y


def q15():
    X, y = load_data('features.train', 0)
    from sklearn import svm
    clf = svm.LinearSVC(C=0.01, loss='l1', fit_intercept=False)
    clf.fit(X, y)
    print clf.coef_.dot(clf.coef_.T)


def q16():
    from sklearn import svm
    for i in range(1, 10, 2):
        X, y = load_data('features.train', i)
        clf = svm.SVC(C=0.01, kernel='poly', degree=2, gamma=1, coef0=1,
                      shrinking=False)
        clf.fit(X, y)
        ein = 1 - clf.score(X, y)
        print i, ein


def q17():
    from sklearn import svm
    for i in range(0, 10, 2):
        X, y = load_data('features.train', i)
        clf = svm.SVC(C=0.01, kernel='poly', degree=2, gamma=1, coef0=1,
                      shrinking=False)
        clf.fit(X, y)
        alpha = np.sum(np.abs(clf.dual_coef_))
        print i, alpha


def q18():
    from sklearn import svm
    X, y = load_data('features.train', 0)
    X_t, y_t = load_data('features.test', 0)
    for C in [0.001,0.01,0.1,1,10]:
        clf = svm.SVC(C=C, kernel='rbf', gamma=100, shrinking=False)
        clf.fit(X, y)
        nsv = clf.dual_coef_.shape[1]
        eout = 1 - clf.score(X_t, y_t)
        print C, nsv, eout, clf.epsilon


def q19():
    from sklearn import svm
    X, y = load_data('features.train', 0)
    X_t, y_t = load_data('features.test', 0)
    for gamma in [1, 10, 100, 1000, 10000]:
        clf = svm.SVC(C=0.1, kernel='rbf', gamma=gamma, shrinking=False)
        clf.fit(X, y)
        eout = 1 - clf.score(X_t, y_t)
        print gamma, eout


def q20():
    from sklearn import svm
    X, y = load_data('features.train', 0)
    gammas = {1: 0, 10: 0, 100: 0, 1000: 0, 10000: 0}
    for _ in range(100):
        train_size = len(y)
        all_indices = np.linspace(0, train_size - 1, train_size).astype(int)
        indices = np.random.choice(all_indices, 1000, replace=False)
        X_v, y_v = X[indices], y[indices]
        t_indices = np.array(list(set(all_indices).difference(set(indices))))
        X_t, y_t = X[t_indices], y[t_indices]
        best_score = 0
        best_gamma = None
        for gamma in [1, 10, 100, 1000, 10000]:
            clf = svm.SVC(C=0.1, kernel='rbf', gamma=gamma, shrinking=False)
            clf.fit(X_t, y_t)
            score = clf.score(X_v, y_v)
            if score > best_score:
                best_score = score
                best_gamma = gamma
        gammas[best_gamma] += 1
        print gammas[1], gammas[10], gammas[100], gammas[1000], gammas[10000]


if __name__ == '__main__':
    q20()
