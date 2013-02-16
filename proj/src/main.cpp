#include <iostream>
#include <fstream>
#include <list>
#include <string>
using namespace std;


enum Tokens {
	VARIABLE,
	FUNCTION,
	INTEGER,
	FLOAT,
	STRING,
	SPACE,
	COMMENT,
	OPENPAR,
	CLOSEPAR,
	OPENBRACK,
	CLOSEBRACK,
	SEMICOLON,
	CALL,
	PLUS,
	MINUS,
	MULT,
	DIV,
	NOT,
	NOTLETTERS,
	AND,
	OR,
	EQ,
	EQLETTERS,
	NEQ,
	NEQLETTERS,
	LT,
	LTLETTERS,
	GT,
	GTLETTERS,
	LE,
	LELETTERS,
	GE,
	GELETTERS,
	COMMA,
	POINT,
	ASSIGN,
	SUB,
	IF,
	ELSE,
	ELSIF,
	UNLESS,
	RETURN,
	DEFINED,
	INT,
	LENGTH,
	PRINT,
	SCALAR,
	SUBSTR
};

struct Token
{
	Token(Tokens id, string str = string()) { token = id; name = str; };
	Tokens token;
	string name;
};

ifstream file;
char character;
string name;
list<Token> tokensList;
int size;
bool isFunction;

bool isLetter()
{
	return ((character >= 'a' && character <= 'z') || (character >= 'A' && character <= 'Z'));
}

void nextCharacter()
{
	if (isFunction)
	{
		name += character;
		++size;
	}
	character = file.get();
}

bool isDigit()
{
	return (character >= '0' && character <= '9');
}

bool isAlphanum()
{
	return (isLetter() || isDigit());
}

bool isSpace()
{
	return (character == '\t' || character == '\n' || character == ' ');
}

void functionStart()
{
	name = string();
	isFunction = true;
	size = 0;
}

void functionEnd()
{
	isFunction = false;
}

void addToken(Token t)
{
	tokensList.push_back(t);
}

void commonTokenEnd(Tokens id)
{
	nextCharacter();
	if (!isAlphanum() && character != '_')
	{
		functionEnd();
		addToken(id);
	}
}

void variable()
{
	nextCharacter();
	functionStart();
	if (isLetter() || character == '_')
	{
		do
		{
			nextCharacter();
		}
		while ((isAlphanum() || character == '_') && size < 252);
		if (size < 252)
		{
			addToken(Token(VARIABLE, name));
			functionEnd();
		}
		else
		{
			throw string("Variable error : name too long\nName = " + name);
		}
	}
	else
	{
		throw string("Variable error : invalid name");
	}
}

void Float()
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
		addToken(Token(FLOAT, name));
	}
	else
	{
		addToken(Token(INTEGER, tmp));
		addToken(POINT);
	}
	functionEnd();
}

void integer_float()
{
	functionStart();
	do
	{
		nextCharacter();
	}
	while (isDigit());
	if (character == '.')
	{
		Float();
	}
	else
	{
		addToken(Token(INTEGER, name));
		functionEnd();
	}

}

void String()
{
	nextCharacter();
	functionStart();
	while (character != '\'')
	{
		nextCharacter();
	}
	addToken(Token(STRING, name));
	functionEnd();
	nextCharacter();
}

void space()
{
	do
	{
		nextCharacter();
	}
	while (isSpace());
	addToken(SPACE);
}

void comment()
{
	do
	{
		nextCharacter();
	}
	while (character != '\n');
	addToken(COMMENT);
}

void call_and()
{
	nextCharacter();
	if (character == '&')
	{
		addToken(AND);
		nextCharacter();
	}
	else
	{
		addToken(CALL);
	}
}

void not_neq()
{
	nextCharacter();
	if (character == '=')
	{
		addToken(NEQ);
		nextCharacter();
	}
	else
	{
		addToken(NOT);
	}
}

void function_notletters()
{
	nextCharacter();
	if (character == 't')
	{
		commonTokenEnd(NOTLETTERS);
	}
}

void function_notletters_neqletters()
{
	nextCharacter();
	if (character == 'o')
	{
		function_notletters();
	}
	else if (character == 'e')
	{
		commonTokenEnd(NEQLETTERS);
	}
}

void Or()
{
	nextCharacter();
	if (character == '|')
	{
		addToken(OR);
		nextCharacter();
	}
	else
	{
		throw string("Or error : Pipe character missing");
	}
}

void eq_assign()
{
	nextCharacter();
	if (character == '=')
	{
		addToken(EQ);
		nextCharacter();
	}
	else
	{
		addToken(ASSIGN);
	}
}

void function_elsif()
{
	nextCharacter();
	if (character == 'f')
	{
		commonTokenEnd(ELSIF);
	}
}

void function_else_elsif()
{
	nextCharacter();
	if (character == 's')
	{
		nextCharacter();
		if (character == 'e')
		{
			commonTokenEnd(ELSE);
		}
		else if (character == 'i')
		{
			function_elsif();
		}
	}
}

