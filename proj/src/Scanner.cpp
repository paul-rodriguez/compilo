#include "Scanner.hpp"
#include <stdexcept>

Scanner::Scanner(char* fileName)
	: file(),
	  character(),
	  name(fileName),
	  token(),
	  size(0),
	  isIdentifier(false)
{
	;
}

Scanner::~Scanner()
{
	;
}

//TODO : error if unrecognised character (like " )

const Token& Scanner::nextToken()
{
	if (!file.is_open())
	{
		file.open(name.c_str(), ios::in);
		if (file.is_open())
		{
			nextCharacter();
		}
	}
	if (file.is_open())
	{
		if (!file.eof())
		{
			if (character == '$')
			{
				var();
			}
			else if (isDigit())
			{
				float_integer();
			}
			else if (character == '\'')
			{
				String();
			}
			else if (isSpace())
			{
				space();
			}
			else if (character == '#')
			{
				comment();
			}
			else if (character == '{')
			{
				token.setId(Token::LBRACE);
				nextCharacter();
			}
			else if (character == '}')
			{
				token.setId(Token::RBRACE);
				nextCharacter();
			}

			else if (character == '(')
			{
				token.setId(Token::LPAR);
				nextCharacter();
			}
			else if (character == ')')
			{
				token.setId(Token::RPAR);
				nextCharacter();
			}
			else if (character == ';')
			{
				token.setId(Token::SEMICOLON);
				nextCharacter();
			}
			else if (character == '&')
			{
				callMark_lazyAnd();
			}
			else if (character == '+')
			{
				token.setId(Token::PLUS);
				nextCharacter();
			}
			else if (character == '-')
			{
				token.setId(Token::MINUS);
				nextCharacter();
			}
			else if (character == '*')
			{
				token.setId(Token::TIMES);
				nextCharacter();
			}
			else if (character == '/')
			{
				token.setId(Token::DIVIDE);
				nextCharacter();
			}
			else if (character == '!')
			{
				different_not();
			}
			else if (character == 'n')
			{
				identifierStart();
				identifier_ne_notletters();
			}
			else if (character == '|')
			{
				lazyOr();
			}
			else if (character == '=')
			{
				assignMark_equals();
			}
			else if (character == 'e')
			{
				identifierStart();
				else_elseif_eq_identifier();
			}
			else if (character == '<')
			{
				lower_lowerEquals();
			}
			else if (character == 'l')
			{
				identifierStart();
				identifier_le_length_lt();
			}
			else if (character == '>')
			{
				greater_greaterEquals();
			}
			else if (character == 'g')
			{
				identifierStart();
				ge_gt_identifier();
			}
			else if (character == ',')
			{
				token.setId(Token::COMMA);
				nextCharacter();
			}
			else if (character == '.')
			{
				token.setId(Token::CONCAT_MARK);
				nextCharacter();
			}
			else if (character == 's')
			{
				identifierStart();
				identifier_scalar_sub_substr();
			}
			else if (character == 'i')
			{
				identifierStart();
				identifier_if_int();
			}
			else if (character == 'u')
			{
				identifierStart();
				identifier_unless();
			}
			else if (character == 'r')
			{
				identifierStart();
				identifier_return();
			}
			else if (character == 'd')
			{
				identifierStart();
				defined_identifier();
			}
			else if (character == 'p')
			{
				identifierStart();
				identifier_print();
			}
			else if (isLetter() || character == '_')
			{
				identifierStart();
			}
			if (isIdentifier)
			{
				identifier();
			}
		}
		else
		{
			token.setId(Token::END);
		}
	}
	else
	{
		throw runtime_error("Invalid file name");
	}
	return token;
}

bool Scanner::isAlphanum() const
{
	return (isLetter() || isDigit());
}

bool Scanner::isLetter() const
{
	return ((character >= 'a' && character <= 'z') || (character >= 'A' && character <= 'Z'));
}

bool Scanner::isDigit() const
{
	return (character >= '0' && character <= '9');
}


bool Scanner::isSpace() const
{
	return (character == '\t' || character == '\n' || character == ' ');
}

void Scanner::nextCharacter()
{
	if (isIdentifier)
	{
		name += character;
		++size;
	}
	character = file.get();
}

void Scanner::identifierStart()
{
	name = string();
	isIdentifier = true;
	size = 0;
}

void Scanner::identifierEnd()
{
	isIdentifier = false;
}

