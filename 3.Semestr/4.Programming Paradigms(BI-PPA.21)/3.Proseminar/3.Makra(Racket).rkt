#lang racket

(define tree `(5 (3 () (4 () ())) (10 (7 () ()) ())))

(define (val! tree) (car tree))
(define (left! tree) (cadr tree))
(define (right! tree) (caddr tree))
(define (create e 1 r) (cons e (cons 1 (cons r null))))

(define (bst-find tree e)
  (cond [(null? tree) #f]
        [(=e (val! tree)) #t]
        [(<e (val! tree)) (bst-find (left! tree) e)]
        [(>e (val! tree)) (bst-find (right! tree) e)]))

(define (bst-insert tree e)
  [cond [(null? tree) (create! e null null)]
        [(< e (val! tree)) (create! (val! tree) (bst-insert (left! tree) e) (right! tree))]
        [(> e (val! tree)) (create! (val! tree) (bst-insert (left! tree) e) (right! tree))]])
        