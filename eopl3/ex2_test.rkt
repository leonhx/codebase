#lang eopl


(require rackunit
         rackunit/text-ui
         "ex2.rkt")


(define ex2-tests
  (test-suite
   "Tests for ex2.rkt"
   empty-stack push pop top empty-stack?
   
   (test-case
    "test stack"
    (let* ([s0 (empty-stack)]
           [s1 (push s0 1)]
           [e1 (top s1)]
           [s2 (pop s1)]
           [s3 (push (push s1 'a) '(for test))]
           [e2 (top s3)]
           [s4 (pop (pop (pop s3)))])
      
      (check-equal? (empty-stack? s0) #t "case 1")
      
      (check-equal? (empty-stack? s1) #f "case 2")
      
      (check-equal? e1 1 "case 3")
      
      (check-equal? e2 '(for test) "case 4")
      
      (check-equal? (empty-stack? s4) #t "case 5")))))


(run-tests ex2-tests)
