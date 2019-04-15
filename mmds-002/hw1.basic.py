import page_rank


def q1():
    g = page_rank.SparseGraph(nodes=['a', 'b', 'c'])
    g['a'] = ['b', 'c']
    g['b'] = 'c'
    g['c'] = 'c'
    return g.importance(beta=0.7)


def q2():
    g = page_rank.SparseGraph(nodes=['a', 'b', 'c'])
    g['a'] = ['b', 'c']
    g['b'] = 'c'
    g['c'] = 'a'
    return g.importance(beta=0.85)


def q3():
    g = page_rank.SparseGraph(nodes=['a', 'b', 'c'])
    g['a'] = ['b', 'c']
    g['b'] = 'c'
    g['c'] = 'a'
    return g.importance(beta=1.0), g.importance(beta=1.0, max_iter=5)


if __name__ == '__main__':
    s1 = q1()
    s2 = q2()
    s3 = q3()
    print s3
