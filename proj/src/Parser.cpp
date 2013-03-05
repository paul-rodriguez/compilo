#include "Parser.hpp"
#include "TokenSet.hpp"
#include "Scanner.hpp"

#include<stdexcept>

Parser::Parser(Scanner& scanner):
	scanner_(scanner),
	tok_(NULL)
{
	// TODO Auto-generated constructor stub

}

Parser::~Parser()
{
	// TODO Auto-generated destructor stub
}

void Parser::program()
{
	program_f();
	program_v();
}

void Parser::program_v()
{
	nextToken();
	if(isToken(Token::END))
	{
		end();
	}
	else
	{
		program_f();
		program_v();
	}
}

void Parser::program_f()
{
	nextToken();
	if(isToken(Token::SUB))
	{
		function();
	}
	else if(isToken(TokenSet::f_instruction))
	{
		instruction();
	}
	else
	{
		error();
	}
}

void Parser::function()
{
	match(Token::SUB);
	match(Token::IDENTIFIER);
	function_argument();
	match(Token::LBRACE);
	instruction_list();
	match(Token::RBRACE);
}


void Parser::function_argument()
{
	nextToken();
	if(isToken(Token::LPAR))
	{
		match();
		argument_list();
		match(Token::RPAR);
	}
}

void Parser::argument_list()
{
	nextToken();
	if(isToken(Token::VAR))
	{
		match();
		argument_list_v();
	}
}

void Parser::argument_list_v()
{
	nextToken();
	if(isToken(Token::COMMA))
	{
		match();
		match(Token::VAR);
		argument_list_v();
	}
}

void Parser::instruction_list()
{
	nextToken();
	if(isToken(TokenSet::f_instruction))
	{
		instruction();
		instruction_list();
	}
}

void Parser::instruction()
{
	nextToken();
	if(isToken(Token::RETURN))
	{
		match();
		expression();
		instruction_f();
		match(Token::SEMICOLON);
	}
	else if(isToken(Token::LBRACE))
	{
		match();
		instruction_list();
		match(Token::RBRACE);
	}
	else if(isToken(TokenSet::f_condition))
	{
		condition();
		expression();
		match(Token::LBRACE);
		instruction_list();
		match(Token::RBRACE);
		condition_end();
	}
	else if(isToken(TokenSet::f_expression))
	{
		expression();
		instruction_f();
		match(Token::SEMICOLON);
	}
	else
	{
		error();
	}
}

void Parser::instruction_f()
{
	nextToken();
	if(isToken(TokenSet::f_condition))
	{
		condition();
		expression();
	}
}

void Parser::condition()
{
	nextToken();
	if(isToken(Token::IF))
	{
		match();
	}
	else if(isToken(Token::UNLESS))
	{
		match();
	}
	else
	{
		error();
	}
}

void Parser::condition_end()
{
	nextToken();
	if(isToken(Token::ELSE))
	{
		match();
		match(Token::LBRACE);
		instruction_list();
		match(Token::RBRACE);
	}
	else if (isToken(Token::ELSIF))
	{
		match();
		expression();
		match(Token::LBRACE);
		instruction_list();
		match(Token::RBRACE);
		condition_end();
	}
}

void Parser::expression()
{
	expression_two();
	expression_v();
}

void Parser::expression_v()
{
	nextToken();
	if(isToken(Token::ASSIGN_MARK))
	{
		match();
		expression_two();
		expression_v();
	}
}

void Parser::expression_two()
{
	expression_three();
	expression_two_v();
}

void Parser::expression_two_v()
{
	nextToken();
	if(isToken(Token::LAZY_OR))
	{
		match();
		expression_three();
		expression_two_v();
	}
}

void Parser::expression_three()
{
	expression_four();
	expression_three_v();
}

void Parser::expression_three_v()
{
	nextToken();
	if(isToken(Token::LAZY_AND))
	{
		match();
		expression_four();
		expression_three_v();
	}
}

