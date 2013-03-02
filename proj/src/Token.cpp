#include "Token.hpp"

Token::Token(TokenID id, string str) :
	RuleElement(),
	id_(id),
	value_(str)
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

bool Token::isLast() const
{
	return ((this->id()) == Token::END);
}

Token::TokenID Token::id() const
{
	return id_;
}

const string& Token::value() const
{
	return value_;
}

ostream& operator<<(ostream& out, const Token& t)
{
	if (t.id() == Token::VAR)
	{
		out << string("VAR " + t.value()).c_str();
	}
	else if (t.id() == Token::IDENTIFIER)
	{
		out << string("IDENTIFIER " + t.value()).c_str();
	}
	else if (t.id() == Token::INTEGER)
	{
		out << string("INTEGER " + t.value()).c_str();
	}
	else if (t.id() == Token::FLOAT)
	{
		out << string("FLOAT " + t.value()).c_str();
	}
	else if (t.id() == Token::STRING)
	{
		out << string("STRING " + t.value()).c_str();
	}
	else if (t.id() == Token::SPACE)
	{
		out << "SPACE";
	}
	else if (t.id() == Token::COMMENT)
	{
		out << "COMMENT";
	}
	else if (t.id() == Token::LPAR)
	{
		out << "LPAR";
	}
	else if (t.id() == Token::RPAR)
	{
		out << "RPAR";
	}
	else if (t.id() == Token::LBRACE)
	{
		out << "LBRACE";
	}
	else if (t.id() == Token::RBRACE)
	{
		out << "RBRACE";
	}
	else if (t.id() == Token::SEMICOLON)
	{
		out << "SEMICOLON";
	}
	else if (t.id() == Token::CALL_MARK)
	{
		out << "CALL_MARK";
	}
	else if (t.id() == Token::PLUS)
	{
		out << "PLUS";
	}
	else if (t.id() == Token::MINUS)
	{
		out << "MINUS";
	}
	else if (t.id() == Token::TIMES)
	{
		out << "TIMES";
	}
	else if (t.id() == Token::DIVIDE)
	{
		out << "DIVIDE";
	}
	else if (t.id() == Token::NOT)
	{
		out << "NOT";
	}
	else if (t.id() == Token::NOTLETTERS)
	{
		out << "NOTLETTERS";
	}
	else if (t.id() == Token::LAZY_AND)
	{
		out << "LAZY_AND";
	}
	else if (t.id() == Token::LAZY_OR)
	{
		out << "LAZY_OR";
	}
	else if (t.id() == Token::EQUALS)
	{
		out << "EQUALS";
	}
	else if (t.id() == Token::EQ)
	{
		out << "EQ";
	}
	else if (t.id() == Token::DIFFERENT)
	{
		out << "DIFFERENT";
	}
	else if (t.id() == Token::NE)
	{
		out << "NE";
	}
	else if (t.id() == Token::LOWER)
	{
		out << "LOWER";
	}
	else if (t.id() == Token::LT)
	{
		out << "LT";
	}
	else if (t.id() == Token::GREATER)
	{
		out << "GREATER";
	}
	else if (t.id() == Token::GT)
	{
		out << "GT";
	}
	else if (t.id() == Token::LOWER_EQUALS)
	{
		out << "LOWER_EQUALS";
	}
	else if (t.id() == Token::LE)
	{
		out << "LE";
	}
	else if (t.id() == Token::GREATER_EQUALS)
	{
		out << "GREATER_EQUALS";
	}
	else if (t.id() == Token::GE)
	{
		out << "GE";
	}
	else if (t.id() == Token::COMMA)
	{
		out << "COMMA";
	}
	else if (t.id() == Token::CONCAT_MARK)
	{
		out << "CONCAT_MARK";
	}
	else if (t.id() == Token::ASSIGN_MARK)
	{
		out << "ASSIGN_MARK";
	}
	else if (t.id() == Token::SUB)
	{
		out << "SUB";
	}
	else if (t.id() == Token::IF)
	{
		out << "IF";
	}
	else if (t.id() == Token::ELSE)
	{
		out << "ELSE";
	}
	else if (t.id() == Token::ELSEIF)
	{
		out << "ELSEIF";
	}
	else if (t.id() == Token::UNLESS)
	{
		out << "UNLESS";
	}
	else if (t.id() == Token::RETURN)
	{
		out << "RETURN";
	}
	else if (t.id() == Token::DEFINED)
	{
		out << "DEFINED";
	}
	else if (t.id() == Token::INT)
	{
		out << "INT";
	}
	else if (t.id() == Token::LENGTH)
	{
		out << "LENGTH";
	}
	else if (t.id() == Token::PRINT)
	{
		out << "PRINT";
	}
	else if (t.id() == Token::SCALAR)
	{
		out << "SCALAR";
	}
	else if (t.id() == Token::SUBSTR)
	{
		out << "SUBSTR";
	}
	return out;
}
