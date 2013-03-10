#ifndef CODEGENERATOR_HPP_
#define CODEGENERATOR_HPP_

#include<string>
#include<fstream>

class CodeGenerator
{
public:
	CodeGenerator(const std::string&);
	virtual ~CodeGenerator();

	void program_header();

protected:
	std::ofstream& file();
	const std::string& filename();

private:
	std::ofstream file_;
	const std::string filename_;
};

#endif /* CODEGENERATOR_HPP_ */