void Scanner::commonTokenEnd(Token::TokenID id)
{
	nextCharacter();
	if (!isAlphanum() && character != '_')
	{
		identifierEnd();
		token.setId(id);
	}
}

void Scanner::var()
{
	nextCharacter();
	identifierStart();
	if (isLetter() || character == '_')
	{
		do
		{
			nextCharacter();
		}
		while ((isAlphanum() || character == '_') && size < 252);
		if (size < 252)
		{
			token.setId(Token::VAR);
			token.setValue(name);
			identifierEnd();
		}
		else
		{
			throw runtime_error("Variable error : name too long\nName = " + name);
		}
	}
	else
	{
		throw runtime_error("Variable error : invalid name");
	}
}

void Scanner::identifier()
{
	while ((isAlphanum() || character == '_') && size < 252)
	{
		nextCharacter();
	}
	if (size < 252)
	{
		token.setId(Token::IDENTIFIER);
		token.setValue(name);
		identifierEnd();
	}
	else
	{
		throw runtime_error("Function error : name too long");
	}
}

void Scanner::float_integer()
{
	identifierStart();
	do
	{
		nextCharacter();
	}
	while (isDigit());
	if (character == '.')
	{
		string tmp;
		tmp = name;
		nextCharacter();
		if (isDigit())
		{
			do
			{
				nextCharacter();
			}
			while (isDigit());
			token.setId(Token::FLOAT);
			token.setValue(name);
		}
		else
		{
			throw runtime_error("Error : syntax error");
			token.setId(Token::INTEGER);
			token.setValue(tmp);
			file.seekg(-2, ios::cur);
		}
	}
	else
	{
		token.setId(Token::INTEGER);
		token.setValue(name);
	}
	identifierEnd();
}

void Scanner::String()
{
	nextCharacter();
	identifierStart();
	while (character != '\'' && !file.eof())
	{
		nextCharacter();
	}
	if (file.eof())
	{
		throw runtime_error("String error : incomplete string");
	}
	token.setId(Token::STRING);
	token.setValue(name);
	identifierEnd();
	nextCharacter();
}

void Scanner::space()
{
	do
	{
		nextCharacter();
	}
	while (isSpace());
	token.setId(Token::SPACE);
}

void Scanner::comment()
{
	do
	{
		nextCharacter();
	}
	while (character != '\n' && !file.eof());
	token.setId(Token::COMMENT);
}

void Scanner::callMark_lazyAnd()
{
	nextCharacter();
	if (character == '&')
	{
		token.setId(Token::LAZY_AND);
		nextCharacter();
	}
	else
	{
		token.setId(Token::CALL_MARK);
	}
}

void Scanner::different_not()
{
	nextCharacter();
	if (character == '=')
	{
		token.setId(Token::DIFFERENT);
		nextCharacter();
	}
	else
	{
		token.setId(Token::NOT);
	}
}

void Scanner::identifier_ne_notletters()
{
	nextCharacter();
	if (character == 'e')
	{
		commonTokenEnd(Token::NE);
	}
}

void Scanner::lazyOr()
{
	nextCharacter();
	if (character == '|')
	{
		token.setId(Token::LAZY_OR);
		nextCharacter();
	}
	else
	{
		throw runtime_error("Or error : Pipe character missing");
	}
}

void Scanner::assignMark_equals()
{
	nextCharacter();
	if (character == '=')
	{
		token.setId(Token::EQUALS);
		nextCharacter();
	}
	else
	{
		token.setId(Token::ASSIGN_MARK);
	}
}

void Scanner::else_elseif_eq_identifier()
{
	nextCharacter();
	if (character == 'l')
	{
		else_elseif_identifier();
	}
	else if (character == 'q')
	{
		commonTokenEnd(Token::EQ);
	}
}

void Scanner::else_elseif_identifier()
{
	nextCharacter();
	if (character == 's')
	{
		nextCharacter();
		if (character == 'e')
		{
			commonTokenEnd(Token::ELSE);
		}
		else if (character == 'i')
		{
			elseif_identifier();
		}
	}
}

void Scanner::elseif_identifier()
{
	nextCharacter();
	if (character == 'f')
	{
		commonTokenEnd(Token::ELSIF);
	}
}

void Scanner::lower_lowerEquals()
{
	nextCharacter();
	if (character == '=')
	{
		token.setId(Token::LOWER_EQUALS);
		nextCharacter();
	}
	else
	{
		token.setId(Token::LOWER);
	}
}

