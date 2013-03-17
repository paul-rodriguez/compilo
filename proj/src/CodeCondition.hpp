#ifndef CODECONDITION_HPP_
#define CODECONDITION_HPP_

#define COND_IF 0
#define COND_UNLESS 1

#include<list>
#include<sstream>

class CodeCondition
{
public:
	CodeCondition(unsigned,int);
	virtual ~CodeCondition();

	std::ostringstream& ifCond();
	std::ostringstream& ifBlock();
	std::ostringstream& elseBlock();

	std::ostringstream& addElseIf();
	std::ostringstream& addInstr();

	std::ostringstream& code();

	std::string write() const;

private:
	std::list<std::ostringstream*> cond_;
	std::list<std::ostringstream*> instr_;
	std::ostringstream* elseBlock_;
	std::ostringstream* if_;
	std::ostringstream* ifBlock_;
	unsigned id_;
	int type_;
	std::ostringstream* current_;
};

#endif /* CODECONDITION_HPP_ */
