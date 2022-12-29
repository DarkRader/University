#lang racket
(require compatibility/defmacro)

(define (SudokuSolver sudokuMatrix)
  (solution sudokuMatrix (find-size-sudoku sudokuMatrix 0)))

(define (find-size-sudoku matrix i)
  (if (null? matrix)
      (sqrt i)
      (find-size-sudoku (cdr matrix) (+ i 1))))

;Preparing function for control row, column and squares.
(define (row lst poz)
  (list-ref lst (- poz 1)))

(define (control-row lst poz num)
  (if (equal? #f (member num (row lst poz)))
      #f
      #t))

(define (get-poz-row lst poz num)
  (if (equal? #f (index-of (row lst poz) num))
      0
      (+ (index-of (row lst poz) num) 1)))

(define (colum lst poz)
  (if (null? lst)
      null
      (append (cons(list-ref (car lst) (- poz 1)) (colum (cdr lst) poz)))))

(define (control-colum lst poz num)
  (if (equal? #f (member num (colum lst poz)))
      #f
      #t))

(define (get-poz-colum lst poz num)
  (if (equal? #f (index-of (colum lst poz) num))
      0
      (+ (index-of (colum lst poz) num) 1)))

(define (row-squarebox lst n num)
  (if (>= num n)
      null
      (append (cons(list-ref (car lst) num) (row-squarebox lst n (+ 1 num))))))

(define (squarebox lst n num i)
  (if (>= i n)
      null
      (append (row-squarebox lst n num) (squarebox (cdr lst) n num (+ 1 i)))))

(define (get-squarebox lst n numbox)
  (squarebox (list-tail lst (* (truncate (/ (- numbox 1) n))n)) (* (+ (modulo (- numbox 1) n) 1) n) (- (* (+ (modulo (- numbox 1) n) 1) n) n) (- (* (+ (modulo (- numbox 1) n) 1) n) n)))

(define (control-squarebox lst n numbox num)
  (if (equal? #f (member num (get-squarebox lst n numbox)))
      #f
      #t))

(define (get-poz-squarebox lst n numbox num)
  (if (equal? #f (index-of (get-squarebox lst n numbox) num))
      0
      (+ (index-of (get-squarebox lst n numbox) num) 1)))
;End of section preparing functions

;Helping function for finding candidate to adding in subgrid
(define (part lst n)
  (let-values (((head tail) (split-at lst n)))
    (list head tail)))

(define (useless-num lst n cut-part)
  (remove* (car(part(list-tail lst cut-part)n))lst))

(define (find-cand-in-box lst n i)
  (if (>= i (* n n))
      lst
      (if (equal? 0 (list-ref lst i))
          (find-cand-in-box lst n (+ i 1))
          (find-cand-in-box (list-set lst i #f) n (+ i 1)))))

(define (cand-in-row lst n i)
  (if (>= i n)
      lst
      (if (equal? 0 (list-ref lst i))
          (cand-in-row (list-set lst i #f) n (+ i 1))
          (cand-in-row lst n (+ i 1)))))

(define (find-cand-in-row matrix lst poz n i num numbox)
  (if (>= (- i 1) n)
      lst
      (if (equal? #f (member num (useless-num (row matrix (+ (* (truncate (/ (- numbox 1) n)) n) i)) n (*(modulo (- numbox 1) n)n))))
          (find-cand-in-row matrix lst (* (+ i 1) n) n (+ i 1) num numbox)
          (find-cand-in-row matrix (cand-in-row lst poz (- poz n)) (* (+ i 1) n) n (+ i 1) num numbox))))

(define (cand-in-colum lst n i poz)
  (if (>= i n)
      lst
      (if (equal? 0 (list-ref lst poz))
          (cand-in-colum (list-set lst poz #f) n (+ 1 i) (+ poz n))
          (cand-in-colum lst n (+ 1 i) (+ poz n)))))

(define (find-cand-in-colum matrix lst poz n i num numbox)
  (if (>= (- i 1) n)
      lst
      (if (equal? #f (member num (useless-num (colum matrix (+ (* (modulo (- numbox 1) n) n) i)) n (* (truncate (/ (- numbox 1) n)) n))))
          (find-cand-in-colum matrix lst (+ poz 1) n (+ 1 i) num numbox)
          (find-cand-in-colum matrix (cand-in-colum lst n 0 poz) (+ poz 1) n (+ 1 i) num numbox))))

(define (i-poz poz n numbox)
  (+ (truncate (/ poz n)) (*(truncate (/ (- numbox 1) n)) n)))

(define (j-poz poz n numbox)
  (+ (* (modulo (- numbox 1) n) n) (modulo poz n)))

(define (new-elem lst poz n numbox num)
  (list-set lst (i-poz poz n numbox) (list-set (list-ref lst (i-poz poz n numbox)) (j-poz poz n numbox) num)))
        
(define (candidate-squarebox lst n numbox num)
  (if (equal? 1 (length (remove* '(#f) (find-cand-in-colum lst (find-cand-in-row lst (find-cand-in-box (get-squarebox lst n numbox) n 0) n n 1 num numbox) 0 n 1 num numbox))))
      (new-elem lst (index-of (find-cand-in-colum lst (find-cand-in-row lst (find-cand-in-box (get-squarebox lst n numbox) n 0) n n 1 num numbox) 0 n 1 num numbox) 0) n numbox num)
      lst))

(define (candidate-squarebox-cycle lst n numbox i)
  (if (> i (* n n))
      lst
      (if (equal? #t (control-squarebox lst n numbox i))
          (candidate-squarebox-cycle lst n numbox (+ i 1))
          (candidate-squarebox-cycle (candidate-squarebox lst n numbox i) n numbox (+ i 1)))))

(define (sudoku-pole lst n i)
  (if (> i (* n n))
      lst
      (sudoku-pole (candidate-squarebox-cycle lst n i 1) n (+ i 1))))

(define (solve-subgrid lst n)
  (if (equal? lst (sudoku-pole lst n 1))
      lst
      (solve-subgrid (sudoku-pole lst n 1) n)))

;Helping function for finding candidate to adding in row and column
(define (num-in-sudoku lst n i)
  (if (> i (* n n))
      lst
     (num-in-sudoku (append lst (cons i '())) n (+ i 1))))

(define (list-cand lst n)
  (remove* lst (num-in-sudoku null n 1)))

(define (list-cand-num lst n i)
  (if (> i (* n n))
      lst
      (if (equal? 0 (list-ref lst (- i 1)))
          (list-cand-num (list-set lst (- i 1) (list-cand lst n)) n (+ i 1))
          (list-cand-num lst n (+ i 1)))))

(define (find-subgrid matrix poz i n)
  (get-squarebox matrix n (+ (+(truncate (/ (- i 1) n)) 1) (* (truncate (/ (- poz 1) n)) n))))

;Row
(define (change-row-elem matrix tmpMatrix lst newElem poz i n)
  (if (equal? 1 (length (remove* (find-subgrid tmpMatrix poz i n) (remove* (colum tmpMatrix i) newElem))))
      (list-set matrix (- poz 1) (list-set lst (- i 1) (car(remove* (find-subgrid tmpMatrix poz i n) (remove* (colum tmpMatrix i) newElem)))))
      matrix))

(define (candidate-row-cycle lst tmpLst n i poz)
  (if (> i (* n n))
      lst
      (if (equal? #f (list? (list-ref (list-cand-num (row lst poz) n 1) (- i 1))))
          (candidate-row-cycle lst tmpLst n (+ i 1) poz)
          (candidate-row-cycle (change-row-elem lst tmpLst (row lst poz) (list-ref (list-cand-num (row lst poz) n 1) (- i 1)) poz i n) tmpLst n (+ i 1) poz))))
;Row

;Column
(define (change-colum-elem matrix tmpLst lst newElem poz i n)
  (if (equal? 1 (length (remove* (find-subgrid tmpLst i poz n) (remove* (row tmpLst i) newElem))))
      (list-set matrix (- i 1) (list-set lst (- poz 1) (car(remove* (find-subgrid tmpLst i poz n) (remove* (row tmpLst i) newElem)))))
      matrix))

(define (candidate-colum-cycle lst tmpLst n i poz)
  (if (> i (* n n))
      lst
      (if (equal? #f (list? (list-ref (list-cand-num (colum lst poz) n 1) (- i 1))))
          (candidate-colum-cycle lst tmpLst n (+ i 1) poz)
          (candidate-colum-cycle (change-colum-elem lst tmpLst (row lst i) (list-ref (list-cand-num (colum lst poz) n 1) (- i 1)) poz i n) tmpLst n (+ i 1) poz))))
;Column

(define (solve lst tmpLst n i type)
  (if (> i (* n n))
      lst
      (if (equal? "row" type)
      (solve (candidate-row-cycle lst tmpLst n 1 i) tmpLst n (+ i 1) type)
      (solve (candidate-colum-cycle lst tmpLst n 1 i) tmpLst n (+ i 1) type))))


;Solving single
(define (set-single-num matrix lst poz num lstControl)
  (if (not (equal? 0 (list-ref lst (- poz 1))))
      (list-set lst (- poz 1) #f)
      (if (member num lstControl)
          (list-set lst (- poz 1) #f)
          lst)))
;Row
(define (single-num-cycle matrix lst n i num)
  (if (> i (* n n))
      lst
      (single-num-cycle matrix (set-single-num matrix lst i num (colum matrix i)) n (+ i 1) num)))
      

(define (check-numbers-r matrix n i poz)
  (if (> i (* n n))
      matrix
      (if (equal? #t (control-row matrix poz i))
          (check-numbers-r matrix n (+ i 1) poz)
          (if (equal? 1 (length (remove* '(#f) (single-num-cycle matrix (row matrix poz) n 1 i))))
              (check-numbers-r (list-set matrix (- poz 1) (list-set (row matrix poz) (index-of (single-num-cycle matrix (row matrix poz) n 1 i) 0) i)) n (+ i 1) poz)
              (check-numbers-r matrix n (+ i 1) poz)))))
;Row

;Column
(define (single-num-cycle-c matrix lst n i num)
  (if (> i (* n n))
      lst
      (single-num-cycle-c matrix (set-single-num matrix lst i num (row matrix i)) n (+ i 1) num)))
      
(define (check-numbers-c matrix n i poz)
  (if (> i (* n n))
      matrix
      (if (equal? #t (control-colum matrix poz i))
          (check-numbers-c matrix n (+ i 1) poz)
          (if (equal? 1 (length (remove* '(#f) (single-num-cycle-c matrix (colum matrix poz) n 1 i))))
              (check-numbers-c (list-set matrix (index-of (single-num-cycle-c matrix (colum matrix poz) n 1 i) 0) (list-set (row matrix (+ (index-of (single-num-cycle-c matrix (colum matrix poz) n 1 i) 0) 1)) (- poz 1) i)) n (+ i 1) poz)
              (check-numbers-c matrix n (+ i 1) poz)))))
;Column


(define (single matrix i n type)
  (if (> i (* n n))
      matrix
      (if (equal? "row" type)
          (single (check-numbers-r matrix n 1 i) (+ i 1) n type)
          (single (check-numbers-c matrix n 1 i) (+ i 1) n type))))

;Solving sudoku with notes
(define (control-numbox-note-r control lst n i)
 (if (> i n)
     (if (> (length control) 0)
         #t
         #f)
      (if (equal? 0 (list-ref lst (- i 1)))
          (control-numbox-note-r (append '(#t) control) lst n (+ i 1))
          (control-numbox-note-r control lst n (+ i 1)))))

(define (control-numbox-note-c control lst n i)
 (if (> i (* n n))
     (if (> (length control) 0)
         #t
         #f)
      (if (equal? 0 (list-ref lst (- i 1)))
          (control-numbox-note-c (append control '(#t)) lst n (+ i n))
          (control-numbox-note-c control lst n (+ i n)))))

(define (control-numbox-notes-row control lst n i i-mn)
  (if (> i (* n n))
      (if (equal? 1 (length (remove* '(#f) control)))
          #t
          #f)
      (if (equal? #t (control-numbox-note-r '() lst (* n i-mn) i))
          (control-numbox-notes-row (append control '(#t)) lst n (+ i n) (+ i-mn 1))
          (control-numbox-notes-row (append control '(#f)) lst n (+ i n) (+ i-mn 1)))))

(define (control-numbox-notes-colum control lst n i)
  (if (> i n)
      (if (equal? 1 (length (remove* '(#f) control)))
          #t
          #f)
      (if (equal? #t (control-numbox-note-c '() lst n i))
          (control-numbox-notes-colum (append control '(#t)) lst n (+ i 1))
          (control-numbox-notes-colum (append control' (#f)) lst n (+ i 1)))))

(define (fin-note-control lst n)
  (if ( equal? #t (and (control-numbox-notes-colum '() lst n 1) (control-numbox-notes-row '() lst n 1 1)))
      #f
      (if (equal? #t (or (control-numbox-notes-colum '() lst n 1) (control-numbox-notes-row '() lst n 1 1)))
          #t
          #f))) 

(define (sudoku-notes lst tmpLst numbox n num i)
  (if (> i (* n n))
      (solve lst tmpLst n 1 "row")
         (if (equal? #f (fin-note-control (find-cand-in-colum lst (find-cand-in-row lst (find-cand-in-box (get-squarebox lst n numbox) n 0) n n 1 num numbox) 0 n 1 num numbox) n))
             lst
         (if (equal? 0 (list-ref (find-cand-in-colum lst (find-cand-in-row lst (find-cand-in-box (get-squarebox lst n numbox) n 0) n n 1 num numbox) 0 n 1 num numbox) (- i 1)))   
         (sudoku-notes lst (new-elem tmpLst (- i 1) n numbox num) numbox n num (+ i 1))
         (sudoku-notes lst tmpLst numbox n num (+ i 1))))))

(define (sudoku-notes-cycle lst tmpLst i n num)
  (if (> i (* n n))
      lst
      (if (equal? #t (control-squarebox lst n i num))
      (sudoku-notes-cycle lst tmpLst (+ i 1) n num)
      (sudoku-notes-cycle (sudoku-notes lst tmpLst i n num 1) lst (+ i 1) n num))))

(define (solve-notes lst beginLst n i)
  (if (not (equal? lst beginLst))
      lst
  (if (> i (* n n))
      lst
      (solve-notes (sudoku-notes-cycle lst lst 1 n i) beginLst n (+ i 1)))))

;Control function
(define (null-control matrix n i)
  (if (> i (* n n))
      (row matrix (- i 1))
      (append (row matrix i) (null-control matrix n (+ 1 i)))))

(define (final-control matrix n)
  (if (equal? #f (member 0 (null-control matrix n 1)))
      #f
      #t))

;Solve function
(define (solve-other matrix n)
  (if (equal? matrix (single (single (solve (solve (solve-subgrid matrix n) (solve-subgrid matrix n) n 1 "row") (solve (solve-subgrid matrix n) (solve-subgrid matrix n) n 1 "row") n 1 "colum") 1 n "row") 1 n "colum"))
      matrix
      (solve-other (single (single (solve (solve (solve-subgrid matrix n) (solve-subgrid matrix n) n 1 "row") (solve (solve-subgrid matrix n) (solve-subgrid matrix n) n 1 "row") n 1 "colum") 1 n "row") 1 n "colum") n)))

(define (solution matrix n)
  (if (equal? #f (final-control matrix n))
      matrix
      (if (equal? #f (final-control (solve-subgrid matrix n) n))
          (solve-subgrid matrix n)
          (if (equal? #f (final-control (solve-other (single (single (solve (solve (solve-subgrid matrix n) (solve-subgrid matrix n) n 1 "row") (solve (solve-subgrid matrix n) (solve-subgrid matrix n) n 1 "row") n 1 "colum") 1 n "row") 1 n "colum") n) n))
             (solution (single (single (solve (solve (solve-subgrid matrix n) (solve-subgrid matrix n) n 1 "row") (solve (solve-subgrid matrix n) (solve-subgrid matrix n) n 1 "row") n 1 "colum") 1 n "row") 1 n "colum") n)
             (solution (solve-notes (single (single (solve (solve (solve-subgrid matrix n) (solve-subgrid matrix n) n 1 "row") (solve (solve-subgrid matrix n) (solve-subgrid matrix n) n 1 "row") n 1 "colum") 1 n "row") 1 n "colum")
                          (single (single (solve (solve (solve-subgrid matrix n) (solve-subgrid matrix n) n 1 "row") (solve (solve-subgrid matrix n) (solve-subgrid matrix n) n 1 "row") n 1 "colum") 1 n "row") 1 n "colum") n 1) n)))))
              

;TESTS:

;2x2

(define sudoku2x2 '((0 0 4 0) (0 1 0 0) (0 0 2 0) (0 3 0 0)))

;EASY
(define sudoku1 '( (5 0 0  0 4 0  0 9 0)
                   (0 6 4  8 2 0  1 0 0)
                   (0 0 3  1 5 7  0 6 4)
                   
                   (0 2 8  0 0 0  4 7 0)
                   (0 4 6  0 9 1  8 5 0)
                   (0 5 7  2 8 0  6 1 0)
                   
                   (2 8 0  6 1 5  3 0 0)
                   (0 0 5  0 7 8  9 2 0)
                   (0 7 0  0 3 0  0 0 6)))

(define sudoku2 '( (0 0 3  0 2 0  6 0 0)
                   (9 0 0  3 0 5  0 0 1)
                   (0 0 1  8 0 6  4 0 0)
                   
                   (0 0 8  1 0 2  9 0 0)
                   (7 0 0  0 0 0  0 0 8)
                   (0 0 6  7 0 8  2 0 0)
                   
                   (0 0 2  6 0 9  5 0 0)
                   (8 0 0  2 0 3  0 0 9)
                   (0 0 5  0 1 0  3 0 0)))

;MEDIUM
(define sudoku3 '( (0 0 0  0 0 0  6 0 9)
                   (1 0 0  0 0 4  0 0 0)
                   (0 0 5  3 0 6  8 2 1)
                   
                   (0 0 4  6 7 0  0 5 0)
                   (0 0 7  0 0 0  9 0 0)
                   (0 0 0  5 4 0  0 0 0)
                   
                   (3 7 0  4 0 5  2 0 6)
                   (0 0 0  0 0 0  5 1 0)
                   (0 6 0  0 2 0  0 3 7)))

(define sudoku4 '( (0 7 0  3 0 2  0 0 8)
                   (2 0 1  0 5 0  0 0 3)
                   (8 0 0  0 7 0  0 0 0)
                   
                   (3 0 0  2 0 0  0 8 0)
                   (0 0 6  0 0 0  3 0 0)
                   (4 5 0  8 0 3  0 0 9)
                   
                   (6 0 7  0 0 9  0 1 5)
                   (0 4 0  0 0 0  0 0 0)
                   (0 9 8  5 2 0  0 0 0)))

;HARD
(define sudoku5 '( (0 0 0  0 6 8  0 3 0)
                   (1 9 0  0 0 0  0 0 0)
                   (8 0 3  1 0 0  2 0 0)
                   
                   (4 0 0  0 5 1  0 6 0)
                   (7 0 0  0 2 0  0 0 4)
                   (0 0 0  0 7 0  8 0 0)
                   
                   (0 1 0  0 0 5  0 0 7)
                   (0 0 4  0 0 0  0 0 0)
                   (0 5 0  0 3 0  1 0 0)))

(define sudoku6 '( (2 6 0  3 0 0  0 1 0)
                   (5 8 0  4 0 0  7 0 0)
                   (0 0 0  0 6 0  0 2 8)
                   
                   (0 0 0  8 3 0  0 0 7)
                   (0 1 2  7 0 5  3 0 0)
                   (0 5 0  0 0 0  0 0 0)
                   
                   (0 4 6  0 0 0  0 0 1)
                   (7 0 0  0 0 3  0 4 0)
                   (0 3 5  0 8 4  6 0 0)))

(define sudoku7 '( (0 7 0  0 0 0  0 0 3)
                   (9 0 0  3 2 0  0 0 7)
                   (0 0 0  1 0 9  5 2 0)
                   
                   (0 2 0  0 0 8  7 4 9)
                   (5 0 9  0 0 0  0 1 0)
                   (0 0 0  0 0 0  0 0 0)
                   
                   (8 0 0  9 6 0  0 3 0)
                   (3 0 0  8 0 0  2 0 0)
                   (0 0 5  0 3 0  9 0 0)))

;16X16 
(define sudoku8 '((13 11  5  4   12  0  6  3  15 16 10  0    7  0 14  1)
                   ( 9  7 14  8    0  4 15  0  13  3  0  0    0  0  0 12)
                   ( 6  0  0  0    7 16  0  0   0  5  0  0    4  8  0  0)
                   ( 0  0 12  3    1  5 13 14   0  0  0  4    0 11  0  9)
                   
                   ( 0  3  7  0    0  1  8 10  12  0 11  2    5  0  0  0)
                   (15  5  8  0    0  0  2  0   0  0  0 14    0  0  0 11)
                   ( 0  1  0  0    0 13 11 15   0  0  0  0    0  3 16  2)
                   ( 0  0  0  0   14  0  0 16   3  0  0  5    0  0 10  8)

                   ( 3  0  4  0    0  0  9  8  10 12  0  7    2  0  0 16)
                   ( 0  0  9  0    0  0  1 12   0  4 14 16    6  0 11 10)
                   ( 5 15  0 10    0  0  0  0   0  9  0  3   12 14  1  0)
                   ( 1  0  2  0    0  0  0  0   6  0  0  0    8  9  0  3)

                   ( 0  0 11  6    0 10  0  0   0  0  0  0    1  0  8 14)
                   (14 10 16 15    8  0  4  1   0  0  3 12   11  0  7  5)
                   ( 7  4  3  0    0  9  0  0   0  1  8  6    0  0  2 15)
                   ( 2  8  1  0   16 12  0 13   0  0 15  0    0  6  9  4)))

;SOLUTION:

(define answer2x2'((3 2 4 1) (4 1 3 2) (1 4 2 3) (2 3 1 4)))
              
(define answer1 '((5 1 2  3 4 6  7 9 8)
                  (7 6 4  8 2 9  1 3 5)
                  (8 9 3  1 5 7  2 6 4)
                  (1 2 8  5 6 3  4 7 9)
                  (3 4 6  7 9 1  8 5 2)
                  (9 5 7  2 8 4  6 1 3)
                  (2 8 9  6 1 5  3 4 7)
                  (6 3 5  4 7 8  9 2 1)
                  (4 7 1  9 3 2  5 8 6)))

(define answer2 '((4 8 3 9 2 1 6 5 7) (9 6 7 3 4 5 8 2 1) (2 5 1 8 7 6 4 9 3) (5 4 8 1 3 2 9 7 6) (7 2 9 5 6 4 1 3 8) (1 3 6 7 9 8 2 4 5) (3 7 2 6 8 9 5 1 4) (8 1 4 2 5 3 7 6 9) (6 9 5 4 1 7 3 8 2)))

(define answer3 '((8 3 2 1 5 7 6 4 9) (1 9 6 2 8 4 3 7 5) (7 4 5 3 9 6 8 2 1) (9 8 4 6 7 2 1 5 3) (2 5 7 8 3 1 9 6 4) (6 1 3 5 4 9 7 8 2) (3 7 8 4 1 5 2 9 6) (4 2 9 7 6 3 5 1 8) (5 6 1 9 2 8 4 3 7)))

(define answer4 '((9 7 4 3 1 2 6 5 8) (2 6 1 9 5 8 7 4 3) (8 3 5 6 7 4 2 9 1) (3 1 9 2 4 7 5 8 6) (7 8 6 1 9 5 3 2 4) (4 5 2 8 6 3 1 7 9) (6 2 7 4 3 9 8 1 5) (5 4 3 7 8 1 9 6 2) (1 9 8 5 2 6 4 3 7)))

(define answer5 '((2 4 7 5 6 8 9 3 1) (1 9 5 3 4 2 6 7 8) (8 6 3 1 9 7 2 4 5) (4 3 9 8 5 1 7 6 2) (7 8 1 9 2 6 3 5 4) (5 2 6 4 7 3 8 1 9) (3 1 2 6 8 5 4 9 7) (6 7 4 2 1 9 5 8 3) (9 5 8 7 3 4 1 2 6)))

(define answer6'((2 6 9 3 7 8 4 1 5) (5 8 1 4 2 9 7 6 3) (4 7 3 5 6 1 9 2 8) (6 9 4 8 3 2 1 5 7) (8 1 2 7 4 5 3 9 6) (3 5 7 1 9 6 2 8 4) (9 4 6 2 5 7 8 3 1) (7 2 8 6 1 3 5 4 9) (1 3 5 9 8 4 6 7 2)))

(define answer7 '((4 7 2 5 8 6 1 9 3) (9 5 1 3 2 4 8 6 7) (6 3 8 1 7 9 5 2 4) (1 2 3 6 5 8 7 4 9) (5 8 9 7 4 3 6 1 2) (7 4 6 2 9 1 3 5 8) (8 1 7 9 6 2 4 3 5) (3 9 4 8 1 5 2 7 6) (2 6 5 4 3 7 9 8 1)))

(define answer8
'((13 11 5 4 12 8 6 3 15 16 10 9 7 2 14 1)
  (9 7 14 8 2 4 15 11 13 3 6 1 16 10 5 12)
  (6 2 15 1 7 16 10 9 14 5 12 11 4 8 3 13)
  (10 16 12 3 1 5 13 14 2 8 7 4 15 11 6 9)
  (16 3 7 14 9 1 8 10 12 13 11 2 5 4 15 6)
  (15 5 8 9 4 3 2 6 1 10 16 14 13 7 12 11)
  (4 1 10 12 5 13 11 15 7 6 9 8 14 3 16 2)
  (11 6 13 2 14 7 12 16 3 15 4 5 9 1 10 8)
  (3 14 4 11 6 15 9 8 10 12 1 7 2 5 13 16)
  (8 13 9 7 3 2 1 12 5 4 14 16 6 15 11 10)
  (5 15 6 10 13 11 16 4 8 9 2 3 12 14 1 7)
  (1 12 2 16 10 14 5 7 6 11 13 15 8 9 4 3)
  (12 9 11 6 15 10 3 2 4 7 5 13 1 16 8 14)
  (14 10 16 15 8 6 4 1 9 2 3 12 11 13 7 5)
  (7 4 3 13 11 9 14 5 16 1 8 6 10 12 2 15)
  (2 8 1 5 16 12 7 13 11 14 15 10 3 6 9 4)))


;ASSERTS
(define-macro (my-assert-equals body1 body2)
         `(unless (equal? ,body1 ,body2)
     (error (format "Failed assertion '(assert-equals ~a ~a)'" ',body1 ',body2))))

(my-assert-equals (SudokuSolver sudoku2x2) answer2x2)
(my-assert-equals (SudokuSolver sudoku1) answer1)
(my-assert-equals (SudokuSolver sudoku2) answer2)
(my-assert-equals (SudokuSolver sudoku3) answer3)
(my-assert-equals (SudokuSolver sudoku4) answer4)
(my-assert-equals (SudokuSolver sudoku5) answer5)
(my-assert-equals (SudokuSolver sudoku6) answer6)
(my-assert-equals (SudokuSolver sudoku7) answer7)
(my-assert-equals (SudokuSolver sudoku8) answer8)







 
