/**
 * @file bares.h
 * @authors Anderson Caio & Rayan Avelino
 * @date 23/05/2017
 */
#ifndef _BARES_H_
#define _BARES_H_

#include <iostream> 
#include <cassert>  
#include <stack>     
#include <cmath>     
#include <string>   
#include <stdexcept> 
#include "parser.h"
#include "token.h"

using value_type = long long int;

/**
 * Functions to help identify the operantor, operand and '(' & ')' symbol.
 * @param t_ The usually Tokens defined in 'token.h'.
 * @return T if is satified one of the conditions; F otherwise.
 */
bool is_operator( Token ); 
bool is_operand( Token );
bool is_opening_scope( Token );
bool is_closing_scope( Token );

/**
 * 
 */
//>For the "^" case
bool is_right_association( Token );

//>Gives the "priotity level" of a operator
int get_precedence( Token );

/** 
 * Funtion that determies which operator has higher precedence.
 * @param o1_ Operator defined in 'token.h'.
 * @param o2_ Operator defined in 'token.h'.
 * @return op1>=op2 If it is T; F otherwise or the special case.
 */
bool has_higher_precedence( Token o1_, Token o2_);

/**
 * Converts an expression in infix notation to an profix notstion.
 * @param infix_ The expression to be converted.
 * @return postifx_ The postix expression of infix_.
 */
std::vector<Token> infix_to_postfix( std::vector<Token> infix_ );

/**
 * Converts a string into an interger
 * @param input_tk_ The string to be converted.
 * @return value The interger
 */
Parser::input_int_type str_to_int( Token input_tk_ );

/**
 * Peforms the operation according to the operator
 * @param l_ The left operand of the expression.
 * @param r_ The right operand of the expression.
 * @param opr Operator of the expression.
 * @return result The result of the expression.
 */
value_type execute_operator( value_type l_, value_type r_, std::string opr);

//>Process the postfix expression and returns its result
value_type evaluate_postfix( std::vector<Token> );

#endif