/**
 * @file parser.h
 * @authors Anderson Caio & Rayan Avelino
 * @date 23/05/2017
 */
#ifndef _PARSER_H_
#define _PARSER_H_

#include <iostream> 
#include <iterator> 
#include <vector>   
#include <sstream>  
#include "token.h"  

class Parser{

    public:
        /// This class represents the result of the parsing operation.
        struct ParserResult{
            typedef size_t size_type; //<! Used for column location.
            /// List of possible syntax errors.
            enum code_t {
                    PARSER_OK = 0,
                    UNEXPECTED_END_OF_EXPRESSION,
                    ILL_FORMED_INTEGER,
                    MISSING_TERM,
                    MISSING_CLOSING_PARENTHESIS,
                    EXTRANEOUS_SYMBOL,
                    INTEGER_OUT_OF_RANGE
            };
            code_t type;      //!< Error code.
            size_type at_col; //!< Guarda a coluna do erro.

            explicit ParserResult( code_t type_=PARSER_OK , size_type col_=0u )
                    : type{ type_ }
                    , at_col{ col_ }
            { /* empty */ }
        };

        typedef short int required_int_type;
        typedef long long int input_int_type;

        ParserResult parse( std::string e_ );
        std::vector< Token > get_tokens( void ) const;

        /// Constutor default.
        Parser() = default;
        ~Parser() = default;
        /// Desligar cópia e atribuição.
        Parser( const Parser & ) = delete;              //!< Construtor cópia.
        Parser & operator=( const Parser & ) = delete;  //!< Atribuição.

    private:
        static constexpr bool SUCCESS{ true };
        static constexpr bool FAILURE{ false };

        /// Terminal symbols table
        enum class terminal_symbol_t{ 
            TS_PLUS,	        //!< "+"
            TS_MINUS,	        //!< "-"
            TS_DIV,             //!< "/"
            TS_MULT,            //!< "*"
            TS_EXPO,            //!< "^"
            TS_MOD,             //!< "%"
            TS_ZERO,            //!< "0"
            TS_NON_ZERO_DIGIT,  //!< "1"->"9"
            TS_OPENING_SCOPE,   //!< "("
            TS_CLOSING_SCOPE,   //!< ")"
            TS_WS,              //!< white-space
            TS_TAB,             //!< tab
            TS_EOS,             //!< End Of String
            TS_INVALID	        //!< invalid token
        };

        std::string expr;                   //!< The expression to be parsed
        std::string::iterator it_curr_symb; //!< Pointer to the current char inside the expression.
        std::vector< Token > token_list;    //!< Resulting list of tokens extracted from the expression.

        terminal_symbol_t lexer( char ) const;
        std::string token_str( terminal_symbol_t s_ ) const;

        /// Support methods.
        void next_symbol( void );                   //!< Advances iterator to the next char in the expression.
        bool peek( terminal_symbol_t s_ ) const;    //!< Peeks the current character.
        bool accept( terminal_symbol_t s_ );        //!< Tries to accept the requested symbol.
        bool expect( terminal_symbol_t );           //!< Skips any WS/Tab and tries to accept the requested symbol.
        void skip_ws( void );                       //!< Skips any WS/Tab ans stops at the next character.
        bool end_input( void ) const;               //!< Checks whether we reached the end of the expression string.
        input_int_type str_to_int( std::string );   //!< Converts a string into an integer.

        /// NTS methods.
        ParserResult expression();                  //!< Validates a expression
        ParserResult term();                        //!< Validates a term
        ParserResult integer();                     //!< Validates a integer
        ParserResult natural_number();              //!< Validates a natural number

        /// Terminal methods - must return bool
        bool digit_excl_zero();
        bool digit();   

};
#endif