#include "CodeCondition.hpp"

CodeCondition::CodeCondition(unsigned id, int t):
	elseBlock_(NULL),
	if_(NULL),
	ifBlock_(NULL),
	id_(id),
	type_(t),
	current_(NULL)
{
	// TODO Auto-generated constructor stub

}

CodeCondition::~CodeCondition()
{
	// TODO Auto-generated destructor stub
}

std::ostringstream& CodeCondition::addElseIf()
{
	std::ostringstream* o = new std::ostringstream();
	current_ = o;
	cond_.push_back(o);
	return *o;
}

std::ostringstream& CodeCondition::addInstr()
{
	std::ostringstream* o = new std::ostringstream();
	current_ = o;
	instr_.push_back(o);
	return *o;
}

std::ostringstream& CodeCondition::code()
{
	return *(current_);
}

std::ostringstream& CodeCondition::ifCond()
{
	if_ = new std::ostringstream();
	current_ = if_;
	return *if_;
}

std::ostringstream& CodeCondition::ifBlock()
{
	ifBlock_ = new std::ostringstream();
	current_ = ifBlock_;
	return *ifBlock_;
}

std::ostringstream& CodeCondition::elseBlock()
{
	elseBlock_ = new std::ostringstream();
	current_ = elseBlock_;
	return *elseBlock_;
}

std::string CodeCondition::write() const
{
	std::ostringstream o;
	o<<if_->str();
	o<<"ldr r4, [sp]"<<std::endl
	<<"add sp, sp, #4"<<std::endl
	<<"ldr r5, [r4, #8]"<<std::endl
	<<"cmp r5, #0"<<std::endl
	<<"be .COND"<<id_<<"false1"<<std::endl
	<<"cmp r5, #1"<<std::endl
	<<"be .COND"<<id_<<"string1"<<std::endl
	<<"ldr r5, [r4]"<<std::endl //test float value

	<<".COND"<<id_<<"string1:"<<std::endl

	<<".COND"<<id_<<"false1:"<<std::endl;

	return o.str();
}

