import numpy as np


def __load_resources__(filename):
	assert filename.startswith('/')
	data = np.loadtxt('../resources%s' % filename)
	return data[:, :-1], data[:, -1].astype(np.int)


def load_train():
	return __load_resources__('/hw4_train.dat')


def load_test():
	return __load_resources__('/hw4_test.dat')
