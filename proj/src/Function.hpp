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
	std::ostringstream& afterReturn();
	std::ostringstream& end();
	std::ostringstream& header();

protected:
	std::vector<std::string>& args();
	const std::vector<std::string>& args() const;

private:
	std::string name_;
	std::ostringstream code_;
	std::vector<std::string> args_;
	std::ostringstream afterReturn_;
	std::ostringstream header_;
};

#endif /* FUNCTION_HPP_ */
