#ifndef GRAMMAR_HPP_
#define GRAMMAR_HPP_

#include<vector>

class Variable;

class Grammar
{
public:
	Grammar(unsigned sizeHint = 10);
	virtual ~Grammar();
	static const Grammar& projectGrammar();

private:
	std::vector<const Variable*> vars_;
	void addVariable(const Variable&);
};

#endif /* GRAMMAR_HPP_ */
