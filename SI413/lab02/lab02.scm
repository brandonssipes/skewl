;;; SI 413 lab2
;;; MIDN SIPES

;;;Exercise 1;;;;;;;;;;;;;;;;;;;;;;;;;;;
(define (to-usdollar amt cur)
  (cond ((eqv? 'euro cur) (/ amt .76))
        ((eqv? 'yen cur) (/ amt 98.18))
        ((eqv? 'won cur) (/ amt 1109.85))
        ((eqv? 'usd cur) amt)))

;;;Exercise 2;;;;;;;;;;;;;;;;;;;;;;;;;;;;
(define (from-usdollar amt cur)
  (/ 1 (to-usdollar (/ 1 amt) cur)))

;;;Exercise 3;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
(define (convert amt fromCur toCur)
  (from-usdollar (to-usdollar amt fromCur) toCur))

;;;Exercise 4;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
(define (squares i j)
  (if (> i j)
      '()
      (cons (expt i 2) (squares (+ 1 i) j))))

;;;Exercise 5;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
(define (longer? L1 L2)
  (if (or (eqv? L1 L2) (eqv? L1 '()))
      #f
      (if (eqv? L2 '())
          #t
          (longer? (cdr L1) (cdr L2)))))

;;;Exercise 6;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
(define (sum-cash L1)
  (if (eqv? L1 '())
      0
      (+
       (convert (caar L1) (cadar L1) 'usd)
       (sum-cash (cdr L1)))))

;;;Exercise 7;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
(define (average L1)
  (/ (apply + L1) (length L1)))

(define (std-devCALC L1 u)
  (if (eqv? L1 '())
      0
      (+ (expt (- (car L1) u) 2) (std-devCALC (cdr L1) u))))

(define (std-dev L1)
  (expt
   (/
    (std-devCALC L1 (average L1))
    (- (length L1) 1))
   0.5))

;;;Exercise 8;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;Optional
;(define (uniquefy L1)
  

;;;Exercise 9;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
(define (test-sin x)
  (let ((a (+ 1
              (expt (sin x) 2))))
    (- (+ (/ 1 a) (expt a 0.5)) (expt a 2))))

;;;Exercise 10;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
(define (dist a b c d)
  (let ((L1 (+ (* 12 a) b))
        (L2 (+ (* 12 c) d)))
    (abs (- L1 L2))))

;;;Exercise 11;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
(define (fd-at g n)
  (- (g (+ 1 n)) (g n)))



;;;filter function
(define (filter pred? L)
  (cond ((null? L) '())
        ((pred? (car L))
         (cons (car L) (filter pred? (cdr L))))
        (else (filter pred? (cdr L)))))
; Returns a list containing integers a, a+1, ..., b.
(define (range a b)
  (if (> a b)
      '()
      (cons a (range (+ a 1) b))))

;;;Exercise 12;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
(define (sqrt-prod n)
  (apply * (map sqrt (range 1 n))))

;;;Exercise 13;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
(define (sqr x) (* x x))
(define (divideByThree x) (/ x 3))
(define (timesThree x) (* x 3))
(define (special-nums n)
  (map timesThree (filter integer? (map divideByThree (map sqr  (filter integer? (map sqrt (range 1 n))))))))
