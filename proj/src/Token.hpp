#ifndef TOKEN_HPP
#define TOKEN_HPP

#include <ostream>
#include <string>
using namespace std;

class Token
{
	public:
		enum TokenID
		{
			END,
			VAR,
			IDENTIFIER,
			INTEGER,
			FLOAT,
			STRING,
			SPACE,
			COMMENT,
			LPAR,
			RPAR,
			LBRACE,
			RBRACE,
			SEMICOLON,
			CALL_MARK,
			PLUS,
			MINUS,
			TIMES,
			DIVIDE,
			NOT,
			NOTLETTERS,
			LAZY_AND,
			LAZY_OR,
			EQUALS,
			EQ,
			DIFFERENT,
			NE,
			LOWER,
			LT,
			GREATER,
			GT,
			LOWER_EQUALS,
			LE,
			GREATER_EQUALS,
			GE,
			COMMA,
			CONCAT_MARK,
			ASSIGN_MARK,
			SUB,
			IF,
			ELSE,
			ELSEIF,
			UNLESS,
			RETURN,
			DEFINED,
			INT,
			LENGTH,
			PRINT,
			SCALAR,
			SUBSTR
		};

		Token(TokenID = END, string = string());
		~Token();
		void setId(TokenID);
		void setValue(string);
		bool isLast() const;
		TokenID id() const;
		string value() const;

	private:
		TokenID id_;
		string value_;
};


ostream& operator<<(ostream&, const Token&);


#endif /* TOKEN_HPP */
