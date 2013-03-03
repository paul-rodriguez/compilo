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
	};
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
		match(Token::LPAR);
		argument_list();
		match(Token::RPAR);
	}
}

void Parser::argument_list()
{
	nextToken();
	if(isToken(Token::VAR))
	{
		match(Token::VAR);
		argument_list_v();
	}
}

void Parser::argument_list_v()
{
	nextToken();
	if(isToken(Token::COMMA))
	{
		match(Token::COMMA);
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
		match(Token::RETURN);
		expression();
		instruction_f();
		match(Token::SEMICOLON);
	}
	else if(isToken(Token::LBRACE))
	{
		match(Token::LBRACE);
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

void Parser::condition()
{
	nextToken();
	if(isToken(Token::IF))
	{
		match(Token::IF);
	}
	else if(isToken(Token::UNLESS))
	{
		match(Token::UNLESS);
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
		match(Token::ELSE);
		match(Token::LBRACE);
		instruction_list();
		match(Token::RBRACE);
	}
	else if (isToken(Token::ELSIF))
	{
		match(Token::ELSIF);
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
		match(Token::ASSIGN_MARK);
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
		match(Token::LAZY_OR);
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
		match(Token::LAZY_AND);
		expression_four();
		expression_three_v();
	}
}

void Parser::expression_four()
{

}

void Parser::instruction_f()
{
	if(isToken(TokenSet::f_condition))
	{
		condition();
		expression();
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

void Parser::match(Token::TokenID id)
{
	nextToken();
	if(isToken(id))
	{
		//TODO store token info


		delete tok_;
		tok_ = NULL;
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
