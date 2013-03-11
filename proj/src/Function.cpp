#include "Function.hpp"

Function::Function(const std::string& str):
	name_(str),
	args_()
{
	args().reserve(10);
}

Function::~Function()
{
	;
}

void Function::addArg(const std::string& arg)
{
	args().push_back(arg);
}

const std::string& Function::name() const { return name_; }
unsigned Function::argNum() const { return args().size(); }
std::vector<std::string>& Function::args() { return args_; }
const std::vector<std::string>& Function::args() const { return args_; }
