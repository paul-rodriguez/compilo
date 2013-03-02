#include "Grammar.hpp"
#include "Variable.hpp"
#include "Rule.hpp"

Grammar::Grammar(unsigned sizeHint):
	vars_()
{
	vars_.reserve(sizeHint);
}

Grammar::~Grammar()
{
	for (std::vector<const Variable*>::iterator it = vars_.begin(); it != vars_.end(); ++it)
	{
		delete *it;
	}
}

void Grammar::addVariable(const Variable& v)
{
	vars_.push_back(&v);
}

const Grammar& Grammar::projectGrammar()
{
	Grammar& grammar = *(new Grammar());
	Variable* program = new Variable();
	Variable* program_v = new Variable();
	Variable* program_f = new Variable();

	Rule* program1 = new Rule(*program,2);
	program1->addElem(*program_v);
	program1->addElem(*program_f);
	program->addRule(*program1);

	grammar.addVariable(*program);

	return grammar;
}

