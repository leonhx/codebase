import numpy as np


def load_dataset(size, f, n_params, noise_level=0.1):
	X = np.random.sample((size, n_params)) * 2 - 1
	y = np.apply_along_axis(f, axis=1, arr=X)
	indices = list(np.arange(size))
	np.random.shuffle(indices)
	indices = indices[:int(round(size*noise_level))]
	y[indices] = - y[indices]
	return X, y
