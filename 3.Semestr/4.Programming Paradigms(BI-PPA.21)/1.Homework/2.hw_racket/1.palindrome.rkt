#lang racket

(define (my-reverse lst)
  (if (null? lst)
      null
      (my-append (my-reverse (cdr lst)) (car lst))))

(define (my-append lst n)
  (if (null? lst)
      (cons n null)
      (cons (car lst) (my-append (cdr lst) n))))

(define (my-len lst)
  (if (null? lst)
      0
      (+ (my-len (cdr lst)) 1)))

(define (is-palindrome? lst)
  (if (< (my-len lst) 3)
      #t
      ( my-palindrom (cdr (my-reverse (cdr lst))))))

(define (my-palindrom lst)
  (if (< (my-len lst) 2)
      #t
      (if (equal? (car lst) (car (my-reverse lst)))
          (my-palindrom (cdr (my-reverse (cdr lst))))
          #f)))