void function_eqletters_else_elsif()
{
	nextCharacter();
	if (character == 'q')
	{
		commonTokenEnd(EQLETTERS);
	}
	else if (character == 'l')
	{
		function_else_elsif();
	}
}

void lt_le()
{
	nextCharacter();
	if (character == '=')
	{
		addToken(LE);
		nextCharacter();
	}
	else
	{
		addToken(LT);
	}
}

void function_length()
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
				commonTokenEnd(LENGTH);
			}
		}
	}
}

void function_leletters_length()
{
	nextCharacter();
	if (character == 'n')
	{
		function_length();
	}
	else if (!isAlphanum() && character != '_')
	{
		functionEnd();
		addToken(LELETTERS);
	}
}

void function_ltletters_leletters_length()
{
	nextCharacter();
	if (character == 't')
	{
		commonTokenEnd(LTLETTERS);
	}
	else if (character == 'e')
	{
		function_leletters_length();
	}
}

void gt_ge()
{
	nextCharacter();
	if (character == '=')
	{
		addToken(GE);
		nextCharacter();
	}
	else
	{
		addToken(GT);
	}
}

void function_gtletters_geletters()
{
	nextCharacter();
	if (character == 't')
	{
		commonTokenEnd(GTLETTERS);
	}
	else if (character == 'e')
	{
		commonTokenEnd(GELETTERS);
	}
}

void function_substr()
{
	nextCharacter();
	if (character == 't')
	{
		nextCharacter();
		if (character == 'r')
		{
			commonTokenEnd(SUBSTR);
		}
	}
}

void function_sub_substr()
{
	nextCharacter();
	if (character == 'b')
	{
		nextCharacter();
		if (character == 's')
		{
			function_substr();
		}
		else if (!isAlphanum() && character != '_')
		{
			functionEnd();
			addToken(SUB);
		}
	}
}

void function_scalar()
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
					commonTokenEnd(SCALAR);
				}
			}
		}
	}
}

void function_sub_scalar_substr()
{
	nextCharacter();
	if (character == 'u')
	{
		function_sub_substr();
	}
	else if (character == 'c')
	{
		function_scalar();
	}
}

void function_int()
{
	nextCharacter();
	if (character == 't')
	{
		commonTokenEnd(INT);
	}
}

void function_if_int()
{
	nextCharacter();
	if (character == 'f')
	{
		commonTokenEnd(IF);
	}
	else if (character == 'n')
	{
		function_int();
	}
}

void function_unless()
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
						commonTokenEnd(UNLESS);
					}
				}
			}
		}
	}
}

void function_return()
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
						commonTokenEnd(RETURN);
					}
				}
			}
		}
	}
}

void function_defined()
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
							commonTokenEnd(DEFINED);
						}
					}
				}
			}
		}
	}
}

void function_print()
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
					commonTokenEnd(PRINT);
				}
			}
		}
	}
}

void function()
{
	while ((isAlphanum() || character == '_') && size < 252)
	{
		nextCharacter();
	}
	if (size < 252)
	{
		addToken(Token(FUNCTION, name));
		functionEnd();
	}
	else
	{
		throw string("Function error : name too long");
	}
}

