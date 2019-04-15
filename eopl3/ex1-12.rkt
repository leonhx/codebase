#lang eopl

;; subst : Sym * Sym * S-list -> S-list
(define subst
  (lambda (new old slist)
    (if (null? slist)
        '() 
        (cons
         (if (symbol? (car slist))
             (if (eqv? (car slist) old) new (car slist)) (subst new old (car slist)))
    (subst new old (cdr slist))))))
