#include "Token.hpp"

Token::Token(TokenID id, string str) : id_(id), value_(str)
{
	;
}

Token::~Token()
{
	;
}

void Token::setId(TokenID id)
{
	id_ = id;
}

void Token::setValue(string value)
{
	value_ = value;
}

Token::TokenID Token::id() const
{
	return id_;
}

string Token::value() const
{
	return value_;
}