void start()
{
	nextCharacter();
	isFunction = false;
	while (!file.eof())
	{
		if (character == '$')
		{
			variable();
		}
		else if (isDigit())
		{
			integer_float();
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
		else if (character == '(')
		{
			addToken(OPENPAR);
			nextCharacter();
		}
		else if (character == ')')
		{
			addToken(CLOSEPAR);
			nextCharacter();
		}
		else if (character == '{')
		{
			addToken(OPENBRACK);
			nextCharacter();
		}
		else if (character == '}')
		{
			addToken(CLOSEBRACK);
			nextCharacter();
		}
		else if (character == ';')
		{
			addToken(SEMICOLON);
			nextCharacter();
		}
		else if (character == '&')
		{
			call_and();
		}
		else if (character == '+')
		{
			addToken(PLUS);
			nextCharacter();
		}
		else if (character == '-')
		{
			addToken(MINUS);
			nextCharacter();
		}
		else if (character == '*')
		{
			addToken(MULT);
			nextCharacter();
		}
		else if (character == '/')
		{
			addToken(DIV);
			nextCharacter();
		}
		else if (character == '!')
		{
			not_neq();
		}
		else if (character == 'n')
		{
			functionStart();
			function_notletters_neqletters();
		}
		else if (character == '|')
		{
			Or();
		}
		else if (character == '=')
		{
			eq_assign();
		}
		else if (character == 'e')
		{
			functionStart();
			function_eqletters_else_elsif();
		}
		else if (character == '<')
		{
			lt_le();
		}
		else if (character == 'l')
		{
			functionStart();
			function_ltletters_leletters_length();
		}
		else if (character == '>')
		{
			gt_ge();
		}
		else if (character == 'g')
		{
			functionStart();
			function_gtletters_geletters();
		}
		else if (character == ',')
		{
			addToken(COMMA);
			nextCharacter();
		}
		else if (character == '.')
		{
			addToken(POINT);
			nextCharacter();
		}
		else if (character == 's')
		{
			functionStart();
			function_sub_scalar_substr();
		}
		else if (character == 'i')
		{
			functionStart();
			function_if_int();
		}
		else if (character == 'u')
		{
			functionStart();
			function_unless();
		}
		else if (character == 'r')
		{
			functionStart();
			function_return();
		}
		else if (character == 'd')
		{
			functionStart();
			function_defined();
		}
		else if (character == 'p')
		{
			functionStart();
			function_print();
		}
		else if (isLetter() || character == '_')
		{
			functionStart();
		}
		if (isFunction)
		{
			function();
		}
	}
}

int main(int argc, char** argv)
{
	if (argc == 2)
	{
		file.open(argv[1], ios::in);
		if (file.is_open())
		{
			try
			{
				start();
			}
			catch (string& error)
			{
				cout << error << endl;
			}
			file.close();
			ofstream out;
			out.open("test.txt", ios::out | ios::trunc);
			if (out.is_open())
			{
				for (list<Token>::iterator it = tokensList.begin(); it != tokensList.end(); ++it)
				{
					Tokens t = (*it).token;
					if (t == VARIABLE)
					{
						out << string("VARIABLE " + (*it).name).c_str();
					}
					else if (t == FUNCTION)
					{
						out << string("FUNCTION " + (*it).name).c_str();
					}
					else if (t == INTEGER)
					{
						out << string("INTEGER " + (*it).name).c_str();
					}
					else if (t == FLOAT)
					{
						out << string("FLOAT " + (*it).name).c_str();
					}
					else if (t == STRING)
					{
						out << string("STRING " + (*it).name).c_str();
					}
					else if (t == SPACE)
					{
						out << "SPACE";
					}
					else if (t == COMMENT)
					{
						out << "COMMENT";
					}
					else if (t == OPENPAR)
					{
						out << "OPENPAR";
					}
					else if (t == CLOSEPAR)
					{
						out << "CLOSEPAR";
					}
					else if (t == OPENBRACK)
					{
						out << "OPENBRACK";
					}
					else if (t == CLOSEBRACK)
					{
						out << "CLOSEBRACK";
					}
					else if (t == SEMICOLON)
					{
						out << "SEMICOLON";
					}
					else if (t == CALL)
					{
						out << "CALL";
					}
					else if (t == PLUS)
					{
						out << "PLUS";
					}
					else if (t == MINUS)
					{
						out << "MINUS";
					}
					else if (t == MULT)
					{
						out << "MULT";
					}
					else if (t == DIV)
					{
						out << "DIV";
					}
					else if (t == NOT)
					{
						out << "NOT";
					}
					else if (t == NOTLETTERS)
					{
						out << "NOTLETTERS";
					}
					else if (t == AND)
					{
						out << "AND";
					}
					else if (t == OR)
					{
						out << "OR";
					}
					else if (t == EQ)
					{
						out << "EQ";
					}
					else if (t == EQLETTERS)
					{
						out << "EQLETTERS";
					}
					else if (t == NEQ)
					{
						out << "NEQ";
					}
					else if (t == NEQLETTERS)
					{
						out << "NEQLETTERS";
					}
					else if (t == LT)
					{
						out << "LT";
					}
					else if (t == LTLETTERS)
					{
						out << "LTLETTERS";
					}
					else if (t == GT)
					{
						out << "GT";
					}
					else if (t == GTLETTERS)
					{
						out << "GTLETTERS";
					}
					else if (t == LE)
					{
						out << "LE";
					}
					else if (t == LELETTERS)
					{
						out << "LELETTERS";
					}
					else if (t == GE)
					{
						out << "GE";
					}
					else if (t == GELETTERS)
					{
						out << "GELETTERS";
					}
					else if (t == COMMA)
					{
						out << "COMMA";
					}
					else if (t == POINT)
					{
						out << "POINT";
					}
					else if (t == ASSIGN)
					{
						out << "ASSIGN";
					}
					else if (t == SUB)
					{
						out << "SUB";
					}
					else if (t == IF)
					{
						out << "IF";
					}
					else if (t == ELSE)
					{
						out << "ELSE";
					}
					else if (t == ELSIF)
					{
						out << "ELSIF";
					}
					else if (t == UNLESS)
					{
						out << "UNLESS";
					}
					else if (t == RETURN)
					{
						out << "RETURN";
					}
					else if (t == DEFINED)
					{
						out << "DEFINED";
					}
					else if (t == INT)
					{
						out << "INT";
					}
					else if (t == LENGTH)
					{
						out << "LENGTH";
					}
					else if (t == PRINT)
					{
						out << "PRINT";
					}
					else if (t == SCALAR)
					{
						out << "SCALAR";
					}
					else if (t == SUBSTR)
					{
						out << "SUBSTR";
					}

					out << "\n";
				}
				out.close();
			}
		}
	}
	else
	{
		cout << "No file specified for compilation" << endl;
	}
	return 0;
}
