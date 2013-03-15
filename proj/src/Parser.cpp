#include "Parser.hpp"
#include "TokenSet.hpp"
#include "Scanner.hpp"
#include "CodeGenerator.hpp"

#include <stdexcept>

Parser::Parser(Scanner& scanner, CodeGenerator& cg):
	scanner_(scanner),
	cg_(cg),
	tok_(NULL)
{
	;
}

Parser::~Parser()
{
	;
}

void Parser::program()
{
	cg().program_header();
	program_f();
	program_v();
	cg().endProgram();
}

void Parser::program_v()
{
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
	cg().function(oldTokValue());
	function_argument();
	match(Token::LBRACE);
	instruction_list();
	match(Token::RBRACE);
	cg().endFunction();
}


void Parser::function_argument()
{
	if(isToken(Token::LPAR))
	{
		match();
		argument_list();
		match(Token::RPAR);
	}
}

void Parser::argument_list()
{
	if(isToken(Token::VAR))
	{
		match();
		cg().functionArg(oldTokValue());
		argument_list_v();
	}
}

void Parser::argument_list_v()
{
	if(isToken(Token::COMMA))
	{
		match();
		match(Token::VAR);
		cg().functionArg(oldTokValue());
		argument_list_v();
	}
}

void Parser::instruction_list()
{
	if(isToken(TokenSet::f_instruction))
	{
		instruction();
		instruction_list();
	}
}

void Parser::instruction()
{
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
	if(isToken(TokenSet::f_condition))
	{
		condition();
		expression();
	}
}

void Parser::condition()
{
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
	if(isToken(Token::ASSIGN_MARK))
	{
		match();
		expression_two();
		expression_v();
		cg().assign_mark();
	}
}

void Parser::expression_two()
{
	expression_three();
	expression_two_v();
}

void Parser::expression_two_v()
{
	if(isToken(Token::LAZY_OR))
	{
		match();
		expression_three();
		cg().lazy_or();
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
	if(isToken(Token::LAZY_AND))
	{
		match();
		expression_four();
		cg().lazy_and();
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
	if(isToken(TokenSet::f_expression_four_v))
	{
		match();
		expression_five();
		if (oldTok().id() == Token::DIFFERENT)
		{
			cg().different();
		}
		else if (oldTok().id() == Token::EQ)
		{
			cg().eq();
		}
		else if (oldTok().id() == Token::EQUALS)
		{
			cg().equals();
		}
		else
		{
			cg().ne();
		}
	}
}

void Parser::expression_five()
{
	expression_six();
	expression_five_v();
}

void Parser::expression_five_v()
{
	if(isToken(TokenSet::f_expression_five_v))
	{
		match();
		expression_six();
		if (oldTok().id() == Token::GREATER)
		{
			cg().greater();
		}
		else if (oldTok().id() == Token::GREATER_EQUALS)
		{
			cg().greater_equals();
		}
		else if (oldTok().id() == Token::GE)
		{
			cg().ge();
		}
		else if (oldTok().id() == Token::GT)
		{
			cg().gt();
		}
		else if (oldTok().id() == Token::LOWER)
		{
			cg().lower();
		}
		else if (oldTok().id() == Token::LOWER_EQUALS)
		{
			cg().lower_equals();
		}
		else if (oldTok().id() == Token::LT)
		{
			cg().lt();
		}
		else
		{
			cg().le();
		}
	}
}

void Parser::expression_six()
{
	expression_seven();
	expression_six_v();
}

void Parser::expression_six_v()
{
	if(isToken(TokenSet::f_expression_six_v))
	{
		match();
		expression_seven();
		if (oldTok().id() == Token::PLUS)
		{
			cg().plus();
		}
		else if (oldTok().id() == Token::MINUS)
		{
			cg().minus();
		}
		else
		{
			cg().concat_mark();
		}
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
	if (isToken(TokenSet::f_expression_seven_v))
	{
		match();
		expression_eight();
		expression_seven_v();
	}
}

void Parser::expression_eight()
{
	if(isToken(TokenSet::f_expression_eight_v))
	{
		match();
		expression_eight();
		if (oldTok().id() == Token::PLUS)
		{
			cg().unary_plus();
		}
		else if (oldTok().id() == Token::MINUS)
		{
			cg().unary_minus();
		}
		else
		{
			cg().Not();
		}
	}
	else if(isToken(TokenSet::f_expression_nine))
	{
		expression_nine();
	}
	else
	{
		error();
	}
}

void Parser::expression_nine()
{
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
	if (isToken(Token::CALL_MARK))
	{
		function_call();
	}
	else if (isToken(Token::INTEGER))
	{
		match(Token::INTEGER);
		cg().integer(oldTokValue());
	}
	else if (isToken(Token::FLOAT))
	{
		match(Token::FLOAT);
		cg().Float(oldTokValue());
	}
	else if (isToken(Token::STRING))
	{
		match(Token::STRING);
		cg().string(oldTokValue());
	}
	else if (isToken(Token::VAR))
	{
		match(Token::VAR);
		cg().var(oldTokValue());
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
	cg().functionCall(oldTokValue());
	match(Token::LPAR);
	argument_call_list();
	match(Token::RPAR);
}

void Parser::argument_call_list()
{
	if (isToken(TokenSet::f_expression))
	{
		expression();
		argument_call_list_v();
	}
}

void Parser::argument_call_list_v()
{
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
	nextToken();
	program();
}

void Parser::match()
{
	delete oldTok_;
	setOldTok(tok());
	nextToken();
}

void Parser::match(Token::TokenID id)
{
	if(isToken(id))
	{
		match();
	}
	else
	{
		error();
	}
}

void Parser::match(const TokenSet& set)
{
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
	throw runtime_error("Syntax error "+tok().str());
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
	bool skip = true;
	while(skip)
	{
		setTok(*(new Token(scanner().nextToken())));
		if(tok().id() == Token::SPACE || tok().id() == Token::COMMENT)
		{
			delete tok_;
		}
		else
		{
			skip = false;
		}
	}
}


const Token& Parser::oldTok() const { return *oldTok_; }
void Parser::setOldTok(const Token& oldTok) { oldTok_ = &oldTok; }
const std::string& Parser::oldTokValue() const { return oldTok().value(); }
Scanner& Parser::scanner() const { return scanner_; }
CodeGenerator& Parser::cg() const { return cg_; }
const Token& Parser::tok() const { return *tok_; }
void Parser::setTok(const Token& tok) { tok_ = &tok; }
