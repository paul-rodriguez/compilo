#ifndef CODEGENERATOR_HPP_
#define CODEGENERATOR_HPP_

#include<string>
#include<fstream>
#include<map>

class Function;

class CodeGenerator
{
public:
	CodeGenerator(const std::string&);
	virtual ~CodeGenerator();

	void program_header();
	void function(const std::string&);
	void functionArg(const std::string&);
	void endFunction();
	void text();
	void rodata();

protected:
	std::ofstream& file();
	const std::string& filename();

	const std::string& functionName() const;
	Function& fct() const;
	Function& fct(const std::string&);
	void newFct(std::string);
	std::map<std::string,Function*>& fctMap();

private:
	std::ofstream file_;
	const std::string filename_;
	Function* fct_;
	std::map<std::string,Function*> fctMap_;
};

#endif /* CODEGENERATOR_HPP_ */
