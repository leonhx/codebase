import numpy as np
import ridge
from common import sign
from dataset import load_train, load_test

def test():
	X_train, y_train = load_train()
	X_test, y_test = load_test()
	lamda = 0
	reg = ridge.RidgeRegression(lamda)
	reg.fit(X_train, y_train)
	e_in = reg.evaluate(X_train, y_train, sign)
	e_out = reg.evaluate(X_test, y_test, sign)
	print "E_in: %.3f, E_out: %.3f" % (e_in, e_out)

def q13():
	X_train, y_train = load_train()
	X_test, y_test = load_test()
	lamda = 10
	reg = ridge.RidgeRegression(lamda)
	reg.fit(X_train, y_train)
	e_in = reg.evaluate(X_train, y_train, sign)
	e_out = reg.evaluate(X_test, y_test, sign)
	print "E_in: %.3f, E_out: %.3f" % (e_in, e_out)


def q14():
	X_train, y_train = load_train()
	X_test, y_test = load_test()
	lamdas = np.logspace(-10, 2, 13)
	best = (1.0, None)
	for lamda in lamdas:
		reg = ridge.RidgeRegression(lamda)
		reg.fit(X_train, y_train)
		e_in = reg.evaluate(X_train, y_train, sign)
		if e_in <= best[0]:
			best = (e_in, reg)
	best_reg = best[1]
	print "lamda: %e, E_in: %.3f, E_out: %.3f" % (
		best_reg.lamda,
		best_reg.evaluate(X_train, y_train, sign),
		best_reg.evaluate(X_test, y_test, sign))


def q15():
	X_train, y_train = load_train()
	X_test, y_test = load_test()
	lamdas = np.logspace(-10, 2, 13)
	best = (1.0, None)
	for lamda in lamdas:
		reg = ridge.RidgeRegression(lamda)
		reg.fit(X_train, y_train)
		e_out = reg.evaluate(X_test, y_test, sign)
		if e_out <= best[0]:
			best = (e_out, reg)
	best_reg = best[1]
	print "lamda: %e, E_in: %.3f, E_out: %.3f" % (
		best_reg.lamda,
		best_reg.evaluate(X_train, y_train, sign),
		best_reg.evaluate(X_test, y_test, sign))


def q16():
	X, y = load_train()
	X_train, X_val = X[:120], X[120:]
	y_train, y_val = y[:120], y[120:]
	X_test, y_test = load_test()
	lamdas = np.logspace(-10, 2, 13)
	best = (1.0, None)
	for lamda in lamdas:
		reg = ridge.RidgeRegression(lamda)
		reg.fit(X_train, y_train)
		e_train = reg.evaluate(X_train, y_train, sign)
		if e_train <= best[0]:
			best = (e_train, reg)
	best_reg = best[1]
	print "lamda: %e, E_train: %.3f, E_val: %.3f, E_out: %.3f" % (
		best_reg.lamda,
		best_reg.evaluate(X_train, y_train, sign),
		best_reg.evaluate(X_val, y_val, sign),
		best_reg.evaluate(X_test, y_test, sign))


def q17():
	X, y = load_train()
	X_train, X_val = X[:120], X[120:]
	y_train, y_val = y[:120], y[120:]
	X_test, y_test = load_test()
	lamdas = np.logspace(-10, 2, 13)
	best = (1.0, None)
	for lamda in lamdas:
		reg = ridge.RidgeRegression(lamda)
		reg.fit(X_train, y_train)
		e_val = reg.evaluate(X_val, y_val, sign)
		if e_val <= best[0]:
			best = (e_val, reg)
	best_reg = best[1]
	print "lamda: %e, E_train: %.3f, E_val: %.3f, E_out: %.3f" % (
		best_reg.lamda,
		best_reg.evaluate(X_train, y_train, sign),
		best_reg.evaluate(X_val, y_val, sign),
		best_reg.evaluate(X_test, y_test, sign))


def q18():
	X, y = load_train()
	X_train, X_val = X[:120], X[120:]
	y_train, y_val = y[:120], y[120:]
	X_test, y_test = load_test()
	lamdas = np.logspace(-10, 2, 13)
	best = (1.0, None)
	for lamda in lamdas:
		reg = ridge.RidgeRegression(lamda)
		reg.fit(X_train, y_train)
		e_val = reg.evaluate(X_val, y_val, sign)
		if e_val <= best[0]:
			best = (e_val, reg)
	best_reg = best[1]
	best_reg.fit(X, y)
	print "lamda: %e, E_in: %.3f, E_out: %.3f" % (
		best_reg.lamda,
		best_reg.evaluate(X, y, sign),
		best_reg.evaluate(X_test, y_test, sign))


def q19():
	def cross_validate(X, y, lamda):
		Xs = X[:40], X[40:80], X[80:120], X[120:160], X[160:]
		ys = y[:40], y[40:80], y[80:120], y[120:160], y[160:]
		reg = ridge.RidgeRegression(lamda)
		e_cv = 0.0
		for i in range(5):
			X_val, y_val = Xs[i], ys[i]
			X_train = np.concatenate([Xs[j] for j in range(5) if i != j])
			y_train = np.concatenate([ys[j] for j in range(5) if i != j])
			reg.fit(X_train, y_train)
			e_cv += reg.evaluate(X_val, y_val, sign)
		return e_cv / 5
	X_train, y_train = load_train()
	X_test, y_test = load_test()
	lamdas = np.logspace(-10, 2, 13)
	best = (1.0, None)
	for lamda in lamdas:
		e_cv = cross_validate(X_train, y_train, lamda)
		if e_cv <= best[0]:
			best = (e_cv, lamda)
	print "lamda: %e, E_cv: %.3f" % (best[1], best[0])


def q20():
	def cross_validate(X, y, lamda):
		Xs = X[:40], X[40:80], X[80:120], X[120:160], X[160:]
		ys = y[:40], y[40:80], y[80:120], y[120:160], y[160:]
		reg = ridge.RidgeRegression(lamda)
		e_cv = 0.0
		for i in range(5):
			X_val, y_val = Xs[i], ys[i]
			X_train = np.concatenate([Xs[j] for j in range(5) if i != j])
			y_train = np.concatenate([ys[j] for j in range(5) if i != j])
			reg.fit(X_train, y_train)
			e_cv += reg.evaluate(X_val, y_val, sign)
		return e_cv / 5
	X_train, y_train = load_train()
	X_test, y_test = load_test()
	lamdas = np.logspace(-10, 2, 13)
	best = (1.0, None)
	for lamda in lamdas:
		e_cv = cross_validate(X_train, y_train, lamda)
		if e_cv <= best[0]:
			best = (e_cv, lamda)
	best_reg = ridge.RidgeRegression(best[1])
	best_reg.fit(X_train, y_train)
	print "lamda: %e, E_in: %.3f, E_out: %.3f" % (best[1],
		best_reg.evaluate(X_train, y_train, sign),
		best_reg.evaluate(X_test, y_test, sign))


if __name__ == '__main__':
	test()
	q13()
	q14()
	q15()
	q16()
	q17()
	q18()
	q19()
	q20()
