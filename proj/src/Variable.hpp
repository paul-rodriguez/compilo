#ifndef VARIABLE_HPP_
#define VARIABLE_HPP_

#include<vector>
#include"RuleElement.hpp"

class Rule;

class Variable : public RuleElement
{
public:
	Variable();
	virtual ~Variable();

	void addRule(const Rule&);

private:
	std::vector<const Rule*> rules_;
};

#endif /* VARIABLE_HPP_ */
