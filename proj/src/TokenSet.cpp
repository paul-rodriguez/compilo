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
		.addToken(Token::UNLESS)

