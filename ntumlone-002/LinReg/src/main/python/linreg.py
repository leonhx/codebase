import numpy as np


class LinearRegression:
	def fit(self, X, y):
		X = np.c_[np.ones(len(X)), X]
		self.w = np.linalg.lstsq(X, y)[0]

	def predict(self, X):
		def __predict__(x):
			return self.w.T.dot(x)
		X = np.c_[np.ones(len(X)), X]
		return np.apply_along_axis(__predict__, axis=1, arr=X)
