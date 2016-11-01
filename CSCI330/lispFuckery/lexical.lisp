;; Global Variables
(defparameter charClass nil)
;;(defparameter lexeme (string ""))
(defparameter lexeme (make-array 0
                                        :element-type 'character
                                        :fill-pointer 0
                                        :adjustable t))
(defparameter nextChar "")
(defparameter lexlen (length lexeme))
(defparameter token nil)
(defparameter nextToken nil)
(defparameter file (open "./tests.txt"))

;;Character Classes
(defvar LETTER 4)
(defvar DIGIT 1)
(defvar UNKNOWN 2)
(defvar EOF 3)

;; Tokens
(defvar INT_LIT 10)
(defvar IDENT 11)
(defvar ADD_OP 12)
(defvar MULT_OP 13)
(defvar LEFT_PAREN 14)
(defvar RIGHT_PAREN 15)

;; We need the following functions: lookup, addChar, getChar, getNoneBlank, and lex
(defun lookup (character)
  (format t "Lookup was called ~%")
  (case character
    ( #\( ;; Check for left parenthesis
      (addChar)
      (setq nextToken LEFT_PAREN )
    )
    ( #\) ;; Check for right parenthesis
      (addChar)
      (setq nextToken RIGHT_PAREN )
    )
    ( #\+ ;; Check for plus
      (addChar)
      (setq nextToken ADD_OP)
    )
    ( #\* ;; Check for multiply
      (addChar)
      (setq nextToken MULT_OP)
    )
    (t ;; Otherwise
      (addChar)
      (setq nextToken EOF)
    )
  )

  nextToken
)

(defun addChar () ;;Good
(format t "addChar was called ~%")

  (if (<= (length lexeme) 98)

    ;; Append to character to lexeme
    (vector-push-extend nextChar lexeme)
    ;; Otherwise print ERROR
    (format t "Error - Lexeme is too long.")
  )

)

(defun getChar () ;;Good
  (format t "getChar was called ~%")
  (if  (not (equal nil ( setq nextChar (read-char file NIL NIL))) )
    ;;(write  (format t "[GETCHAR FUNC] NextCHAR IS CURRENTLY: ~a" (alpha-char-p nextChar)))
    (if (equal T (alpha-char-p nextChar)) ;;is alpha stuff is true
        (setq charClass LETTER )
        (if (not (equal nil (digit-char-p nextChar)) ) ;;is digit stuff is true
            (setq charClass DIGIT)
            (setq charClass UNKNOWN)
        )
    )
    (setq charClass EOF)
  )
)

(defun getNonBlank () ;;Good
(format t "getNonBlank was called ~%")

  (loop while (or (equal nextChar #\Space) (equal nextChar #\Newline)) do
      (format t "CURRENT CHAR IS: ~a ~%" nextChar)
      (getChar)
  )
)


(defun EOFCASE ()
  ;;(format t "EOF WAS CALLED ~%")
  (setq nextToken EOF)
  (concatenate 'string lexeme "EOF")
)

(defun UNKNOWNCASE ()
  ;;(format t "UNKNOWN WAS CALLED ~%")
  (lookup nextChar)
  (getChar)
)


(defun DIGITCASE ()
;;(format t "DIGIT WAS CALLED ~%")
(addChar)
(getChar)
(loop while (equal charClass DIGIT) do
            (addChar)
            (getChar)
)
(setq nextToken INT_LIT))

(defun LETTERCASE ()
  ;;(format t "LETTER WAS CALLED ~%")
  (addChar)
  (getChar)
  (loop while (or (equal charClass LETTER) (equal charClass DIGIT) ) do
            ;;(format t "CURRENT CHAR CLASS IS: ~a ~%" charClass)
            (addChar)
            (getChar)
   )
  (setq nextToken IDENT)
)


(defun lex ()
;;(format t "Lex was called ~%")
(defparameter lexeme (make-array 0 :element-type 'character :fill-pointer 0 :adjustable t ))
(getNonBlank)
;;(write "CHECKING CHAR CLASS")
;;(write charClass)
(case charClass
(4 (LETTERCASE))
(1 (DIGITCASE))
(2 (UNKNOWNCASE))
(3 (EOFCASE)))

(write  (format t "Next token is: ~a , Next lexeme is: ~a ~%" nextToken lexeme))

;;nextToken
)

(getChar)
;; Main Code
(loop while (not (equal nextToken EOF)) do
  (lex)
)
