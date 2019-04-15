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

(define rember
  (lambda (a lat)
    (cond [(null? lat) '()]
          [(eq? a (car lat)) (cdr lat)]
          [else (cons (car lat) (rember a (cdr lat)))])))

(define firsts
  (lambda (l)
    (cond [(null? l) '()]
          [else (cons (car (car l)) (firsts (cdr l)))])))

(define insertR
  (lambda (new old lat)
    (cond [(null? lat) '()]
          [(eq? old (car lat)) 
           (cons (car lat) (cons new (cdr lat)))]
          [else (cons (car lat) (insertR new old (cdr lat)))])))
