#lang racket

(define (my-reverse lst)
  (if (null? lst)
      null
      (my-append (my-reverse (cdr lst)) (car lst))))

(define (my-delete-all lst e)
  (cond
    ((null? lst)          '())
    ((equal? (car lst) e) (my-delete-all (cdr lst) e))
    (#t                   (cons (car lst) (my-delete-all (cdr lst) e)))))

(define (my-append lst x)
  (if (null? lst)
      (cons x null)
      (cons (car lst) (my-append (cdr lst) x))))

(define (in-interval? lst1 lst2)
  (if (or (equal? (car lst1) (car lst2)) (equal? (car lst1) (car (cdr lst2))) (equal? (car (cdr lst1)) (car lst2)) (equal? (car (cdr lst1)) (car (cdr lst2))))
      1
      (if (or (and (< (car lst2) (car lst1)) (< (car lst1) (car (cdr lst2)))) (and (< (car lst2) (car (cdr lst1))) (< (car (cdr lst1)) (car (cdr lst2)))) (and (< (car lst1) (car lst2)) (< (car (cdr lst2)) (car (cdr lst1)))))
          1
          0)))

(define (inter-or-not lst1 lst2)
  (if (null? lst2)
      0
      (+ (in-interval? lst1 (car lst2)) (inter-or-not lst1 (cdr lst2)))))

(define (list-interval lst controlList newList)
  (if (null? controlList)
      `()
      (my-append (list-interval lst (cdr controlList) newList) (- (inter-or-not (car controlList) lst) 1))))

       
(define (intervals lst)
  (my-reverse (list-interval lst lst `())))