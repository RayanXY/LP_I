#include "../include/bares.h"

std::vector<Token> infix_to_postfix( std::vector<Token> infix_ ){

    /// Stores the postfix expression.
    std::vector<Token> postfix; //>>vector to return by the end of function
    /// Stack to help us convert the expression.
    std::stack< Token > s;

    /// Traverse the expression.
    for(auto tk : infix_){

        /// If its a operand, goes right into the postfix expression
        if (is_operand(tk)){ 						//!< 1 23 100, etc.
            postfix.push_back(tk);
        }
        /// If its a operator, goes into the auxiliary stack
        else if (is_operator(tk)){
            /** 
             * If its has a high priority than the others operator its stay in the top
             * else, pop all the operator with higher priority
             */
            while(not s.empty() and has_higher_precedence(s.top(), tk)){
                postfix.push_back(s.top());
                s.pop();
            }
            /// The incoming operator always goes into the stack.
            s.push(tk);
        }else if (is_opening_scope(tk)){ 			//!< "("
            s.push(tk);
        }
        else if (is_closing_scope(tk)){ 			//!< ")"
            /// Pop out all elements that are not '('.
            while(not s.empty() and not is_opening_scope(s.top())){
                postfix.push_back( s.top() ); 		//!< goes to the output.
                s.pop();
            }
            s.pop(); 								//!< Remove the '(' that was on the stack.
        }else{ 										//!< Anything else.
            /* Ignore this char */
        }

    }

    /// Pop out all the remaining operators in the stack.
    while(not s.empty()){
        postfix.push_back( s.top() );
        s.pop();
    }
    return postfix;

}

bool is_operator( Token t_ ){
    return t_.type == Token::token_t::OPERATOR;
}

bool is_operand( Token t_ ){
    return t_.type == Token::token_t::OPERAND;
}

bool is_opening_scope( Token t_ ){
    return t_.type == Token::token_t::OPENING_SCOPE;
}
bool is_closing_scope( Token t_ ){
    return t_.type == Token::token_t::CLOSING_SCOPE;
}

bool is_right_association( Token t_ ){
    return t_.value == "^";
}

int get_precedence( Token t_ ){

    if ( t_.value == "^" )    {
        return 3;
    }else if ( t_.value == "*" or t_.value ==   "/" or t_.value == "%" ){
        return 2;
    }else if ( t_.value == "+" or t_.value == "-" ){
        return 1;
    }else if ( t_.value == ")" ){
        return 0;
    }
    return 0;

}

/// Determines if the first operator has priority above the second
bool has_higher_precedence( Token op1, Token op2 ){

    auto p1 = get_precedence( op1 );
    auto p2 = get_precedence( op2 );

    /// special case: has the same precedence and is right association.
    if ( p1 == p2 and is_right_association( op1 ) ){
        return false;
    }
    return p1 >= p2 ;

}

/// Process made in class but adapted for token
Parser::input_int_type str_to_int( Token tk_ ){

    /// Creating input stream.
    std::istringstream iss( tk_.value );
    /// Resulting value.
    Parser::input_int_type value;
    iss >> value; 				//!< Ignore trailling white space.
    /// Check for error during convertion.
    if ( iss.fail() ){
        throw std::runtime_error( "str_to_int(): Erro, illegal integer format." );
    }
    return value;

}

value_type evaluate_postfix( std::vector<Token> postfix_ ){

    /// Stacking the operators
    std::stack< value_type > s;

    for( auto tk_ : postfix_ ){
        if ( is_operand( tk_ ) ){
            s.push( str_to_int(tk_) );
        }else if ( is_operator(tk_) ){
            // Recover the two operands in reverse order.
            auto x2 = s.top(); s.pop();
            auto x1 = s.top(); s.pop();

            auto result = execute_operator( x1, x2, tk_.value );

            s.push(result);
        }else{
            assert(false);
        }
    }
    return s.top();

}

value_type execute_operator( value_type n1, value_type n2, std::string opr ){

    value_type result(0);

    /// Ordenating by priority   
       if ( opr == "^"){
           result = static_cast<value_type>( pow( n1, n2 ) );
       }else if( opr == "*"){
            result =  n1 * n2;
       }else if( opr == "/"){
            if ( n2 == 0 ){
                /// Returns a error for division by zero
                std::cout << ">>> Error : Division by zero (Result = 0 by default)\n";
                /// Makes the result of expression equal to zero
                return 0;
            }
            result = n1/n2;
       }else if(opr == "%"){
            if ( n2 == 0 ){
                /// Returns a error for division by zero
                std::cout << ">>> Error : Division by zero> (Result = 0 by default)\n";
                /// Makes the result of expression equal to zero
                return 0;
            }
            result = n1%n2;
       }else if(opr == "-"){
            result =  n1 - n2;
       }else if(opr == "+"){
            result = n1 + n2;
       }
    return result;

}
