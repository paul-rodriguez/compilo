#ifndef TOKENSET_HPP_
#define TOKENSET_HPP_

#include<set>
#include"Token.hpp"

class TokenSet
{
public:
	TokenSet();
	virtual ~TokenSet();

	bool contains(const Token&) const;

	static const TokenSet f_instruction;
	static const TokenSet f_expression;
	static const TokenSet f_condition;
	static const TokenSet f_expression_four_v;
	static const TokenSet f_expression_four_f;
	static const TokenSet f_expression_five_v;
	static const TokenSet f_expression_six_v;
	static const TokenSet f_expression_seven_v;
	static const TokenSet f_expression_eight_v;
	static const TokenSet f_simple_expression;

protected:
	TokenSet& addToken(Token::TokenID);

private:
	std::set<Token::TokenID> tokens_;
};

#endif /* TOKENSET_HPP_ */
