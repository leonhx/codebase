import numpy as np


def __theta__(s):
	return 1. / (1. + np.e ** -s)


class LogisticRegression:
	def __init__(self, eta, max_iterations):
		self.eta = eta
		self.max_iterations = max_iterations

	def fit(self, X, y):
		X = np.c_[np.ones(len(X)), X]
		N, dim = X.shape
		self.w = np.zeros((dim,))
		yX = (X.T * -y).T
		for _ in xrange(self.max_iterations):
			dEin = 1. / N * yX.T.dot(__theta__(yX.dot(self.w)))
			if np.all(dEin == 0):
				break
			self.w -= self.eta * dEin

	def predict(self, X):
		def __predict__(x):
			if __theta__(self.w.T.dot(x)) >= 0.5:
				return 1
			else:
				return -1
		X = np.c_[np.ones(len(X)), X]
		return np.apply_along_axis(__predict__, axis=1, arr=X)

	def evaluate(self, X, y):
		return np.sum(self.predict(X) != y) * 1.0 / y.size


class SGDLogisticRegression(LogisticRegression):
	def fit(self, X, y):
		X = np.c_[np.ones(len(X)), X]
		N, dim = X.shape
		self.w = np.zeros((dim,))
		for i in xrange(self.max_iterations):
			n = i % N
			yx = y[n] * X[n]
			dnein = __theta__(self.w.T.dot(-yx)) * yx
			self.w += self.eta * dnein
