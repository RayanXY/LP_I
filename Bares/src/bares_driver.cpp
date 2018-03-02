#include "../include/bares.h"
#include "../include/parser.h"
#include "../include/token.h"
#include <fstream>  //!< To open the file and get the lines

void print_msg( const Parser::ParserResult & result, std::string str ){
    std::string error_indicator( str.size()+1, ' ');

    error_indicator[result.at_col] = '^';
    switch ( result.type ){

        case Parser::ParserResult::UNEXPECTED_END_OF_EXPRESSION:
            std::cout << ">>> Unexpected end of input at column (" << result.at_col << ")!\n";
            break;
        case Parser::ParserResult::ILL_FORMED_INTEGER:
            std::cout << ">>> Ill formed integer at column (" << result.at_col << ")!\n";
            break;
        case Parser::ParserResult::MISSING_TERM:
            std::cout << ">>> Missing <term> at column (" << result.at_col << ")!\n";
            break;
        case Parser::ParserResult::EXTRANEOUS_SYMBOL:
            std::cout << ">>> Extraneous symbol after valid expression found at column (" << result.at_col << ")!\n";
            break;
        case Parser::ParserResult::MISSING_CLOSING_PARENTHESIS:
            std::cout << ">>> Missing closing parenthesis \")\" at column (" << result.at_col << ")!\n";
            break;
        case Parser::ParserResult::INTEGER_OUT_OF_RANGE:
            std::cout << ">>> Integer constant out of range beginning at column (" << result.at_col << ")!\n";
            break;
        default:
            std::cout << ">>> Unhandled error found!\n";
            break;
    }
    std::cout << "\"" << str << "\"\n";
    std::cout << " " << error_indicator << std::endl;

}

int main(int argc, char * argv[]){

	std::string express;
    auto num_of_expr = 1;

	std::ifstream file;
	file.open(argv[1]);
	Parser a;

	if(file.is_open()){

		while(getline(file, express)){

			auto presult = a.Parser::parse(express);
            std::cout << "Expression " << num_of_expr << ": \n";

			if ( presult.type != Parser::ParserResult::PARSER_OK ){ 
          		print_msg( presult, express );
          	}else{
				std::vector<Token> infix = a.Parser::get_tokens();
				std::vector<Token> postfix = infix_to_postfix(infix);
				auto exprresult = evaluate_postfix(postfix);
				std::cout << express << " = " << exprresult << "\n\n";
			}
            num_of_expr++;
		}

	}else{
		std::cout << "Missing open file\n";
	}

}