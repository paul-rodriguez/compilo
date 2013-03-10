#include "CodeGenerator.hpp"

CodeGenerator::CodeGenerator(const std::string& filename):
	file_(),
	filename_(filename)
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
		<<".file "<<filename()<<std::endl;
}

