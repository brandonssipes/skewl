;;; SI 413 lab3
;;; MIDN Sipes

;;;Exercise 1;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
(define (min-sinHelp min lst)
  (if (= min (sin (car lst))) ;break when you hit empty list
      (car lst)
      (min-sinHelp min (cdr lst))))

(define (min-sin x . vals)
  (min-sinHelp
   (apply min (map sin (cons x vals))) (cons x vals)))

;;;Exercise 2;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
(define (removeList k lst) ;delete k elements from the lst
  (if (> k 0)
      (removeList (- k 1) (cdr lst))
      lst))

(define (makeList k lst) ;build lst into the list from args
  (if (> k 0)
      (cons (car lst) (makeList (- k 1) (cdr lst)))
      '()))


(define (group k . args)
  (if (not (null? args))
      (cons (makeList k args) (apply group k (removeList k args)))
      '()))


;;;Exercise 3;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
(define (power n)
  (lambda (x)
    (expt x n)))

;;;Exercise 4;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;



;(define (make-cXr . args)
;  (lambda (lst)
;    (if (not (null? args))
;        (cond ((eqv? (car args) 'a)
;               ((apply make-cXr (cdr args))(car lst)))
;              ((eqv? (car args) 'd)
;               ((apply make-cXr (cdr args)) (cdr lst)))
;              (else (display args)))
;        lst)))
 
(define (make-cXr i . x)
  (if (not (null? (x)))
      (lambda (y)
        (cond ((eqv? i 'a)
               (car y))
              ((eqv? i 'd)
               (cdr y)))
        (cond ((eqv? i 'a)
               (car ((apply make-cXr x) y)))
              ((eqv? i 'd)
               (cdr ((apply make-cXr x) y)))))))


;;;Exercies 5;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
(define (make-stack)
  (let ((stack '()))
    (lambda (command . items)
      (cond ((eqv? command 'size)
             (length stack))
            ((eqv? command 'pop)
             (let ((save (car stack)))
               (set! stack (cdr stack))
               save))
            ((eqv? command 'push)
             (if (null? stack)
                 (set! stack items)
                 (set! stack (cons stack items))))))))

;;;Exercise 6;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
(define (make-set)
  (let ((set '()))
    (lambda (command . nums)
      (cond ((eqv? command 'get)
             set)
            ((eqv? command 'size)
             (length set))
            ((eqv? command 'set!)
             (set! set (car nums)))))))

;;;Exercise 7;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
(define (contains x lst)
  (cond ((null? lst)
         #f)
        ((eqv? x (car lst))
         #t)
        (else (contains x (cdr lst)))))
;(define (insert new lst)
; (
  
(define (make-set)
  (let ((set '()))
    (lambda (command . nums)
      (cond ((eqv? command 'get)
             set)
            ((eqv? command 'size)
             (length set))
            ((eqv? command 'set!)
             (set! set (car nums)))
            ((eqv? command 'contains?)
             (contains nums set))
            ((eqv? command 'insert!);use contains to check each one
             (if (not (contains nums set))
                 (insert nums set)))))))
                 

;;;Exercise 8;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
(define (merge lst set)
  (if (not (null? lst))
      (if (not (contains (car lst) set))
          (insert (car lst) set))
      (intersect (cdr lst) set)))

;(define (intersect lst set);NOT DONE

(define (make-set)
  (let ((set '()))
    (lambda (command . nums)
      (cond ((eqv? command 'get)
             set)
            ((eqv? command 'size)
             (length set))
            ((eqv? command 'set!)
             (set! set (car nums)))
            ((eqv? command 'contains?)
             (contains nums set))
            ((eqv? command 'insert!);use contains to check each one
             (if (not (contains nums set))
                 (insert nums set)))
            ((eqv? command 'intersect)
             (intersect nums set))))))

;;;Exercise 10;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
(define (min-sinHelp min lst)
  (if (not (= min (sin (car lst)))) ;break when you hit empty list
      (min-sinHelp min (cdr lst))
      (car lst)))
      

(define (min-sin x . vals)
  (min-sinHelp
   (apply min (map sin (cons x vals))) (cons x vals)))



