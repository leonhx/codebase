#lang racket

(define atom? 
  (lambda (x)
    (and (not (pair? x)) (not (null? x)))))

(define lat?
  (lambda (x)
    (cond [(null? x) #t]
          [(atom? (car x)) (lat? (cdr x))]
          [else #f])))

(define member?
  (lambda (a lat)
    (cond [(null? lat) #f]
          [(eq? a (car lat)) #t]
          [else (member? a (cdr lat))])))
