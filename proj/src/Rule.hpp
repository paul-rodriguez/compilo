#ifndef RULE_HPP_
#define RULE_HPP_

#include<vector>

class RuleElement;
class Variable;

class Rule
{
public:
	Rule(const Variable&, unsigned sizeHint = 5);
	virtual ~Rule();

	void addElem(const RuleElement&);

private:
	std::vector<const RuleElement*> prod_;
	const Variable& var_;
};

#endif /* RULE_HPP_ */
