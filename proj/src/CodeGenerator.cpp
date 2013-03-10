#include "CodeGenerator.hpp"
#include "Function.hpp"

CodeGenerator::CodeGenerator(const std::string& filename):
	file_(),
	filename_(filename),
	fct_(NULL),
	fctMap_()
{
	file().open(filename.c_str());
}

CodeGenerator::~CodeGenerator()
{
	// TODO Auto-generated destructor stub
}

std::ofstream& CodeGenerator::file()
{
	return file_;
}

const std::string& CodeGenerator::filename()
{
	return filename_;
}

void CodeGenerator::program_header()
{
	file()<<".arch armv5te"<<std::endl
		<<".fpu softvfp"<<std::endl
		<<".eabi_attribute 20, 1"<<std::endl
		<<".eabi_attribute 21, 1"<<std::endl
		<<".eabi_attribute 23, 3"<<std::endl
		<<".eabi_attribute 24, 1"<<std::endl
		<<".eabi_attribute 25, 1"<<std::endl
		<<".eabi_attribute 26, 2"<<std::endl
		<<".eabi_attribute 30, 6"<<std::endl
		<<".eabi_attribute 18, 4"<<std::endl
		<<".file "<<filename()<<std::endl<<std::endl;
}

void CodeGenerator::text()
{
	file()<<".text"<<std::endl
		<<".align 2"<<std::endl;
}

void CodeGenerator::rodata()
{
	file()<<"section .rodata"<<std::endl
		<<".align 2"<<std::endl;
}

void CodeGenerator::function(const std::string& name)
{
	newFct(name);
	file()<<".global "<<functionName()<<std::endl
		<<".type "<<functionName()<<", %function"<<std::endl
		<<functionName()<<":"<<std::endl
		<<"stmfd sp!, {fp, lr}"<<std::endl;
}

void CodeGenerator::functionArg(const std::string& name)
{
	fct().addArg(name);
}

void CodeGenerator::endFunction()
{
	file()<<"ldmfd sp!, {fp, pc}"<<std::endl
		<<".size "<<functionName()<<", .-"<<functionName()<<std::endl;
}

Function& CodeGenerator::fct(const std::string& name)
{
	return *(fctMap()[name]);
}

const std::string& CodeGenerator::functionName() const { return fct().name(); }
Function& CodeGenerator::fct() const { return *fct_; }
std::map<std::string,Function*>& CodeGenerator::fctMap() { return fctMap_; }
void CodeGenerator::newFct(std::string name)
{
	fct_ = new Function(name);
	fctMap()[name] = fct_;
}


