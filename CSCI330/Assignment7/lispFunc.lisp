(defun expr () 
	(write-line "Enter <expr>")
	(term)
	(loop while (equal nextToken ADD_OP) do
      (lex)
      (term)
  	)
  	(write-line "Exit <expr>")
)

(defun term ()
	(write-line "Enter <term")
	(factor)
	(loop while (equal nextToken MULT_OP) do 
		(lex)
		(factor)
	)
	(write-line "Exit <term>")
)


Question 1: The unambiguous grammar

<expr> -> <expr> + <term>
          | <term>
<term> -> <term> * <factor>
          | <factor>
<factor> -> (<expr>)
            | <id>
            | <int>
<id> -> <letter> {<letter> | <digit>}(9)
<int> -> <digit> {<digit>}(9)
<letter> -> a | b | ... | y | z
            | A | B | ... | Y | Z
<digit> -> 1 | 2 | ... | 9