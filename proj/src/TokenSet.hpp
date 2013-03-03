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

protected:
	TokenSet& addToken(Token::TokenID);

private:
	std::set<Token::TokenID> tokens_;
};

#endif /* TOKENSET_HPP_ */
