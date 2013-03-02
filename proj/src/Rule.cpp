#include "Rule.hpp"
#include "Variable.hpp"

Rule::Rule(const Variable& var, unsigned sizeHint):
	prod_(),
	var_(var)
{
	prod_.reserve(sizeHint);
}

Rule::~Rule()
{
	//do nothing : everything will be deleted elsewhere
}

void Rule::addElem(const RuleElement& e)
{
	prod_.push_back(&e);
}
