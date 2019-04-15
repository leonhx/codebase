import numpy as np


def load(filename):
    dataset = np.loadtxt(filename)
    return dataset[:, :-1], dataset[:, -1]


def load_train():
    return load('hw3_train.dat')


def load_test():
    return load('hw3_test.dat')
