#lang racket

(define (my-len lst)
  (if (null? lst)
      0
      (+ (my-len (cdr lst)) 1)))

(define (my-max x y)
    (if (> x y)
        x
        y))

(define (my-mod x y)
  (if (equal? #f x)
      #f
      (if (equal? #f y)
          #f
  (if (> 0 (- x y))
      (if (> -1 (- x y))
          #f
          #t)
      (if (< 1 (- x y))
          #f
          #t)))))

(define (in-depth son)
  (if (null? son)
      0
      (if (equal? #f (my-mod(in-depth(cadr son)) (in-depth(caddr son))))
          #f
          (+ 1 (my-max(in-depth(cadr son)) (in-depth(caddr son)))))))

(define (is-balanced? tree)
  (if (< (my-len tree) 2)
      #t
      (my-mod (in-depth (cadr tree)) (in-depth (caddr tree)))))