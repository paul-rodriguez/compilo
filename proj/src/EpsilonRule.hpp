#ifndef EPSILONRULE_HPP_
#define EPSILONRULE_HPP_

#include "Rule.hpp"

class EpsilonRule: public Rule
{
public:
	EpsilonRule(const Variable& var);
	virtual ~EpsilonRule();
};

#endif /* EPSILONRULE_HPP_ */
