#include "TokenSet.hpp"

TokenSet::TokenSet()
{
	// TODO Auto-generated constructor stub

}

TokenSet::~TokenSet()
{
	// TODO Auto-generated destructor stub
}

bool TokenSet::contains(const Token& t) const
{
	return (tokens_.count(t.id()) >= 1);
}

TokenSet& TokenSet::addToken(Token::TokenID t)
{
	tokens_.insert(t);
	return *this;
}

const TokenSet TokenSet::f_instruction = TokenSet()
		.addToken(Token::RETURN)
		.addToken(Token::LBRACE)
		.addToken(Token::LPAR)
		.addToken(Token::INTEGER)
		.addToken(Token::FLOAT)
		.addToken(Token::STRING)
		.addToken(Token::VAR)
		.addToken(Token::CALL_MARK)
		.addToken(Token::IF)
		.addToken(Token::UNLESS)
		.addToken(Token::NOT)
		.addToken(Token::PLUS)
		.addToken(Token::MINUS);

const TokenSet TokenSet::f_expression = TokenSet()
		.addToken(Token::LPAR)
		.addToken(Token::INTEGER)
		.addToken(Token::FLOAT)
		.addToken(Token::STRING)
		.addToken(Token::VAR)
		.addToken(Token::CALL_MARK)
		.addToken(Token::NOT)
		.addToken(Token::PLUS)
		.addToken(Token::MINUS);

const TokenSet TokenSet::f_condition = TokenSet()
		.addToken(Token::IF)
		.addToken(Token::UNLESS);

const TokenSet TokenSet::f_expression_four_v = TokenSet()
		.addToken(Token::DIFFERENT)
		.addToken(Token::EQ)
		.addToken(Token::EQUALS)
		.addToken(Token::NE);

const TokenSet TokenSet::f_expression_five_v = TokenSet()
		.addToken(Token::GE)
		.addToken(Token::GREATER)
		.addToken(Token::GREATER_EQUALS)
		.addToken(Token::GT)
		.addToken(Token::LE)
		.addToken(Token::LOWER)
		.addToken(Token::LOWER_EQUALS)
		.addToken(Token::LT);

const TokenSet TokenSet::f_expression_six_v = TokenSet()
		.addToken(Token::PLUS)
		.addToken(Token::MINUS)
		.addToken(Token::CONCAT_MARK);

const TokenSet TokenSet::f_expression_seven_v = TokenSet()
		.addToken(Token::TIMES)
		.addToken(Token::DIVIDE);

const TokenSet TokenSet::f_expression_eight_v = TokenSet()
		.addToken(Token::NOT)
		.addToken(Token::PLUS)
		.addToken(Token::MINUS);

const TokenSet TokenSet::f_expression_nine = TokenSet()
		.addToken(Token::LPAR)
		.addToken(Token::CALL_MARK)
		.addToken(Token::INTEGER)
		.addToken(Token::FLOAT)
		.addToken(Token::STRING)
		.addToken(Token::VAR);

const TokenSet TokenSet::f_simple_expression = TokenSet()
		.addToken(Token::CALL_MARK)
		.addToken(Token::INTEGER)
		.addToken(Token::FLOAT)
		.addToken(Token::STRING)
		.addToken(Token::VAR);

