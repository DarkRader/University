#lang racket

(define (my-select-middle-element lst)
  (if (null? lst)
      null
      (my-select-middle-element-aux lst lst)))

(define (my-select-middle-element-aux p1 p2)
  (cond
    ((null? p2)        (car p1))
    ((null? (cdr p2))  (car p1))
    (#t                (my-select-middle-element-aux (cdr p1) (cddr p2)))))

(define (my-quicksort lst)
  (cond
    ((null? lst)       lst)
    ((null? (cdr lst)) lst)
    (#t                (let ((pivot (my-select-middle-element lst)))
                         (let ((left  (my-filter-lt lst pivot))
                               (right (my-filter-gt lst pivot))
                               (mid   (my-filter-eq lst pivot)))
                           (my-appendL (my-quicksort left)
                                       (my-appendL mid
                                                   (my-quicksort right))))))))

(define (my-filter-gt lst n) (my-filter (lambda (x) (> x n)) lst))
(define (my-filter-lt lst n) (my-filter (lambda (x) (< x n)) lst))
(define (my-filter-eq lst n) (my-filter (lambda (x) (= x n)) lst))

(define (my-foldr foo init lst)
  (if (null? lst)
      init
      (foo (my-foldr foo init (cdr lst)) (car lst))))

(define (my-filter foo lst)
  (my-foldr (lambda (acc x) (if (foo x) (cons x acc) acc)) null lst))

(define (my-appendL lst1 lst2)
  (if (null? lst1)
      lst2
      (cons (car lst1) (my-appendL (cdr lst1) lst2))))

(define (my-unique lst)
  (my-unique-aux lst null))
(define (my-unique-aux lst prev)
  (cond
    ((null? lst) lst)
    ((equal? prev (car lst)) (my-unique-aux (cdr lst) (car lst)))
    (#t                      (cons (car lst) (my-unique-aux (cdr lst) (car lst))))))

(define (my-member lst x)
  (cond
    ((null? lst)           #f)
    ((equal? (car lst) x)  #t)
    (#t (my-member (cdr lst) x))))

(define (my-delete-all lst e)
  (cond
    ((null? lst)'())
    ((equal? (car lst) e) (my-delete-all (cdr lst) e))
    (#t (cons (car lst) (my-delete-all (cdr lst) e)))))

(define (intersect lst1 lst2)
  (new-list lst1 lst2 lst2))

(define (new-list lst1 lst2 newLst)
  (if (null? lst2)
      (my-unique (my-quicksort newLst))
      (if (equal? #f (my-member lst1 (car lst2)))
          (new-list lst1 (cdr lst2) (my-delete-all newLst (car lst2)))
          (new-list lst1 (cdr lst2) newLst))))