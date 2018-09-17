;;; SI 413 lab3
;;; MIDN Sipes

;;;Exercise 1;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;TAIL RECURSIVE
(define (min-sinHelp min lst)
  (if (= min (sin (car lst))) ;break when you hit empty list
      (car lst)
      (min-sinHelp min (cdr lst))))

(define (min-sin x . vals)
  (min-sinHelp
   (apply min (map sin (cons x vals))) (cons x vals)))



;;;Exercise 2;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;TAIL RECURSIVE
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
;TAIL RECURSIVE I think this could be considered tail recursive but I'm not sure...
(define (make-cXr i . args)
  (lambda (lst)
    (if (not (null? args)) ;then break it down even more
        (cond ((eqv? i 'a)
               (car ((apply make-cXr args) lst)))
              ((eqv? i 'd)
               (cdr ((apply make-cXr args) lst))))
        (cond ((eqv? i 'a) ;otherwise just use the initial one
               (car lst))
              ((eqv? i 'd)
               (cdr lst))))))



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
        ((= x (car lst))
         #t)
        (else
         (contains x (cdr lst)))))

(define (insertOne item lst)
  (cond ((null? lst);empty list
         (list item))
        ((<= item (car lst));;head of list
         (cons item lst))
        (else ;;put head of list in front of item
         (cons (car lst) (insertOne item (cdr lst))))))

(define (insert new lst)
  (display new)
  (cond ((not (list? new))
         (if (not (contains new lst))
             (insert (cdr new) (insertOne (car new) lst))))
        (else
         (display new)
         (if (not (contains (car new) lst))
             (insert (cdr new) (insertOne (car new) lst))))))
         
;  (if (not (null? new))
;      (insert (cdr new) (insertOne (car new) lst))
;      lst))
  
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
             (if (not (contains nums set));;FIX This to put the check in insert
                 (set! set (insert nums set))))))))
                 

;;;Exercise 8;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;TAIL RECURSIVE
(define (intersect lst set new)
  (if (or (null? lst) (null? set));;if either is empty return what the new list is
      new
      (if (contains (car set) lst);;if the first thing of set is in lst
          (insertOne (car set) new);put it into the new list
          (intersect (cdr lst) set new))));;Otherwise move to the next one

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
                 (set! set (insert nums set))))
            ((eqv? command 'intersect) ;;FIXME Intersect needs to return a make-set!!!
             (intersect set ((car nums) 'get) '()))))));;intersect takes my list and another make-set list that I need to call 'get on