void Parser::expression_four()
{
	expression_five();
	expression_four_v();
}

void Parser::expression_four_v()
{
	nextToken();
	if(isToken(TokenSet::f_expression_four_v))
	{
		match();
		expression_five();
	}
}

void Parser::expression_five()
{
	expression_six();
	expression_five_v();
}

void Parser::expression_five_v()
{
	nextToken();
	if(isToken(TokenSet::f_expression_five_v))
	{
		match();
		expression_six();
	}
}

void Parser::expression_six()
{
	expression_seven();
	expression_six_v();
}

void Parser::expression_six_v()
{
	nextToken();
	if(isToken(TokenSet::f_expression_six_v))
	{
		match();
		expression_seven();
		expression_six_v();
	}
}

void Parser::expression_seven()
{
	expression_eight();
	expression_seven_v();
}

void Parser::expression_seven_v()
{
	nextToken();
	if (isToken(TokenSet::f_expression_seven_v))
	{
		match();
		expression_eight();
		expression_seven_v();
	}
}

void Parser::expression_eight()
{
	expression_eight_v();
	expression_nine();
}

void Parser::expression_eight_v()
{
	nextToken();
	if(isToken(TokenSet::f_expression_eight_v))
	{
		match();
		expression_eight_v();
	}
}

void Parser::expression_nine()
{
	nextToken();
	if (isToken(Token::LPAR))
	{
		match();
		expression();
		match(Token::RPAR);
	}
	else if (isToken(TokenSet::f_simple_expression))
	{
		simple_expression();
	}
	else
	{
		error();
	}
}

void Parser::simple_expression()
{
	nextToken();
	if (isToken(Token::CALL_MARK))
	{
		function_call();
	}
	else if (isToken(Token::INTEGER))
	{
		match(Token::INTEGER);
	}
	else if (isToken(Token::FLOAT))
	{
		match(Token::FLOAT);
	}
	else if (isToken(Token::STRING))
	{
		match(Token::STRING);
	}
	else if (isToken(Token::VAR))
	{
		match(Token::VAR);
	}
	else
	{
		error();
	}
}

void Parser::function_call()
{
	match(Token::CALL_MARK);
	match(Token::IDENTIFIER);
	match(Token::LPAR);
	argument_call_list();
	match(Token::RPAR);
}

void Parser::argument_call_list()
{
	nextToken();
	if (isToken(TokenSet::f_expression))
	{
		expression();
		argument_call_list_v();
	}
}

void Parser::argument_call_list_v()
{
	nextToken();
	if (isToken(Token::COMMA))
	{
		match();
		expression();
		argument_call_list_v();
	}
}

void Parser::end()
{

}

void Parser::run()
{
	program();
//	do
//	{
//		nextToken();
//	}
//	while(tok().id() != Token::END);
}

void Parser::match()
{
	delete tok_;
	tok_ = NULL;
}

void Parser::match(Token::TokenID id)
{
	nextToken();
	if(isToken(id))
	{
		//TODO store token info

		match();
	}
	else
	{
		error();
	}
}

void Parser::match(const TokenSet& set)
{
	nextToken();
	if (isToken(set))
	{
		match();
	}
	else
	{
		error();
	}
}

void Parser::error()
{
	throw runtime_error("Syntax error");
}


bool Parser::isToken(Token::TokenID id) const
{
	return (tok().id() == id);
}

bool Parser::isToken(const TokenSet& set) const
{
	return (set.contains(tok()));
}

void Parser::nextToken()
{
	if(tok_ == NULL)
	{
		bool space = true;
		while(space)
		{
			setTok(*(new Token(scanner().nextToken())));
			if(tok().id() == Token::SPACE)
			{
				delete tok_;
			}
			else
			{
				space = false;
			}
		}
	}
}

Scanner& Parser::scanner() const { return scanner_; }
const Token& Parser::tok() const { return *tok_; }
void Parser::setTok(const Token& tok) { tok_ = &tok; }