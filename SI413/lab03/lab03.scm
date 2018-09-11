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
(define (makeList k lst args)
  (if (> k 0)
      (if (null? lst)
          (makeList (- k 1) (list (car args)) (cdr args))
          (makeList (- k 1) (list lst (car args)) (cdr args)))
      lst))
;(define (groupHelp k lst args
      
;(define (group k . args)

;;;Exercise 3;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
(define (power n)
  (lambda (x)
    (expt x n)))

;;;Exercise 4;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;(define (make-cXr x)
;  (lambda (y) 

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
(define (insert new old lst)
  (
  
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
                 

    
    
                  