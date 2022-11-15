#lang racket

;Proseminar 1 - introduction 

; factorial
(define (fact n)
  (if (= n 0)
      1
      (* n (fact (- n 1)))))

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




;Proseminar 2 - introduction 

(define (is-prime? n)
  (is-prime-inner? n 2))

; (if (>= i n)
 ;     #t
  ;    (if (= (modulo n i) 0)
   ;       #f
    ;      (is-prime-inner? n (+ i 1)))))

(define (is-prime-inner? n i)
  (cond
    [(> (* i i) n ) #t]
    [(= (modulo n i) 0) #f]
    [#t (is-prime-inner? n (+ i 1))]))

(define (my-pair x y)
  (cons x (cons y null)))

(define (lst-cart n lst)
  (if (null? lst)
      null
      (cons (my-pair n (car lst)) (lst-cart n (cdr lst)))))

(define (append-lst lst1 lst2)
  (if (null? lst1)
      lst2
      (cons (car lst1) (append-lst (cdr lst1) lst2))))

(define (cart lst1 lst2)
  (if (null? lst1)
      null
      (append-lst (lst-cart (car lst1) lst2) (cart (cdr lst1) lst2))))
    
(define (flatten lst)
  (cond
    [(null? lst) null]
    [(not (list? (car lst))) (cons (car lst) (flatten (cdr lst)))]
    [#t (append-lst (flatten (car lst)) (flatten (cdr lst)))]))


;Implementation InsertSort

;insert on the right position in order array
(define (insert-pos lst n)
  (cond
    [(null? lst) (cons n null)]
    [(<= n (car lst)) (cons n lst)]
    [#t (cons (car lst) (insert-pos (cdr lst) n))]))

(define (insert-sort lst)
  (if (null? lst)
      null
      (insert-pos (insert-sort (cdr lst)) (car lst))))


;Implementation MergeSort

(define (split lst)
  (let ([len (floor (/ (my-len lst) 2))])
  (my-pair(take lst len)
          (drop lst len))))

(define (merge lst1 lst2)
  (cond
    [(null? lst1) lst2]
    [(null? lst2) lst1]
    [(< (car lst1) (car lst2)) (cons (car lst1) (merge (cdr lst1) lst2))]
    [#t (cons (car lst2) (merge lst1 (cdr lst2)))]))

(define (mergesort lst)
  (if (or (null? lst) (null? (cdr lst)))
      lst
      (let*
          ([pair-res (split lst)]
           [first-half (car pair-res)]
           [second-half (cadr pair-res)]
           )
        (merge (mergesort first-half) (mergesort second-half) ))))