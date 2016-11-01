(defun foo(s) 
	(cond ((null s) 1) 
	((atom s) 0) 
	(t (max (+ (foo (first s)) 1) (foo (rest s))))))
(foo(list 1 2 3 4 5 6 7))

(defun power(n m)
	(if (= m 0) 1
	(* n (power n (- m 1)))))

(defun replace_elmt(a_list list_elmt new_elmt)
	(cons (if (eq (first a_list) list_elmt) new_elmt (first a_list))
		(if (eq (rest a_list) nil) '() 
			(replace_elmt (rest a_list) list_elmt new_elmt))))

(defun add1(my_list)
	(if (= (mod (length my_list) 2) 0) my_list 
		(if (= (length my_list) 1) (+ (car my_list) 1)
			(cons (car my_list) 
			(add1 cdr (reverse ( cdr (reverse my_list)))) 
			(car (reverse my_list))))))

(defun add1(my_list)
	(if (= (mod (length my_list) 2) 0) my_list
		(append (if (= (length my_list) 1) (+ (car my_list) 1)
			 (car my_list)
				(add1 (remove 1(remove (length my_list) my_list)))
				(car (reverse my_list))))))

;; Let's give it another shot
(defun add1(my_list)
	(if (= (mod (length my_list) 2) 0) my_list
		(cons (if (= (length my_list) 1) (+ (car my_list) 1)
			 (cons (car my_list)
				(add1 (cdr (reverse ( cdr (reverse my_list)))))))
				(car (reverse my_list)))))

(defun compare(list1 list2)
	(if (and (eq list1 '()) (eq list2 '()))
		0
		(if (eq (car list1) '())	
			1 
			(if (eq (car list2) '())
				-1
				(compare (cdr list1) (cdr list2))
			)
		)
	))





















