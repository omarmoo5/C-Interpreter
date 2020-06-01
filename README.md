# C-Interpreter
This project is a simple interpreter that executes instructions and prints the result of execution using C programming language.
## System Description:
* Accept a text file as source code and Checks if it exists
* Scan the line containing the variable name and the expression / value.
* Validates RHS & LHS of the equation.
* Evaluating the RHS.
* Inserting the variable name & it’s value into BST 
* After going through all the lines in source code, we copy the tree into heap. 
* In order traversal for BST was used in order to sort the variables by names.
* Heap sort Algorithm was used in order to sort the variables by values.

## User Manual:
* Create text file named src.txt  in the same directory containing the equations
* Form of Equations  is not restricted by spaces or -ve signs. Some valid expression examples:
> X = 12.5 <br />
> Z = X*Y/5 <br />
> K = 10.5+ (Z-2.5)/(X+Y) <br />
## Notes to avoid  : 
* Left hand side should contain only one variable.
* Invalid expressions example : 
> (x+y)/(3+1
* Invalid expression example : 
> Invalid Symbol , Missing (=).
## Output  will be printed twice as follows:
 * Sorted according to variable name
 * Sorted according to the variable value
