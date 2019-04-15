import numpy as np


class RidgeRegression:
	def __init__(self, lamda):
		self.lamda = lamda

	def fit(self, X, y):
		X = np.c_[np.ones(len(X)), X]
		zTz = X.T.dot(X)
		reg_zTz = zTz + self.lamda * np.eye(zTz.shape[0])
		self.w = np.linalg.pinv(reg_zTz).dot(X.T).dot(y)

	def predict(self, X, p=None):
		if p is None:
			p = lambda x: x
		def __predict__(x):
			return p(self.w.T.dot(x))
		X = np.c_[np.ones(len(X)), X]
		return np.apply_along_axis(__predict__, axis=1, arr=X)

	def evaluate(self, X, y, p=None):
		return np.sum(self.predict(X, p) != y) * 1.0 / y.size
