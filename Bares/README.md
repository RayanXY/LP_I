## Bares ##

### What is it? ###

Bares is a program that reads a file with expressions (one expression for each line) and returns the result of each expression or an error and the column where it is if the expression is not well formed.

### How does it work? ###

The program read a file with expressions, build a string with the content of the expression and checks if theres any error with the expression using the PARSER methods (parser.cpp/parser.h), the method can found the following errors:

`UNEXPECTED_END_OF_EXPRESSION` > Happens when nothing is found on the line

`ILL_FORMED_INTEGER` > Happens when a term is not well formed

`MISSING_TERM` > Happens when a term is expected but not found

`MISSING_CLOSING_PARENTHESIS` > Happens when the expression has a "(" but not a ")"

`EXTRANEOUS_SYMBOL` > Happens when the following part of the string is different of the expected

While checking if the expression is fine, the parsing method make a vector of Tokens (token.h) with the terms and operators of the expression, preparing it for the bares method.

After checking the expression, if it is everything right, is time to calculate the result, it is made by the bares method (bares.cpp) it takes the vector of tokens made by the parsing process, and converts the expression for the infix ordenation to the postfix,(infix_to_postfix function). And then, with the postfix expression, the result is calculated (evaluate_postfix function), while the postfix is calculated it can throw a "Division by zero error", that happens when the operators "/" and "%" has 0(zero) as the second operand.
Finally if it is everythin alright, the program prints on screen the expression and its result:

 `>>> Expression = Result`

 P.S: On `INTEGER_OUT_RANGE` error has a bug.

### Compiling ###

To compile the program use the following code:

`make`

### Setting the expressions ###

To set your expressions you must edit the `expressions.txt` file in the `data/` folder

**Exemple:**
```
2+7 -4  + 22
40 * 7 / (9 - 9)
2^2^2
```

### Running ###

To run the program use the following code:

`./build/bares ./data/expressions.txt`

This program was made by ANDERSON CAIO and RAYAN AVELINO. ⒸAll rights reserved.