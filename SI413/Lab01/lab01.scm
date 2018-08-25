;;; SI 413 Lab1
;;; MIDN SIPES

;;;Exercise 1;;;;;;;;;;;;;;;;;;;;;
(+ 3.7
   (* 4.7
      (- 34.453 47.728)))

;;;Exercise 2;;;;;;;;;;;;;;;;;;;;;;
(max
 (sqrt 5)
 (+
  (sin 1)
  (sin 2)
  (sin 3))
 (/ 31 13));/ sign produces exact rational numbers but
           ;due to how the max function evaluates inputs
           ;it turns into a decimal
           

;;;Exercise 3;;;;;;;;;;;;;;;;;;;;;;
(-
 (+
  (* 3 2.451)
  (-
   (* 2
      (expt 2.451 3))
   (expt 2.451 2)))
 5)

;;;Exercise 4;;;;;;;;;;;;;;;;;;;;;;;
(define root2
  (sqrt 2))
(define ex1
  (+ 3.7
     (* 4.7
        (- 34.453 47.728))))
(define ex2 
  (max
   (sqrt 5)
   (+
    (sin 1)
    (sin 2)
    (sin 3))
   (/ 31 13)))
(define ex3
  (-
   (+
    (* 3 2.451)
    (-
     (* 2
        (expt 2.451 3))
     (expt 2.451 2)))
   5))

;;;Exercise 5;;;;;;;;;;;;;;;;;;;;;;;;
(define (to-celsius f)
  (* (/ 5 9.0)
     (- f 32)))
(define (to-fahrenheit c)
  (+ 32
     (/ (* 9 c)
        5.0)))
;;;Exercise 6;;;;;;;;;;;;;;;;;;;;;;;;;;
(define (test-trig x)
  (+ (* (cos x)
        x)
     (expt (sin x) 2)))
;;;Exercise 7;;;;;;;;;;;;;;;;;;;;;;;;;;
(define (signed-inc x)
  (if (>= x 0)
      (+ x 1)
      (+ x -1)))
;;;Exercise 8;;;;;;;;;;;;;;;;;;;;;;;;;;;
(define (signed-inc-better x)
  (if (> x 0)
      (+ x 1)
      (if (= x 0)
          x
          (- x 1))))
;;;Exercise 9;;;;;;;;;;;;;;;;;;;;;;;;;;;
(define (middle x y z)
  (if (= x y)
      x)
  (if (= y z)
      y)
  (if (= x z)
      x)
  (if (> x y)
      (if (> y z)
          y
          (if (> x z)
              z
              x))
      (if (> x z)
          x
          (if (> y z)
              z
              y))))
;;;Exercise 10;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
(define (middle-better x y z)
  (cond ((or (= x y) (= x z)) x)
        ((= y z) z)
        ((and (> x y) (< x z)) x)
        ((and (< x y) (> x z)) x)
        ((and (> y z) (< y x)) y)
        ((and (< y z) (> y x)) y)
        (else z)))
;;;Exercise 11;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
(define (factorial x)
  (if (<= x 1)
      1
      (* x (factorial (- x 1)))))
;Java would not be able to do (factorial 111) because
;it would overflow the integer size
;;;Exercise 12;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
(define (compound-month B r)
  (* B
     (+ 1
        (/ r 1200))))
(define (accrue-months B r m)
  (if (> m 0)
      (accrue-months (compound-month B r) r (- m 1))
      B))
  
(define (accrue B r y)
  (if (> y 0)
      (accrue-months B r (* y 12))
      B))

;;;Exercise 13;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
(define (fiber x)
  (if (= x 0)
      0
      (if (or (= x 2) (= x 1))
          1
          (+ (fib (- x 1)) (fib (- x 2)))
          )))
(define (fib x)
  (if (< x 0)
      (* (expt -1 (+ x 1)) (fiber (* -1 x)))
      (fiber x)))
  
  
;;;Exercise 14;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
(define (split-inches x)
  (cons (quotient x 12) (modulo x 12)))
;;;Exercise 15;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
(define (shorter? x y)
  (if (> (car x) (car y))
      #f
      (if (< (car x) (car y))
          #t
          (< (cdr x) (cdr y)))))