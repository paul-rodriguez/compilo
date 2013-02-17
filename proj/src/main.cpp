#include <iostream>
#include <fstream>
#include <list>
#include <string>
#include "Scanner.hpp"
#include "Token.hpp"
using namespace std;

int main(int argc, char** argv)
{
	if (argc == 2)
	{
		Scanner sc = Scanner(argv[1]);
		ofstream out;
		out.open("test.txt", ios::out | ios::trunc)
		if (out.is_open())
		{
			Token t = sc.nextToken();
			while (t.id() != END)
			{
				if (t.id() == VARIABLE)
				{
					out << string("VARIABLE " + t.value()).c_str();
				}
				else if (t.id() == FUNCTION)
				{
					out << string("FUNCTION " + t.value()).c_str();
				}
				else if (t.id() == INTEGER)
				{
					out << string("INTEGER " + t.value()).c_str();
				}
				else if (t.id() == FLOAT)
				{
					out << string("FLOAT " + t.value()).c_str();
				}
				else if (t.id() == STRING)
				{
					out << string("STRING " + t.value()).c_str();
				}
				else if (t.id() == SPACE)
				{
					out << "SPACE";
				}
				else if (t.id() == COMMENT)
				{
					out << "COMMENT";
				}
				else if (t.id() == LPAR)
				{
					out << "LPAR";
				}
				else if (t.id() == RPAR)
				{
					out << "RPAR";
				}
				else if (t.id() == LBRACE)
				{
					out << "LBRACE";
				}
				else if (t.id() == RBRACE)
				{
					out << "RBRACE";
				}
				else if (t.id() == SEMICOLON)
				{
					out << "SEMICOLON";
				}
				else if (t.id() == FUNCTION_CALL)
				{
					out << "FUNCTION_CALL";
				}
				else if (t.id() == PLUS)
				{
					out << "PLUS";
				}
				else if (t.id() == MINUS)
				{
					out << "MINUS";
				}
				else if (t.id() == TIMES)
				{
					out << "TIMES";
				}
				else if (t.id() == DIVIDE)
				{
					out << "DIVIDE";
				}
				else if (t.id() == NOT)
				{
					out << "NOT";
				}
				else if (t.id() == NOTLETTERS)
				{
					out << "NOTLETTERS";
				}
				else if (t.id() == AND)
				{
					out << "AND";
				}
				else if (t.id() == OR)
				{
					out << "OR";
				}
				else if (t.id() == EQ)
				{
					out << "EQ";
				}
				else if (t.id() == EQLETTERS)
				{
					out << "EQLETTERS";
				}
				else if (t.id() == NEQ)
				{
					out << "NEQ";
				}
				else if (t.id() == NEQLETTERS)
				{
					out << "NEQLETTERS";
				}
				else if (t.id() == LT)
				{
					out << "LT";
				}
				else if (t.id() == LTLETTERS)
				{
					out << "LTLETTERS";
				}
				else if (t.id() == GT)
				{
					out << "GT";
				}
				else if (t.id() == GTLETTERS)
				{
					out << "GTLETTERS";
				}
				else if (t.id() == LE)
				{
					out << "LE";
				}
				else if (t.id() == LELETTERS)
				{
					out << "LELETTERS";
				}
				else if (t.id() == GE)
				{
					out << "GE";
				}
				else if (t.id() == GELETTERS)
				{
					out << "GELETTERS";
				}
				else if (t.id() == COMMA)
				{
					out << "COMMA";
				}
				else if (t.id() == POINT)
				{
					out << "POINT";
				}
				else if (t.id() == ASSIGN_MARK)
				{
					out << "ASSIGN_MARK";
				}
				else if (t.id() == SUB)
				{
					out << "SUB";
				}
				else if (t.id() == IF)
				{
					out << "IF";
				}
				else if (t.id() == ELSE)
				{
					out << "ELSE";
				}
				else if (t.id() == ELSIF)
				{
					out << "ELSIF";
				}
				else if (t.id() == UNLESS)
				{
					out << "UNLESS";
				}
				else if (t.id() == RETURN)
				{
					out << "RETURN";
				}
				else if (t.id() == DEFINED)
				{
					out << "DEFINED";
				}
				else if (t.id() == INT)
				{
					out << "INT";
				}
				else if (t.id() == LENGTH)
				{
					out << "LENGTH";
				}
				else if (t.id() == PRINT)
				{
					out << "PRINT";
				}
				else if (t.id() == SCALAR)
				{
					out << "SCALAR";
				}
				else if (t.id() == SUBSTR)
				{
					out << "SUBSTR";
				}
				out << "\n";
				t = sc.nextToken();
			}
			out.close();
		}
	}
	else
	{
		cout << "No file specified for compilation" << endl;
	}
	return 0;
}
