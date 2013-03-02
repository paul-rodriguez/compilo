#include "Variable.hpp"
#include "Rule.hpp"


Variable::Variable():
	RuleElement(),
	rules_()
{
	// TODO Auto-generated constructor stub
}

Variable::~Variable()
{
	for (std::vector<const Rule*>::iterator it = rules_.begin(); it != rules_.end(); ++it)
	{
		delete *it;
	}
}

void Variable::addRule(const Rule& r)
{
	rules_.push_back(&r);
}