void Scanner::identifier_le_length_lt()
{
	nextCharacter();
	if (character == 'e')
	{
		identifier_le_length();
	}
	else if (character == 't')
	{
		commonTokenEnd(Token::LT);
	}
}

void Scanner::identifier_le_length()
{
	nextCharacter();
	if (character == 'n')
	{
		identifier_length();
	}
	else if (!isAlphanum() && character != '_')
	{
		identifierEnd();
		token.setId(Token::LE);
	}
}

void Scanner::identifier_length()
{
	nextCharacter();
	if (character == 'g')
	{
		nextCharacter();
		if (character == 't')
		{
			nextCharacter();
			if (character == 'h')
			{
				commonTokenEnd(Token::IDENTIFIER);
				token.setValue("length");
			}
		}
	}
}

void Scanner::greater_greaterEquals()
{
	nextCharacter();
	if (character == '=')
	{
		token.setId(Token::GREATER_EQUALS);
		nextCharacter();
	}
	else
	{
		token.setId(Token::GREATER);
	}
}

void Scanner::ge_gt_identifier()
{
	nextCharacter();
	if (character == 'e')
	{
		commonTokenEnd(Token::GE);
	}
	else if (character == 't')
	{
		commonTokenEnd(Token::GT);
	}
}

void Scanner::identifier_scalar_sub_substr()
{
	nextCharacter();
	if (character == 'c')
	{
		identifier_scalar();
	}
	else if (character == 'u')
	{
		identifier_sub_substr();
	}
}

void Scanner::identifier_scalar()
{
	nextCharacter();
	if (character == 'a')
	{
		nextCharacter();
		if (character == 'l')
		{
			nextCharacter();
			if (character == 'a')
			{
				nextCharacter();
				if (character == 'r')
				{
					commonTokenEnd(Token::IDENTIFIER);
					token.setValue("scalar");
				}
			}
		}
	}
}

void Scanner::identifier_sub_substr()
{
	nextCharacter();
	if (character == 'b')
	{
		nextCharacter();
		if (character == 's')
		{
			identifier_substr();
		}
		else if (!isAlphanum() && character != '_')
		{
			identifierEnd();
			token.setId(Token::SUB);
		}
	}
}

void Scanner::identifier_substr()
{
	nextCharacter();
	if (character == 't')
	{
		nextCharacter();
		if (character == 'r')
		{
			commonTokenEnd(Token::IDENTIFIER);
			token.setValue("substr");
		}
	}
}

void Scanner::identifier_if_int()
{
	nextCharacter();
	if (character == 'f')
	{
		commonTokenEnd(Token::IF);
	}
	else if (character == 'n')
	{
		identifier_int();
	}
}

void Scanner::identifier_int()
{
	nextCharacter();
	if (character == 't')
	{
		commonTokenEnd(Token::IDENTIFIER);
		token.setValue("int");
	}
}

void Scanner::identifier_unless()
{
	nextCharacter();
	if (character == 'n')
	{
		nextCharacter();
		if (character == 'l')
		{
			nextCharacter();
			if (character == 'e')
			{
				nextCharacter();
				if (character == 's')
				{
					nextCharacter();
					if (character == 's')
					{
						commonTokenEnd(Token::UNLESS);
					}
				}
			}
		}
	}
}

void Scanner::identifier_return()
{
	nextCharacter();
	if (character == 'e')
	{
		nextCharacter();
		if (character == 't')
		{
			nextCharacter();
			if (character == 'u')
			{
				nextCharacter();
				if (character == 'r')
				{
					nextCharacter();
					if (character == 'n')
					{
						commonTokenEnd(Token::RETURN);
					}
				}
			}
		}
	}
}

void Scanner::defined_identifier()
{
	nextCharacter();
	if (character == 'e')
	{
		nextCharacter();
		if (character == 'f')
		{
			nextCharacter();
			if (character == 'i')
			{
				nextCharacter();
				if (character == 'n')
				{
					nextCharacter();
					if (character == 'e')
					{
						nextCharacter();
						if (character == 'd')
						{
							commonTokenEnd(Token::IDENTIFIER);
							token.setValue("defined");
						}
					}
				}
			}
		}
	}
}

void Scanner::identifier_print()
{
	nextCharacter();
	if (character == 'r')
	{
		nextCharacter();
		if (character == 'i')
		{
			nextCharacter();
			if (character == 'n')
			{
				nextCharacter();
				if (character == 't')
				{
					commonTokenEnd(Token::IDENTIFIER);
					token.setValue("print");
				}
			}
		}
	}
}




