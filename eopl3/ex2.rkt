#lang eopl


;; empty-stack : () -> Stack
(define empty-stack
  (lambda ()
    (lambda (func)
      (cond [(eq? func 'pop) (eopl:error "pop on an empty stack")]
            [(eq? func 'top) (eopl:error "top on an empty stack")]
            [(eq? func 'empty-stack?) #t]))))


;; push : Stack * SchemeVal -> Stack
(define push
  (lambda (stack e)
    (lambda (func)
      (cond [(eq? func 'pop) stack]
            [(eq? func 'top) e]
            [(eq? func 'empty-stack?) #f]))))


;; pop : Stack -> Stack
(define pop
  (lambda (stack)
    (stack 'pop)))


;; top : Stack -> SchemeVal
(define top
  (lambda (stack)
    (stack 'top)))


;; empty-stack? : Stack -> Bool
(define empty-stack?
  (lambda (stack)
    (stack 'empty-stack?)))


(provide empty-stack push pop top empty-stack?)
