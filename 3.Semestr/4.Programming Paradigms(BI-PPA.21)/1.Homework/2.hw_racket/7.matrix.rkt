#lang racket

(define (my-reverse lst)
  (if (null? lst)
      null
      (my-append (my-reverse (cdr lst)) (car lst))))

(define (my-append lst n)
  (if (null? lst)
      (cons n null)
      (cons (car lst) (my-append (cdr lst) n))))

(define (my-nth lst n)
  (cond
    ((null? lst) null)
    ((= n 0)     (car lst))
    (#t          (my-nth (cdr lst) (- n 1)))))
  
(define (mul-row lst mat poz)
  (if (null? lst)
      0
      (+ (mul-row (cdr lst) (cdr mat) poz) (* (car lst) (my-nth(car mat) poz)))))

(define (app-row lst mat poz controlMat)
  (if (null? (my-nth (car controlMat) poz))
      null
      (my-append (app-row lst mat (+ 1 poz)  controlMat) (mul-row lst mat poz))))
  
(define (app-column mat1 mat2)
  (if (null? mat1)
      null
      (my-append (app-column (cdr mat1) mat2) (my-reverse (app-row (car mat1) mat2  0 mat2)))))
      
(define (matrix-mul mat1 mat2)
  (my-reverse (app-column mat1 mat2)))