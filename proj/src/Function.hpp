#ifndef FUNCTION_HPP_
#define FUNCTION_HPP_

#include <string>
#include <vector>
#include <sstream>

class Function
{
public:
	Function(const std::string&);
	virtual ~Function();

	const std::string& name() const;
	std::ostringstream& code();
	void setCode(const std::string&);

	unsigned argSize() const;
	unsigned argIndex(const std::string&) const;
	void addArg(const std::string&);

protected:
	std::vector<std::string>& args();
	const std::vector<std::string>& args() const;

private:
	std::string name_;
	std::ostringstream code_;
	std::vector<std::string> args_;
};

#endif /* FUNCTION_HPP_ */
