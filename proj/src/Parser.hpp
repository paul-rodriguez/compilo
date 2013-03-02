#ifndef PARSER_H_
#define PARSER_H_

class Grammar;

class Parser
{
public:
	Parser();
	virtual ~Parser();

private:
	const Grammar& grammar_;

};

#endif /* PARSER_H_ */
