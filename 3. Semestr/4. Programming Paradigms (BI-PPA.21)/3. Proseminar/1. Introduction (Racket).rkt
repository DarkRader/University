#lang racket

; factorial
(define (fact n)
    (if (= n 0)
    1
    (*(fact)(- n 1)n)))

; max and min
(define (my-max x y)
    (if (> x y)
        x
        y))

(define (my-min x y)
    (if (< x y)
        x
        y))

(define (fact-2 n)
  (fact-acc-inner n 1))

(define (fact-acc-inner n acc)
    (if (= n 0)
        acc
        (fact-acc-inner (- n 1) (* n acc))))

(define (my-len lst)
  (if (null? lst)
      0
      (+ (my-len (cdr lst)) 1)))

(define (my-sum lst)
   (if (null? lst)
       0
       (+(car lst)(my-sum (cdr lst)))))

(define (my-min-lst lst)
  (if (null? (cdr lst))
      (car lst)
      (my-min (car lst) (my-min-lst (cdr lst)))))

(define (lst-times-two lst)
  (if (null? lst)
       null
      (cons (* (car lst) 2) (lst-times-two (cdr lst)))))


(define(my-range-1 n)
  (my-reverse-acc (my-range-1-rev n) null))

(define(my-range-1-rev n)
  (if (= n 0)
      null
      (cons n (my-range-1-rev (- n 1)))))

(define (my-reverse lst)
  (if (null? lst)
      null
      (my-append (my-reverse (cdr lst)) (car lst))))

(define (my-reverse-acc lst acc)
  (if (null? lst)
      acc
      (my-reverse-acc (cdr lst) (cons (car lst) acc))))

(define (my-append lst n)
  (if (null? lst)
      (cons n null)
      (cons (car lst) (my-append (cdr lst) n))))

(define(my-range-2 n)
  (if (= n 0)
      null
      (my-append (my-range-2 (- n 1)) n)))

(define(my-range-3 n acc)
  (if (= n 0)
      acc
      (my-range-3 (- n 1) (cons n acc))))

(define(my-range-4 from to)
  (if (> from to)
      null
      (cons from (my-range-4 (+ from 1) to))))