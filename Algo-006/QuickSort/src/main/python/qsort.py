def loadData(file):
    if not file.startswith('/'):
        file = '/' + file
    with open('../resources%s' % file) as f:
        return [int(line) for line in f.readlines()]

def swap(A, i, j):
    A[i], A[j] = A[j], A[i]

def pivot_first(A, l, r):
    return l

def pivot_last(A, l, r):
    return r - 1

def pivot_median_of_three(A, l, r):
    m = l + (r - l - 1) / 2
    a = A[l]
    b = A[m]
    c = A[r-1]
    if a <= b <= c or c <= b <= a:
        return m
    elif b <= a <= c or c <= a <= b:
        return l
    elif a <= c <= b or b <= c <= a:
        return r-1
    else:
        assert False

def partition(A, l, r, pivot_index):
    swap(A, l, pivot_index)
    p = A[l]
    i = l+1
    for j in range(l+1, r):
        if A[j] < p:
            swap(A, i, j)
            i += 1
    swap(A, l, i-1)
    return i-1

def qsort(A, l=None, r=None, choose_pivot=pivot_first):
    if l is None:
        l = 0
    if r is None:
        r = len(A)
    if r - l <= 1:
        return 0
    i = choose_pivot(A, l, r)
    p = partition(A, l, r, i)
    # print('pivot: %d:    %s and %s' % (A[p], A[l:p], A[p+1:r]))
    return qsort(A, l, p, choose_pivot) + \
           qsort(A, p+1, r, choose_pivot) + r - l - 1

def testOn(file):
    A = loadData(file)
    return (qsort(A[:], choose_pivot=pivot_first),
        qsort(A[:], choose_pivot=pivot_last),
        qsort(A[:], choose_pivot=pivot_median_of_three))

if __name__ == '__main__':
    print(testOn('/10.txt'))
    print(testOn('/100.txt'))
    print(testOn('/1000.txt'))
    print(testOn('/QuickSort.txt'))
