#lang racket

;Proseminar 3

(define (fact n)
  (if (= n 0)
      1
      (* n (fact (- n 1)))))

(define (my-nth n lst)
  (if (= n 0)
      (car lst)
      (my-nth (- n 1) (cdr lst))))

(define (my-pair x y)
  (cons x (cons y null)))

(define (my-append n lst)
  (if (null? lst)
      (cons n null)
      (cons (car lst) (my-append n (cdr lst)))))



(define (sum lst)
  (if (null? lst)
      0
      (+ (sum (cdr lst)) (car lst))))

(define (mul lst)
  (if (null? lst)
      1
      (* (mul (cdr lst)) (car lst))))

(define (max-lst lst)
  (if (null? lst)
      0
      (max (car lst) (max-lst (cdr lst)))))

(define (foldr proc init lst)
  (if (null? lst)
      init
      (proc (car lst) (foldr proc init (cdr lst)))))

(define (sum-foldr lst)
  (foldr + 0 lst))

(define (reverse lst)
  (foldr my-append null lst))

(define (append-lst lst1 lst2)
  (if (null? lst1)
      lst2
      (cons (car lst1) (append-lst (cdr lst1) lst2))))

(define (rev lst)
  (if (null? lst)
      null
      (my-append (car lst) (rev (cdr lst)))))


(define (fact-acc n acc)
  (if (= n 0)
      acc
      (fact-acc (- n 1) (* n acc))))

(define (rev-acc lst acc)
  (if (null? lst)
      acc
      (rev-acc (cdr lst) (cons (car lst) acc))))

(define (foldl proc init lst)
  (if (null? lst)
      init
      (foldl proc (proc (car lst) init) (cdr lst))))
  

(define (mul-by-two lst)
  (if (null? lst)
      null
      (cons (* 2 (car lst)) (mul-by-two (cdr lst)))))

(define (lst-fact lst)
  (if (null? lst)
      null
      (cons (fact (car lst)) (lst-fact (cdr lst)))))

(define (my-map proc lst)
  (if (null? lst)
      null
      (cons (proc (car lst)) (my-map proc (cdr lst)))))

(define (map proc lst)
  (foldr (lambda (e init) (cons (proc e) init)) null lst))

(define (filter proc lst)
  (foldr (lambda (e init)
           (if (proc e)
               (cons e init)
               init)) null lst))

(define (avg-fold lst)
  (foldl (lambda (e init)
           (let ([sum (car init)]
                 [len (cadr init)])
             (my-pair (+ e sum) (+ len 1)))) (my-pair 0 0) lst))

(define (avg lst)
  (let ([res (avg-fold lst)])
    (/ (car res) (cadr res))))

(define matrix1 '( (1 2 3)
                   (4 5 6)
                   (7 8 9)))
(define matrix2 '( (4 2 3)
                   (4 1 6)
                   (4 1 6)))

(define (col matrix n)
  (map (lambda (row) (my-nth n row)) matrix))

(define (my-zip lst1 lst2)
  (if (or (null? lst1) (null? lst2))
      null
      (cons (my-pair (car lst1) (car lst2)) (my-zip (cdr lst1) (cdr lst2)))))

(define (lst-sum lst1 lst2)
  (map
   (lambda (pair)
     ( + (car pair) (cadr pair)))
   (my-zip lst1 lst2)))

(define (matrix-sum mat1 mat2)
  (map (lambda (row-pair) (lst-sum (car row-pair) (cadr row-pair) )) (my-zip mat1 mat2)))