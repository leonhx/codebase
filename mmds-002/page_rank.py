import numpy as np
import collections


class SparseGraph(dict):

    def __init__(self, N=None, nodes=None):
        if N is None and nodes is None:
            raise AttributeError('either N or nodes should be not None')
        if N is None:
            self.nodes = set(nodes)
            self.N = len(self.nodes)
        else:
            self.N = N
            self.nodes = set(range(N))

    def __repr__(self):
        return '{}({})'.format(self.__class__.__name__,
                               super(SparseGraph, self).__repr__())

    def __setitem__(self, n1, n2):
        if n1 not in self.nodes:
            raise AttributeError('%r not in nodes list' % n1)
        if n1 not in self:
            super(SparseGraph, self).__setitem__(n1, set())
        if not isinstance(n2, collections.Iterable):
            n2 = [n2]
        for n in n2:
            if n not in self.nodes:
                raise AttributeError('%r not in nodes list' % n)
            super(SparseGraph, self).__getitem__(n1).add(n)

    def sort(self, beta):
        pass


if __name__ == '__main__':
    g = SparseGraph(nodes={1, 2, 3, 4, 5})
