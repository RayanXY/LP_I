#include "../include/parser.h"
#include <iterator>
#include <algorithm>


/// Converts a valid character to the corresponding terminal symbol.
Parser::terminal_symbol_t  Parser::lexer( char c_ ) const{

    switch( c_ ){
        case '+':  return terminal_symbol_t::TS_PLUS;
        case '-':  return terminal_symbol_t::TS_MINUS;
        case '^':  return terminal_symbol_t::TS_EXPO;
        case '*':  return terminal_symbol_t::TS_MULT;
        case '/':  return terminal_symbol_t::TS_DIV;
        case '%':  return terminal_symbol_t::TS_MOD;
        case '(':  return terminal_symbol_t::TS_OPENING_SCOPE;
        case ')':  return terminal_symbol_t::TS_CLOSING_SCOPE;
        case ' ':  return terminal_symbol_t::TS_WS;
        case   9:  return terminal_symbol_t::TS_TAB;
        case '0':  return terminal_symbol_t::TS_ZERO;
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':  return terminal_symbol_t::TS_NON_ZERO_DIGIT;
        case '\0': return terminal_symbol_t::TS_EOS;            //!< end of string: the $ terminal symbol
    }
    return terminal_symbol_t::TS_INVALID;

}


/// Convert a terminal symbol into its corresponding string representation.
std::string Parser::token_str( terminal_symbol_t s_ ) const{

    switch( s_ ){
        case terminal_symbol_t::TS_PLUS         : return "+";
        case terminal_symbol_t::TS_MINUS        : return "-";
        case terminal_symbol_t::TS_EXPO         : return "^";
        case terminal_symbol_t::TS_MULT         : return "*";
        case terminal_symbol_t::TS_DIV          : return "/";
        case terminal_symbol_t::TS_MOD          : return "%";
        case terminal_symbol_t::TS_OPENING_SCOPE: return "(";
        case terminal_symbol_t::TS_CLOSING_SCOPE: return ")";
        case terminal_symbol_t::TS_WS           : return " ";
        case terminal_symbol_t::TS_ZERO         : return "0";
        default                                 : return "X";
    }

}

/// Consumes a valid character from the expression being parsed.
void Parser::next_symbol( void ){
    /// Get a valid symbol for processing
    std::advance( it_curr_symb, 1 );
}

/// Verifies whether the current symbol is equal to the terminal symbol requested.
bool Parser::peek( terminal_symbol_t c_ ) const{
    return ( not end_input() and lexer( *it_curr_symb ) == c_ );
}

/// Tries to match the current character to a symbol passed as argument.
bool Parser::accept( terminal_symbol_t c_ ){

    if (peek( c_ )){
        next_symbol();
        return true;
    }
    return false;

}

/// Verify whether the next valid symbol is the one expected; if it is so, the method accepts it.
bool Parser::expect( terminal_symbol_t c_ ){
    /// Skip white spaces and tries to validate the following char
    skip_ws();
    return accept( c_ );
}

/// Ignores any white space or tabs in the expression until reach a valid symbol or end of input.
void Parser::skip_ws( void ){

    while ( not end_input() and
            ( lexer( *it_curr_symb ) == Parser::terminal_symbol_t::TS_WS  or
              lexer( *it_curr_symb ) == Parser::terminal_symbol_t::TS_TAB ) )
    {
        next_symbol();
    }

}

/// Checks whether we reached the end of the expression string.
bool Parser::end_input( void ) const{
    return it_curr_symb == expr.end();
}

/// Converts from string to integer.
Parser::input_int_type str_to_int( std::string input_str_ ){

    /// Creating input stream.
    std::istringstream iss( input_str_ );
    /// Resulting value.
    Parser::input_int_type value;
    iss >> value; // Ignore trailling white space.
    /// Check for error during convertion.
    if ( iss.fail() ){
        throw std::runtime_error( "str_to_int(): Erro, illegal integer format." );
    }
    return value;

}

Parser::ParserResult Parser::expression(){

    skip_ws();
    /// Validating a term
    auto result = term();

    while ( result.type == ParserResult::PARSER_OK  and not end_input() ){
    	/// If we get a "+"
        if ( expect( terminal_symbol_t::TS_PLUS ) ){
            token_list.push_back( Token( token_str(terminal_symbol_t::TS_PLUS), Token::token_t::OPERATOR) );
        }
        /// If we get a "-"
        else if ( expect( terminal_symbol_t::TS_MINUS ) ){
            token_list.push_back( Token(token_str(terminal_symbol_t::TS_MINUS), Token::token_t::OPERATOR) );
        }
        /// If we get a "^"
        else if ( expect( terminal_symbol_t::TS_EXPO ) ){
            token_list.push_back( Token(token_str(terminal_symbol_t::TS_EXPO), Token::token_t::OPERATOR) );
        }
        /// If we get a "*"
        else if ( expect( terminal_symbol_t::TS_MULT ) ){
            token_list.push_back( Token(token_str(terminal_symbol_t::TS_MULT), Token::token_t::OPERATOR) );
        }
        /// If we get a "/"
        else if ( expect( terminal_symbol_t::TS_DIV ) ){
            token_list.push_back( Token(token_str(terminal_symbol_t::TS_DIV), Token::token_t::OPERATOR) );
        }
        /// If we get a "%"
        else if ( expect( terminal_symbol_t::TS_MOD ) ){
            token_list.push_back( Token(token_str(terminal_symbol_t::TS_MOD), Token::token_t::OPERATOR) );
        }else{ 
            return result;
        }
        /// After getting the operator we expect another term
        result = term();
        if ( result.type != ParserResult::PARSER_OK and end_input() ){
            //If we don't get a term, return that a term is missing
            return Parser::ParserResult( ParserResult::MISSING_TERM, std::distance( expr.begin(),expr.end() ) );
        }
    }
    return result;

}

