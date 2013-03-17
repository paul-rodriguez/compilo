#ifndef CODEGENERATOR_HPP_
#define CODEGENERATOR_HPP_

#include <string>
#include <stack>
#include "Type.hpp"

class Function;
class Code;
class CodeCondition;

class CodeGenerator
{
public:
	CodeGenerator(const std::string&);
	virtual ~CodeGenerator();

	void program_header();
	void endProgram();
	void function(const std::string&);
	void functionArg(const std::string&);
	void endFunction();
	void functionCall(const std::string&);
	void functionCallArgument();
	void var(const std::string&);
	void integer(const std::string& value);
	void Float(const std::string& value);
	void string(const std::string& value);
	void assign_mark();
	void unary_plus();
	void unary_minus();
	void Not();
	void different();
	void eq();
	void equals();
	void ne();
	void plus();
	void minus();
	void concat_mark();
	void lazy_or();
	void lazy_and();
	void greater();
	void greater_equals();
	void ge();
	void gt();
	void lower();
	void lower_equals();
	void le();
	void lt();
	void data();
	Code& code() const;
	void pop();

	void beginIf();
	void beginUnless();
	void beginIfBlock();
	void endCond();

	static int structSize;

protected:
	std::ostringstream& currentCode();
	const std::string& fctDefName() const;
	Function& fct() const;
	void unsetFctDef();
	bool isFctDef() const;
	void setFct(const std::string&);
	void newFct(std::string);
	bool isGlobal(const std::string&) const;
	void addGlobal(const std::string&);
	void Operator(Type);
	void calloc();
	void calloc(unsigned size);
	void strCpy(const std::string& destination, const std::string& source);
	void pushStack();
	void pushStackScalar(const std::string&, unsigned);
	void startOperator();
	void inequation();
	void lexicographicOrder();
	std::string nextLabel();

private:
	Code& code_;
	Function* fctDef_;
	unsigned label_;
	unsigned argumentIndex_;
	std::stack<CodeCondition*> cond_;
	unsigned condIndex_;
	std::ostringstream* condCode_;
};

#endif /* CODEGENERATOR_HPP_ */
