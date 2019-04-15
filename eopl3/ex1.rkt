#lang eopl


;; duple : Int * SchemeVal -> Listof(SchemeVal)
;; usage : (duple n x) returns a list containing n copies of x
(define duple
  (lambda (n x)
    (if (= n 0)
        '()
        (cons x (duple (- n 1) x)))))


;; invert : Listof(SchemeVal) -> Listof(SchemeVal)
;; usage : (invert lst), where lst is a list of 2-lists (lists of length two), 
;;         returns a list with each 2-list reversed
(define invert
  (lambda (lst)
    (if (null? lst)
        '()
        (cons (list (cadar lst) (caar lst)) (invert (cdr lst))))))


;; down : Listof(SchemeVal) -> Listof(SchemeVal)
;; usage : (down lst) wraps parentheses around each top-level element of lst
(define down
  (lambda (lst)
    (if (null? lst)
        '()
        (cons (list (car lst)) (down (cdr lst))))))


;; swapper : Sym * Sym * S-list -> S-list
;; usage : (swapper s1 s2 slist) returns a list the same as slist, but with
;;         all occurrences of s1 replaced by s2 and all occurrences of s2
;;         replaced by s1
(define swapper
  (lambda (s1 s2 slist)
    (if (null? slist)
        '()
        (let ([head (car slist)]
              [tail (cdr slist)])
          (if (symbol? head)
              (cond [(eqv? head s1) (cons s2 (swapper s1 s2 tail))]
                    [(eqv? head s2) (cons s1 (swapper s1 s2 tail))]
                    [else (cons head (swapper s1 s2 tail))])
              (cons (swapper s1 s2 head) (swapper s1 s2 tail)))))))


;; list-set : Listof(SchemeVal) * Int * SchemeVal -> Listof(SchemeVal)
;; usage : (list-set lst n x) returns a list like lst, except that the 
;;         n-th element, using zero-based indexing, is x
(define list-set
  (lambda (lst n x)
    (if (= n 0)
        (cons x (cdr lst))
        (cons (car lst) (list-set (cdr lst) (- n 1) x)))))


;; count-occurrences : Sym * S-list -> Int
;; usage : (count-occurrences s slist) returns the number of occurrences
;;         of s in slist
(define count-occurrences
  (lambda (s slist)
    (if (null? slist) 0
        (let ([head (car slist)]
              [tail (cdr slist)])
          (+ (if (symbol? head)
                 (if (eqv? head s) 1 0)
                 (count-occurrences s head))
             (count-occurrences s tail))))))


(define concat
  (lambda (lst1 lst2)
    (if (null? lst1) lst2
        (cons (car lst1) (concat (cdr lst1) lst2)))))


;; product : Listof(Sym) * Listof(Sym) -> Listof(List(Sym,Sym))
;; usage : (product los1 los2), where sos1 and sos2 are each a list of
;;         symbols without repetitions, returns a list of 2-lists that
;;         represents the Cartesian product of sos1 and sos2. The 2-lists
;;         may appear in any order
(define product
  (lambda (los1 los2)
    (if (or (null? los1) (null? los2)) '()
        (concat (map (lambda (e) (list (car los1) e)) los2)
                (product (cdr los1) los2)))))


;; filter-in : (SchemeVal -> Bool) * Listof(SchemeVal) -> Listof(SchemeVal)
;; usage : (filter-in pred lst) returns the list of those elements in lst
;;         that satisfy the predicate pred
(define filter-in
  (lambda (pred lst)
    (if (null? lst) '()
        (if (pred (car lst))
            (cons (car lst) (filter-in pred (cdr lst)))
            (filter-in pred (cdr lst))))))


;; list-index : (SchemeVal -> Bool) * Listof(SchemeVal) -> Int
;; usage : (list-index pred lst) returns the 0-based position of the first
;;         element of lst that satisfies the predicate pred. If no element
;;         of lst satisfies the predicate, then list-index returns #f
(define list-index
  (lambda (pred lst)
    (list-index-from pred lst 0)))

