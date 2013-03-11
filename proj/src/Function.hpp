#ifndef FUNCTION_HPP_
#define FUNCTION_HPP_

#include <string>
#include <vector>

class Function
{
public:
	Function(const std::string&);
	virtual ~Function();

	const std::string& name() const;

	unsigned argNum() const;
	void addArg(const std::string&);

protected:
	std::vector<std::string>& args();
	const std::vector<std::string>& args() const;

private:
	std::string name_;
	std::vector<std::string> args_;
};

#endif /* FUNCTION_HPP_ */
