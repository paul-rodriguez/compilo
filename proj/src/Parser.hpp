#ifndef PARSER_H_
#define PARSER_H_

#include"Token.hpp"

class Scanner;
class TokenSet;

class Parser
{
public:
	Parser(Scanner&);
	virtual ~Parser();

	void run();

protected:
	Scanner& scanner() const;
	const Token& tok() const;
	void setTok(const Token&);

	void match(Token::TokenID);
	void error();
	void error(Token::TokenID tok);
	void nextToken();
	bool isToken(Token::TokenID) const;
	bool isToken(const TokenSet&) const;

	void program();
	void program_f();
	void program_v();
	void instruction();
	void instruction_list();
	void instruction_f();
	void function();
	void function_argument();
	void argument_list();
	void argument_list_v();
	void condition();
	void condition_end();
	void expression();
	void expression_v();
	void expression_two();
	void expression_two_v();
	void expression_three();
	void expression_three_v();
	void expression_four();
	void expression_four_v();
	void expression_five();
	void expression_five_v();
	void expression_six();
	void expression_six_v();
	void expression_seven();
	void expression_seven_v();
	void expression_eight();
	void expression_eight_v();
	void expression_nine();

	void end();

private:
	Scanner& scanner_;
	const Token* tok_;

};

#endif /* PARSER_H_ */