(define list-index-from
  (lambda (pred lst idx)
    (cond [(null? lst) #f]
          [(pred (car lst)) idx]
          [else (list-index-from pred (cdr lst) (+ idx 1))])))


;; every? : (SchemeVal -> Bool) * Listof(SchemeVal) -> Bool
;; usage : (every? pred lst) returns #f if any element of lst fails to
;;         satisfy pred, and returns #t otherwise
(define every?
  (lambda (pred lst)
    (cond [(null? lst) #t]
          [(not (pred (car lst))) #f]
          [else (every? pred (cdr lst))])))


;; exists? : (SchemeVal -> Bool) * Listof(SchemeVal) -> Bool
;; usage : (exists? pred lst) returns #t if any element of lst satisfies
;;         pred, and returns #f otherwise satisfy pred, and returns #t
;;         otherwise
(define exists?
  (lambda (pred lst)
    (cond [(null? lst) #f]
          [(pred (car lst)) #t]
          [else (exists? pred (cdr lst))])))


;; up : Listof(SchemeVal) -> Listof(SchemeVal)
;; usage : (up lst) removes a pair of parentheses from each top-level
;;         element of lst. If a top-level element is not a list, it is
;;         included in the result, as is. The value of (up (down lst)) is
;;         equivalent to lst, but (down (up lst)) is not necessarily lst
(define up
  (lambda (lst)
    (cond [(null? lst) '()]
          [(pair? (car lst)) (concat (car lst) (up (cdr lst)))]
          [else (cons (car lst) (up (cdr lst)))])))


;; flatten: S-list -> S-list
;; usage : (flatten slist) returns a list of the symbols contained in 
;;         slist in the order in which they occur when slist is printed.
;;         Intuitively, flatten removes all the inner parentheses from
;;         its argument
(define flatten
  (lambda (slist)
    (cond [(null? slist) '()]
          [(symbol? (car slist)) (cons (car slist) (flatten (cdr slist)))]
          [else (concat (flatten (car slist)) (flatten (cdr slist)))])))


;; merge : Listof(Int) * Listof(Int) -> Listof(Int)
;; usage : (merge loi1 loi2), where loi1 and loi2 are lists of integers
;;         that are sorted in ascending order, returns a sorted list of
;;         all the integers in loi1 and loi2
(define merge
  (lambda (loi1 loi2)
    (cond [(null? loi1) loi2]
          [(null? loi2) loi1]
          [else
           (let ([h1 (car loi1)]
                 [h2 (car loi2)])
             (if (< h1 h2)
                 (cons h1 (merge (cdr loi1) loi2))
                 (cons h2 (merge loi1 (cdr loi2)))))])))


(define take
  (lambda (n lst)
    (if (or (= n 0) (null? lst)) '()
        (cons (car lst) (take (- n 1) (cdr lst))))))


(define drop
  (lambda (n lst)
    (if (or (= n 0) (null? lst)) lst
        (drop (- n 1) (cdr lst)))))


;; sort : Listof(Int) -> Listof(Int)
;; usage : (sort loi) returns a list of the elements of loi in ascending order
(define sort
  (lambda (loi)
    (let ([len (length loi)])
      (if (<= len 1) loi
          (merge (sort (take (quotient len 2) loi))
                 (sort (drop (quotient len 2) loi)))))))


(define merge/predicate
  (lambda (pred loi1 loi2)
    (cond [(null? loi1) loi2]
          [(null? loi2) loi1]
          [else
           (let ([h1 (car loi1)]
                 [h2 (car loi2)])
             (if (pred h1 h2)
                 (cons h1 (merge/predicate pred (cdr loi1) loi2))
                 (cons h2 (merge/predicate pred loi1 (cdr loi2)))))])))


;; sort/predicate : (SchemeVal * SchemeVal -> Bool) * Listof(SchemeVal) -> Listof(SchemeVal)
;; usage : (sort/predicate pred loi) returns a list of elements sorted by the predicate
(define sort/predicate
  (lambda (pred loi)
    (let ([len (length loi)])
      (if (<= len 1) loi
          (merge/predicate
           pred
           (sort/predicate pred (take (quotient len 2) loi))
           (sort/predicate pred (drop (quotient len 2) loi)))))))


;; Bintree ::= Int | (Symbol Bintree Bintree)

;; leaf : Int -> Leaf
(define leaf
  (lambda (n)
    n))


;; interior-node : Sym * Bintree * Bintree -> InNode
(define interior-node
  (lambda (s bt1 bt2)
    (list s bt1 bt2)))


;; leaf? : Bintree -> Bool
(define leaf?
  (lambda (bt)
    (not (pair? bt))))


;; lson : InNode -> Bintree
(define lson
  (lambda (in)
    (cadr in)))


;; rson : InNode -> Bintree
(define rson
  (lambda (in)
    (caddr in)))


;; contents-of : Bintree -> Sym
(define contents-of
  (lambda (bt)
    (if (leaf? bt) bt (car bt))))


;; double-tree : Bintree -> Bintree
(define double-tree
  (lambda (t)
    (if (leaf? t)
        (leaf (* 2 (contents-of t)))
        (interior-node (contents-of t)
                       (double-tree (lson t))
                       (double-tree (rson t))))))


;; mark-leaves-with-red-depth-from : Bintree * Int -> Bintree
(define mark-leaves-with-red-depth-from
  (lambda (t n)
    (cond [(leaf? t) (leaf n)]
          [(eq? (contents-of t) 'red)
           (interior-node (contents-of t)
                          (mark-leaves-with-red-depth-from (lson t) (+ n 1))
                          (mark-leaves-with-red-depth-from (rson t) (+ n 1)))]
          [else (interior-node (contents-of t)
                               (mark-leaves-with-red-depth-from (lson t) n)
                               (mark-leaves-with-red-depth-from (rson t) n))])))


;; mark-leaves-with-red-depth : Bintree -> Bintree
(define mark-leaves-with-red-depth
  (lambda (t)
    (mark-leaves-with-red-depth-from t 0)))


;; Binary-search-tree ::= () | (Int Binary-search-tree Binary-search-tree)

;; path-from : Int * BST * Listof(Sym) -> Listof(Sym)
(define path-from
  (lambda (n bst p)
    (cond [(null? bst) #f]
          [(= n (car bst)) p]
          [(< n (car bst)) (path-from n (cadr bst) (concat p '(left)))]
          [else (path-from n (caddr bst) (concat p '(right)))])))


;; path : Int * BST -> Listof(Sym)
(define path
  (lambda (n bst)
    (path-from n bst '())))


;; count-leaves : Bintree -> Int
(define count-leaves
  (lambda (t)
    (if (leaf? t) 1
        (+ (count-leaves (lson t))
           (count-leaves (rson t))))))



;; number-leaves-from : Bintree * n -> Bintree
(define number-leaves-from
  (lambda (t n)
    (if (leaf? t)
        (leaf n)
        (interior-node (contents-of t)
                       (number-leaves-from (lson t) n)
                       (number-leaves-from (rson t) (+ n (count-leaves (lson t))))))))


;; number-leaves : Bintree -> Bintree
(define number-leaves
  (lambda (t)
    (number-leaves-from t 0)))


;; g : List(Int, SchemeVal) * Listof(List(Int, SchemeVal)) -> Listof(List(Int, SchemeVal))
(define g
  (lambda (lst plst)
    (cons lst
          (map (lambda (p) (list (+ (car p) 1) (cadr p))) plst))))


;; number-elements : List -> Listof(List(Int, SchemeVal))
;; usage: (number-elements ’(v0 v1 v2 ...))
;;        = ((0 v0) (1 v1) (2 v2) ...)
(define number-elements
  (lambda (lst)
    (if (null? lst) '()
        (g (list 0 (car lst)) (number-elements (cdr lst))))))


(provide duple invert down swapper list-set count-occurrences product 
         filter-in list-index every? exists? up flatten merge sort
         sort/predicate leaf interior-node leaf? lson rson contents-of
         double-tree mark-leaves-with-red-depth path number-leaves
         number-elements)
