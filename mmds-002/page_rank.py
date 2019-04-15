import numpy as np
import collections
import itertools


def __close_enough__(v1, v2, tolerance):
    return abs(np.linalg.norm(v1 - v2)) < tolerance


class SparseGraph(dict):

    def __init__(self, N=None, nodes=None):
        super(SparseGraph, self).__init__()
        if N is None and nodes is None:
            raise AttributeError('either N or nodes should be not None')
        if N is None:
            self.nodes_ = list(set(nodes))
            self.N_ = len(self.nodes_)
        else:
            self.N_ = N
            self.nodes_ = list(range(N))

    def __repr__(self):
        return '{}({})'.format(self.__class__.__name__,
                               super(SparseGraph, self).__repr__())

    def __setitem__(self, n1, n2):
        if n1 not in self.nodes_:
            raise AttributeError('%r not in nodes list' % n1)
        if not super(SparseGraph, self).__contains__(n1):
            super(SparseGraph, self).__setitem__(n1, set())
        if not isinstance(n2, collections.Iterable):
            n2 = [n2]
        for n in n2:
            if n not in self.nodes_:
                raise AttributeError('%r not in nodes list' % n)
            super(SparseGraph, self).__getitem__(n1).add(n)

    @property
    def M(self):
        m = np.zeros((self.N_, self.N_), dtype=np.float)
        for i in xrange(self.N_):
            n_i = self.nodes_[i]
            if super(SparseGraph, self).__contains__(n_i):
                n_i_out = super(SparseGraph, self).__getitem__(n_i)
                w = 1. / len(n_i_out)
                for n_j in n_i_out:
                    j = self.nodes_.index(n_j)
                    m[j, i] = w
        return m

    def importance(self, beta=0.8, max_iter=None, tolerance=1e-4):
        A = beta * self.M + (1. - beta) / self.N_
        r = np.ones((self.N_,), dtype=np.float) / self.N_
        for i in itertools.count(start=0, step=1):
            if max_iter is not None and max_iter <= i:
                break
            r_ = A.dot(r)
            if __close_enough__(r, r_, tolerance):
                r = r_
                break
            r = r_
        return dict(zip(self.nodes_, r))

    def sort(self, beta=0.8, max_iter=None, tolerance=1e-4,
             with_importance=True):
        z = self.importance(beta, max_iter, tolerance).items()
        z.sort(key=lambda e: e[1])
        if with_importance:
            return z
        else:
            return [e[0] for e in z]


if __name__ == '__main__':
    g = SparseGraph(nodes=['a', 'm', 'y'])
    g['a'] = 'y'
    g['a'] = 'm'
    g['y'] = 'y'
    g['y'] = 'a'
    g['m'] = 'm'
    print g
    print g.M
    print g.sort()
