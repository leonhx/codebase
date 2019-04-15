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

(define add1
  (lambda (n) (+ n 1)))

(define sub1
  (lambda (n) (- n 1)))

(define o+
  (lambda (n m)
    (cond [(zero? m) n]
          [else (o+ (add1 n) (sub1 m))])))

(define o-
  (lambda (n m)
    (cond [(zero? m) n]
          [else (o- (sub1 n) (sub1 m))])))

(define addtup
  (lambda (tup)
    (cond [(null? tup) 0]
          [else (o+ (car tup) (addtup (cdr tup)))])))

(define x
  (lambda (n m)
    (cond [(zero? m) 0]
          [else (o+ n (x n (sub1 m)))])))

(define tup+
  (lambda (tup1 tup2)
    (cond [(null? tup1) tup2]
          [(null? tup2) tup1]
          [else (cons (o+ (car tup1) (car tup2))
                      (tup+ (cdr tup1) (cdr tup2)))])))

(define >
  (lambda (n m)
    (cond [(zero? n) #f]
          [(zero? m) #t]
          (else (> (sub1 n) (sub1 m))))))

(define <
  (lambda (n m)
    (cond [(zero? m) #f]
          [(zero? n) #t]
          (else (< (sub1 n) (sub1 m))))))

(define =
  (lambda (n m)
    (cond [(> n m) #f]
          [(< n m) #f]
          (else #t))))

(define expt
  (lambda (n m)
    (cond [(zero? m) 1]
          [else (x n (expt n (sub1 m)))])))

(define rember*
  (lambda (a l)
    (cond [(null? l) '()]
          [(atom? (car l))
           (cond [(eq? a (car l)) (rember* a (cdr l))]
                 [else (cons (car l) (rember* a (cdr l)))])]
          [else (cons (rember* a (car l)) (rember* a (cdr l)))])))
