#lang racket

(define tree '(5 (3 () (4 () ())) (10 (7 () ()) ())))

(define (val! tree) (car tree))
(define (left! tree) (cadr tree))
(define (right! tree) (caddr tree))
(define (create! e l r) (cons e (cons l (cons r null))))

(define (bst-find tree e)
  (cond [(null? tree) #f]
        [(= e (val! tree)) #t]
        [(< e (val! tree)) (bst-find (left! tree) e)]
        [(> e (val! tree)) (bst-find (right! tree) e)]))

(define (bst-insert tree e)
  (cond [(null? tree) (create! e null null)]
        [(< e (val! tree)) (create! (val! tree) (bst-insert (left! tree) e) (right! tree))]
        [(> e (val! tree)) (create! (val! tree) (left! tree) (bst-insert (right! tree) e))]
        [#t tree])) ; duplicita - nic nevkladame

(define (my-append-lst l1 l2)
  (if (null? l1)
      l2
      (cons (car l1) (my-append-lst (cdr l1) l2))))
(define (bst-inorder tree)
  (if (null? tree)
      null
      (my-append-lst
       (bst-inorder (left! tree))
       (cons (val! tree)
             (bst-inorder (right! tree))))))


; (define tree1 '(5 null null))    ; POZOR! 'null != null !
  (define tree2 `(5 ,null ,null))  ; spravne :-)
  (define tree3 '(5 () ()))        ; taky spravne
  (define tree4 `(5 () ()))        ; samozrejme taky spravne

; -------------------------------------------------------------------

(require compatibility/defmacro)


(define-macro (ifNull? condX tb fb)
  `(if (null? ,condX)
      ,tb
      ,fb))


; if (null? (cdr '(5))
;      (println -...)
;      (println -...)

; (ifNull? (cdr '(5)) (println "ahoj") (println "hello"))

; -------------------------------------------------


; (assert (my-append-lst '(1 2) '(3 4)) '(1 2 3 4))
#|(if (equal? (my-append-lst '(1 2) '(3 4)) '(1 2 3 4))
    (void)
    (println kod-ktery-se-testuje vysledek ocekavany-vysledek))
|#

(define-macro (assert expr expected)
  (let [(newVar (gensym))]
  `(let [(,newVar ,expr)]
    (if (equal? ,newVar ,expected)
       (void)
       (println (format "Assertion ~a resulted in ~a but expected ~a" ',expr ,newVar ,expected))))))

 ;(assert (my-append-lst '(1 2) '(3 4)) '(1 2 3 3 4))

; myslenka: (let [a (* 2 3)] (+ a 1))
;        + a 1           a je volna promenna -> svazat!
;  (\a . + a 1)          -> ale kolik je a? Jak dosadim za a?
; ((\a . + a 1) (* 2 3))
(define-macro (let-one bind-pair body)
  `(
    (lambda (,(car bind-pair)) ,body)
    ,(cadr bind-pair)
   ))


(let-one (a (+ 2 1)) (+ a 2))

; stejna myslenka jako v let-one, jen dovolime multi-args lambdy
;          (+ a b)
;  (\a b . (+ a b)) 3 (+ 2 2)
(define-macro (let bind-pairs body)
  `(
    (lambda  ,(map car bind-pairs) ,body)
    ,@(map cadr bind-pairs)
    ))

;(let [(a (+ 3 2)) (b (+ 3 3))] (+ a b))
; (let ((a 3) (b a)) (+ a b))

; bonus:
; rekurzivni makro - sledujte expanzi v macro stepperu
; Myslenka:
; (let [(a 2) (b (+ a 1))] body
;
;              body
;       [(\b . body) (+ a 1)]
; (\a . [(\b . body) (+ a 1)]) 2)
(define-macro (let* bind-pairs body)
  (if (null? bind-pairs)
      body
      `( (lambda (,(caar bind-pairs))
           (let* ,(cdr bind-pairs) ,body))
         ,(cadar bind-pairs))))

(assert (let* [(a 3) (b (+ a 1)) (c (+ b 1))] (+ a b c)) 12)

; -----------------------


(define (my-while i to f)
  (if (> i to)
      (void)
      (begin ; vykona kazdy prikaz a vrati navratovou hodnotu toho posledniho
        (f i)
        (my-while (+ i 1) to f)
      )))

(define-macro (loop var from to body)
  `(my-while ,from ,to (lambda (,var) ,body)))

(define (fact n) (if (= n 0) 1 (* n (fact (- n 1)))))
(loop asdasdasdasd 5 100 (println (fact asdasdasdasd)))        