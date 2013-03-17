#ifndef CODE_HPP_
#define CODE_HPP_

#include<string>
#include<fstream>
#include<list>
#include<map>
#include<sstream>

#include "Function.hpp"

class Code
{
public:
	Code(const std::string&);
	virtual ~Code();

	void write();
	void setProgramHeader(bool programHeader);

	bool isGlobal(const std::string&) const;
	void addGlobal(const std::string&);
	std::string addRodata(const std::string&);
	void addFunction(Function&);
	unsigned globalOffset(const std::string&) const;
	void writeMain();
	Function& main();

protected:
	std::ofstream& file();
	const std::string& filename();

	void predefinedFunctions();
	void programHeader();
	void writeRodata();
	void endProgram();
	void function(Function&);

	std::list<std::string>& globals();
	const std::list<std::string>& globals() const;
	std::map<std::string,Function*>& fctMap();
	Function& fct(const std::string&);
	std::list<std::string>& rodata();

private:
	std::ofstream file_;
	const std::string filename_;

	bool programHeader_;
	std::list<std::string> globals_;
	std::map<std::string,Function*> fctMap_;
	Function main_;
	std::list<std::string> rodata_;
};

#endif /* CODE_HPP_ */
