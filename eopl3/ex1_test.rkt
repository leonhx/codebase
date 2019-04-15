#lang eopl


(require rackunit
         rackunit/text-ui
         "ex1.rkt")


(define ex1-tests
  (test-suite
   "Tests for ex1.rkt"


   (test-case
    "provided cases for duple"
    (let ([cases (list [list 2 3 '(3 3)]
                       [list 4 '(ha ha) '((ha ha) (ha ha) (ha ha) (ha ha))]
                       [list 0 '(blah) '()])])
      (for-each
       (lambda (elt)
         (check-equal? (duple (car elt) (cadr elt)) (caddr elt)))
       cases)))


   (test-case
    "provided cases for invert"
    (let ([cases (list [list '((a 1) (a 2) (1 b) (2 b))
                             '((1 a) (2 a) (b 1) (b 2))])])
      (for-each
       (lambda (elt)
         (check-equal? (invert (car elt)) (cadr elt)))
       cases)))


   (test-case
    "provided cases for down"
    (let ([cases (list [list '(1 2 3) '((1) (2) (3))]
                       [list '((a) (fine) (idea)) '(((a)) ((fine)) ((idea)))]
                       [list '(a (more (complicated)) object)
                             '((a) ((more (complicated))) (object))])])
      (for-each
       (lambda (elt)
         (check-equal? (down (car elt)) (cadr elt)))
       cases)))


   (test-case
    "provided cases for swapper"
    (let ([cases (list [list 'a 'd '(a b c d) '(d b c a)]
                       [list 'a 'd '(a d () c d) '(d a () c a)]
                       [list 'x 'y '((x) y (z (x))) '((y) x (z (y)))])])
      (for-each
       (lambda (elt)
         (check-equal? (swapper (car elt) (cadr elt) (caddr elt)) (cadddr elt)))
       cases)))


   (test-case
    "provided cases for list-set"
    (let ([cases (list [list '(a b c d) 2 '(1 2) '(a b (1 2) d)]
                       [list '(a b c d) 3 '(1 5 10) '(a b c (1 5 10))])])
      (for-each
       (lambda (elt)
         (check-equal? (list-set (car elt) (cadr elt) (caddr elt)) (cadddr elt)))
       cases)))


   (test-case
    "provided cases for count-occurrences"
    (let ([cases (list [list 'x '((f x) y (((x z) x))) 3]
                       [list 'x '((f x) y (((x z) () x))) 3]
                       [list 'w '((f x) y (((x z) x))) 0])])
      (for-each
       (lambda (elt)
         (check-equal? (count-occurrences (car elt) (cadr elt)) (caddr elt)))
       cases)))


   (test-case
    "provided cases for product"
    (let ([cases (list [list '(a b c) '(x y)
                             '((a x) (a y) (b x) (b y) (c x) (c y))]
                       [list '(a b c) '() '()])])
      (for-each
       (lambda (elt)
         (check-equal? (product (car elt) (cadr elt)) (caddr elt)))
       cases)))


   (test-case
    "provided cases for filter-in"
    (let ([cases (list [list number? '(a 2 (1 3) b 7) '(2 7)]
                       [list symbol? '(a (b c) 17 foo) '(a foo)])])
      (for-each
       (lambda (elt)
         (check-equal? (filter-in (car elt) (cadr elt)) (caddr elt)))
       cases)))


   (test-case
    "provided cases for list-index"
    (let ([cases (list [list number? '(a 2 (1 3) b 7) 1]
                       [list symbol? '(a (b c) 17 foo) 0]
                       [list symbol? '(1 2 (a b) 3) #f])])
      (for-each
       (lambda (elt)
         (check-equal? (list-index (car elt) (cadr elt)) (caddr elt)))
       cases)))


   (test-case
    "provided cases for every?"
    (let ([cases (list [list number? '(a b c 3 e) #f]
                       [list number? '(1 2 3 5 4) #t])])
      (for-each
       (lambda (elt)
         (check-equal? (every? (car elt) (cadr elt)) (caddr elt)))
       cases)))


   (test-case
    "provided cases for exists?"
    (let ([cases (list [list number? '(a b c 3 e) #t]
                       [list number? '(a b c d e) #f])])
      (for-each
       (lambda (elt)
         (check-equal? (exists? (car elt) (cadr elt)) (caddr elt)))
       cases)))


   (test-case
    "provided cases for up"
    (let ([cases (list [list '((1 2) (3 4)) '(1 2 3 4)]
                       [list '((x (y)) z) '(x (y) z)])])
      (for-each
       (lambda (elt)
         (check-equal? (up (car elt)) (cadr elt)))
       cases)))


   (test-case
    "provided cases for flatten"
    (let ([cases (list [list '(a b c) '(a b c)]
                       [list '((a) () (b ()) () (c)) '(a b c)]
                       [list '((a b) c (((d)) e)) '(a b c d e)]
                       [list '(a b (() (c))) '(a b c)])])
      (for-each
       (lambda (elt)
         (check-equal? (flatten (car elt)) (cadr elt)))
       cases)))


   (test-case
    "provided cases for merge"
    (let ([cases (list [list '(1 4) '(1 2 8) '(1 1 2 4 8)]
                       [list '(35 62 81 90 91) '(3 83 85 90)
                             '(3 35 62 81 83 85 90 90 91)])])
      (for-each
       (lambda (elt)
         (check-equal? (merge (car elt) (cadr elt)) (caddr elt)))
       cases)))


   (test-case
    "provided cases for sort"
    (let ([cases (list [list '(8 2 5 2 3) '(2 2 3 5 8)])])
      (for-each
       (lambda (elt)
         (check-equal? (sort (car elt)) (cadr elt)))
       cases)))


   (test-case
    "provided cases for sort/predicate"
    (let ([cases (list [list < '(8 2 5 2 3) '(2 2 3 5 8)]
                       [list > '(8 2 5 2 3) '(8 5 3 2 2)])])
      (for-each
       (lambda (elt)
         (check-equal? (sort/predicate (car elt) (cadr elt)) (caddr elt)))
       cases)))


   (let* ([l1 (leaf 10)]
          [l2 (leaf 11)]
          [l3 (leaf 12)]
          [l4 (leaf 13)]
          [n1 (interior-node 'a l1 l2)]
          [n2 (interior-node 'b l3 n1)]
          [n3 (interior-node 'c n2 l4)])

     (check-equal? (leaf? l1) #t "case 1 for leaf?")
     (check-equal? (leaf? n1) #f "case 2 for leaf?")

     (check-equal? (lson n1) l1 "case 1 for lson")
     (check-equal? (lson n2) l3 "case 2 for lson")
     (check-equal? (lson n3) n2 "case 3 for lson")

     (check-equal? (rson n1) l2 "case 1 for rson")
     (check-equal? (rson n2) n1 "case 2 for rson")
     (check-equal? (rson n3) l4 "case 3 for rson")

     (check-equal? (contents-of n1) 'a "case 1 for contents-of")
     (check-equal? (contents-of n2) 'b "case 2 for contents-of")
     (check-equal? (contents-of n3) 'c "case 3 for contents-of"))


   (let* ([l1 (leaf 10)]
          [dl1 (leaf 20)]
          [l2 (leaf 11)]
          [dl2 (leaf 22)]
          [l3 (leaf 12)]
          [dl3 (leaf 24)]
          [l4 (leaf 13)]
          [dl4 (leaf 26)]
          [n1 (interior-node 'a l1 l2)]
          [dn1 (interior-node 'a dl1 dl2)]
          [n2 (interior-node 'b l3 n1)]
          [dn2 (interior-node 'b dl3 dn1)]
          [n3 (interior-node 'c n2 l4)]
          [dn3 (interior-node 'c dn2 dl4)])

     (check-equal? (double-tree l1) dl1 "case 1 for double-tree")
     (check-equal? (double-tree l2) dl2 "case 2 for double-tree")
     (check-equal? (double-tree l3) dl3 "case 3 for double-tree")
     (check-equal? (double-tree l4) dl4 "case 4 for double-tree")
     (check-equal? (double-tree n1) dn1 "case 5 for double-tree")
     (check-equal? (double-tree n2) dn2 "case 6 for double-tree")
     (check-equal? (double-tree n3) dn3 "case 7 for double-tree"))


   (let ([t (interior-node 'red
                           (interior-node 'bar
                                          (leaf 26)
                                          (leaf 12))
                           (interior-node 'red
                                          (leaf 11)
                                          (interior-node 'quux
                                                         (leaf 117)
                                                         (leaf 14))))]
         [mt '(red
               (bar 1 1)
               (red 2 (quux 2 2)))])
     (check-equal? (mark-leaves-with-red-depth t) mt "case 1 for mark-leaves-with-red-depth"))


   (let ([bst '(14 (7 () (12 () ()))
                   (26 (20 (17 () ())
                           ())
                       (31 () ())))])

     (check-equal? (path 17 bst) '(right left left) "case 1 for path")
     (check-equal? (path 14 bst) '() "case 2 for path"))


   (let ([t (interior-node 'foo
                           (interior-node 'bar
                                          (leaf 26)
                                          (leaf 12))
                           (interior-node 'baz
                                          (leaf 11)
                                          (interior-node 'quux
                                                         (leaf 117)
                                                         (leaf 14))))])

     (check-equal? (number-leaves t) '(foo
                                       (bar 0 1)
                                       (baz
                                        2
                                        (quux 3 4))) "case 1 for number-leaves"))


   (check-equal? (number-elements '(a b c)) '((0 a) (1 b) (2 c)) "case 1 for number-elements")))


(run-tests ex1-tests)
