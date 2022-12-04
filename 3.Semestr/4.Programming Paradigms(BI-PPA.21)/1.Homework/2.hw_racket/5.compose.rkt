#lang racket

(define (compose-chain lstFunc)
  ( lambda (x) (foldr (lambda (newInt oldInt)  (newInt oldInt)) ((lambda (y) y) x) lstFunc)))