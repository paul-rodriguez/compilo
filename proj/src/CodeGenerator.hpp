#ifndef CODEGENERATOR_HPP_
#define CODEGENERATOR_HPP_

#include<string>

class Function;
class Code;

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
	void var(const std::string&);
	void integer(const std::string&);
	void text();
	void rodata();
	void data();
	Code& code() const;

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

private:
	Code& code_;
	Function* fctDef_;
};

#endif /* CODEGENERATOR_HPP_ */
