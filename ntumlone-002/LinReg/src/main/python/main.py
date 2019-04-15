import linreg
import logreg
from data import load_dataset
from common import sign
import numpy as np


def f(row):
	x1, x2 = row
	return sign(x1**2 + x2**2 - 0.6)


def q13(never_used_param):
	n_params = 2
	N = 1000
	X, y = load_dataset(N, f, n_params, noise_level=0.1)
	lr = linreg.LinearRegression()
	lr.fit(X, y)
	err = np.sum(np.vectorize(sign)(lr.predict(X)) != y)
	err_rate = err * 1.0 / N
	return err_rate


def transform(X):
	return np.c_[X, X[:, 0] * X[:, 1], X[:, 0] ** 2, X[:, 1] ** 2]


def q14(never_used_param):
	n_params = 2
	N = 1000
	X, y = load_dataset(N, f, n_params, noise_level=0.1)
	lr = linreg.LinearRegression()
	lr.fit(transform(X), y)
	return lr.w


def q15(never_used_param):
	n_params = 2
	N = 1000
	X_train, y_train = load_dataset(N, f, n_params, noise_level=0.1)
	lr = linreg.LinearRegression()
	lr.fit(transform(X_train), y_train)
	X_test, y_test = load_dataset(N, f, n_params, noise_level=0.1)
	err = np.sum(np.vectorize(sign)(lr.predict(transform(X_test))) != y_test)
	err_rate = err * 1.0 / N
	return err_rate


def load_resources(filename):
	assert filename.startswith('/')
	data = np.loadtxt('../resources%s' % filename)
	return data[:, :-1], data[:, -1].astype(np.int)


def load_train_data():
	return load_resources('/hw3_train.dat')


def load_test_data():
	return load_resources('/hw3_test.dat')


def q18():
	X_train, y_train = load_train_data()
	lr = logreg.LogisticRegression(0.001, 2000)
	lr.fit(X_train, y_train)
	X_test, y_test = load_test_data()
	return lr.evaluate(X_test, y_test)


def q19():
	X_train, y_train = load_train_data()
	lr = logreg.LogisticRegression(0.01, 2000)
	lr.fit(X_train, y_train)
	X_test, y_test = load_test_data()
	return lr.evaluate(X_test, y_test)


def q20():
	X_train, y_train = load_train_data()
	lr = logreg.SGDLogisticRegression(0.001, 2000)
	lr.fit(X_train, y_train)
	X_test, y_test = load_test_data()
	return lr.evaluate(X_test, y_test)


if __name__ == '__main__':
	# print np.average(np.vectorize(q13)(np.arange(100)))
	# print np.average(np.array([q14(_) for _ in np.arange(200)]), axis=0)
	# print np.average(np.vectorize(q15)(np.arange(10)))
	# print q18()
	# print q19()
	print q20()
