;;; SI 413 Exam1
;;; MIDN SIPES

;;;Definitions;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
(define (filter pred? L)
  (cond ((null? L) '())
        ((pred? (car L))
         (cons (car L) (filter pred? (cdr L))))
        (else (filter pred? (cdr L)))))

(#%require (only scheme/base printf))

;;lmax from Unit2 notes
(define (lmax L)
  (cond ((null? (cdr L))
         (car L)) ; if list has one element, return it
        ((>= (car L) (lmax (cdr L)))
         (car L)) ; if first element is largest, return it
        (else (lmax (cdr L))))) ; else return recursive call
;;;Problem 1;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
(define (sum a b)
  (if (or (eqv? a 'inf) (eqv? b 'inf))
      'inf
      (+ a b)))

;;;Problem 2;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;do the python a[2:6] thingy
;;might need recursion helper function...
(define (sublistHelpback lst j newlst)
  (if (> j 1)
      (sublistHelpback (cdr lst) (- j 1) (append newlst (list (car lst))))
      newlst))

(define (sublistHelpfront lst i)
  (if (> i 0)
      (sublistHelpfront (cdr lst) (- i 1))
      (begin
        lst)))

(define (sublist lst i j)
  (sublistHelpback
   (sublistHelpfront lst i) (+ (- j i) 2) '()))

;;;Problem 3;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
(define (greaterthan22? x)
  (if (and (>= x 220000) (< x 230000) (modulo (modulo x 10000) 6))
      #t
      #f))
(define (count-plebes lst)
  (length (filter greaterthan22? lst)))


;;;Problem 4;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;


;;;FIXME for example: (pir 10 10 10 10)
(define (pir p . args)
  (if (> (length
          (filter (lambda (y) (if (>= p y) #t #f)) args))
         0)
      (lmax (filter (lambda (y) (if (>= p y) #t #f)) args))
      'over))


;;;Problem 5 & 6;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
(define (hotel chicken)
  (let ((rooms 0))
    (lambda (x)
      (cond ((eqv? x 'checkin!)
             (if (< rooms chicken)
                 (begin (set! rooms (+ rooms 1))
                        rooms)
                 'novacancy))
            ((eqv? x 'vacancies)
             (- chicken rooms))))))




      
