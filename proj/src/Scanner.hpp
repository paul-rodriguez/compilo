#ifndef SCANNER_HPP
#define SCANNER_HPP

#include <fstream>
#include <list>
#include <string>
#include "Token.hpp"
using namespace std;

class Scanner
{
	public:
		Scanner(char*);
		~Scanner();

		/*
		 * The token has to be copied (this function changes the same token object)
		 */
		const Token& nextToken();

	protected:
		bool isAlphanum() const;
		bool isLetter() const;
		bool isDigit() const;
		bool isSpace() const;

		void nextCharacter();

		void identifierStart();
		void identifierEnd();

		void commonTokenEnd(Token::TokenID id);

		void var();
		void identifier();
		void float_integer();
		void String();
		void space();
		void comment();
		void callMark_lazyAnd();
		void different_not();
		void identifier_ne_notletters();
		void identifier_notletters();
		void lazyOr();
		void assignMark_equals();
		void else_elseif_eq_identifier();
		void else_elseif_identifier();
		void elseif_identifier();
		void lower_lowerEquals();
		void identifier_le_length_lt();
		void identifier_le_length();
		void identifier_length();
		void greater_greaterEquals();
		void ge_gt_identifier();
		void identifier_scalar_sub_substr();
		void identifier_scalar();
		void identifier_sub_substr();
		void identifier_substr();
		void identifier_if_int();
		void identifier_int();
		void identifier_unless();
		void identifier_return();
		void defined_identifier();
		void identifier_print();

	private:
		ifstream file;
		char character;
		string name;
		Token token;
		int size;
		bool isIdentifier;
};


#endif /* SCANNER_HPP */