Parser::ParserResult Parser::term(){

    skip_ws();
    std::string::iterator begin_token =  it_curr_symb;
    Parser::ParserResult result = Parser::ParserResult( ParserResult::MISSING_TERM, std::distance( expr.begin(), it_curr_symb) );
    
    //If we don't get a term, return that a term is missing
    if ( end_input() ){
        return Parser::ParserResult( ParserResult::MISSING_TERM, std::distance (  expr.begin(), expr.end() ) );
    }   
    //For the case theres a opening scope "("
    else if( expect( terminal_symbol_t::TS_OPENING_SCOPE ) ){
        token_list.push_back( Token( token_str(terminal_symbol_t::TS_OPENING_SCOPE), Token::token_t::OPENING_SCOPE) );
        //Then we read the expression inside the parenthesis
        result = expression();
        
        if(result.type == ParserResult::PARSER_OK){
        	//if the expression has a "(" but not a ")" we return that the closing scope is missing
            if( not expect(terminal_symbol_t::TS_CLOSING_SCOPE) )
                return Parser::ParserResult( ParserResult::MISSING_CLOSING_PARENTHESIS, std::distance( expr.begin(), it_curr_symb) );
            //if we get a "(" its read and placed in the token list
            token_list.push_back( 
                           Token( token_str(terminal_symbol_t::TS_CLOSING_SCOPE), Token::token_t::CLOSING_SCOPE ) );
        }
    }else{
        result = integer();
        std::string num;
        num.insert( num.begin(), begin_token, it_curr_symb );

        if(result.type == ParserResult::PARSER_OK){
            std::string num;
            num.insert(num.begin(), begin_token, it_curr_symb);

            //Checking the size of the readed string
            input_int_type value = std::stoll( num );
            //If its inside the limits, its placed in the token list
            if( value <= std::numeric_limits< Parser::required_int_type >::max() 
                and value >= std::numeric_limits< Parser::required_int_type >::min() ){

                token_list.push_back( 
                           Token( num, Token::token_t::OPERAND ) );
            }else{
            	//if its out of limits, return that the term is out of range
                result.type = ParserResult::INTEGER_OUT_OF_RANGE;
                result.at_col = std::distance( expr.begin(), begin_token );
            }
        }
    }
    return result;

}

Parser::ParserResult Parser::integer(){

    if(lexer( *it_curr_symb ) ==  terminal_symbol_t::TS_ZERO )    {
        return ParserResult( ParserResult::PARSER_OK ); 
    }
    accept( terminal_symbol_t::TS_MINUS );
    return natural_number();

}

Parser::ParserResult Parser::natural_number(){

    if ( digit_excl_zero() ){
        while( digit() ) /* empty */ ;
        return ParserResult( ParserResult::PARSER_OK );
    }
    return ParserResult( ParserResult::ILL_FORMED_INTEGER, std::distance( expr.begin(), it_curr_symb ) );

}

bool Parser::digit_excl_zero(){
    return accept( terminal_symbol_t::TS_NON_ZERO_DIGIT );
}

bool Parser::digit(){
    return ( accept( terminal_symbol_t::TS_ZERO ) or
             accept( terminal_symbol_t::TS_NON_ZERO_DIGIT ) );
}

Parser::ParserResult Parser::parse( std::string e_ ){

    // We reset the parsing process each new expression.
    expr = e_;  // The expression in a string.
    it_curr_symb = expr.begin(); // Iterator to the 1st character in the expression.
    token_list.clear(); // Clear the list of tokens.

    // Default result.
    ParserResult result( ParserResult::PARSER_OK );

    skip_ws();
    if ( end_input() ){
        return ParserResult( ParserResult::UNEXPECTED_END_OF_EXPRESSION,
                std::distance( expr.begin(), it_curr_symb ) );
    }

    //Validating a expression
    result = expression();

    //Check if has anything remaining in the expression
    if ( result.type == ParserResult::PARSER_OK ){
        skip_ws();
        if ( not end_input() ){
            return ParserResult( ParserResult::EXTRANEOUS_SYMBOL, 
                    std::distance( expr.begin(), it_curr_symb ) );
        }
    }else{
        if(it_curr_symb == expr.begin()){
        	//if its anything else but a number
            return ParserResult( ParserResult::ILL_FORMED_INTEGER, 
                    std::distance( expr.begin(), it_curr_symb ) );
        }else if ( not end_input() ){
            return ParserResult( ParserResult::EXTRANEOUS_SYMBOL, 
                    std::distance( expr.begin(), it_curr_symb ) );
        }
    }
    return result;

}

/// Return the token list generated by the parsing process
std::vector< Token >
Parser::get_tokens( void ) const
{
    return token_list;
}