import numpy as np

from decision_stump import DecisionStump


def gini(y):
    uniq_y = np.unique(y)
    most_k_count = 0
    for k in uniq_y:
        k_count =


class DecisionTree(object):

    def __init__(self, impurity=gini, pruning=False):
        pass
