#lang racket

(define (my-foldr foo init lst)
  (if (null? lst)
      init
      (foo (my-foldr foo init (cdr lst)) (car lst))))

(define (my-filter foo lst)
  (my-foldr (lambda (acc x) (if (foo x) (cons x acc) acc)) null lst))

(define (my-filter-rev foo lst)
  (my-foldr (lambda (acc x) (if (foo x) acc (cons x acc))) null lst))

(define (my-pair x y)
  (cons x (cons y null)))

(define (partition-by f lst)
  (my-pair (my-filter f lst) (my-filter-rev f lst)))