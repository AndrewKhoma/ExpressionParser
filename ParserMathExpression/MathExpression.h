#ifndef MATHEXPRESSION_H_
#define MATHEXPRESSION_H_

#include <stdexcept>
#include <cstring>
#include <string>
#include <vector>
#include <cctype>
#include <cmath>

using namespace std;

struct Expression 
{
	Expression(string token) : token(token) {}
	Expression(string token, Expression a) : token(token), args{ a } {}
	Expression(string token, Expression a, Expression b) : token(token), args{ a, b } {}

	string token;
	vector<Expression> args;
};

class Parser 
{
public:
	explicit Parser(const char* input) : input(input) {}
	Expression parse();
private:
	string parse_token();
	Expression parse_simple_expression();
	Expression parse_binary_expression(int min_priority);

	const char* input;
};

string Parser::parse_token() 
{
	while (isspace(*input)) 
		++input;

	if (isdigit(*input)) 
	{
		string number;
		while (isdigit(*input) || *input == '.') 
			number.push_back(*input++);
		return number;
	}

	static const string tokens[] = { "+", "-", "^", "*", "/", "mod", "abs", "sin", "cos", "(", ")" };
	for (auto& t : tokens) 
	{
		if (strncmp(input, t.c_str(), t.size()) == 0) 
		{
			input += t.size();
			return t;
		}
	}

	return "";
}

Expression Parser::parse_simple_expression() 
{
	auto token = parse_token();
	if (token.empty()) 
		throw runtime_error("Invalid input");

	if (token == "(") 
	{
		auto result = parse();
		if (parse_token() != ")") 
			throw runtime_error("Expected ')'");
		return result;
	}

	if (isdigit(token[0]))
		return Expression(token);

	return Expression(token, parse_simple_expression());
}

int get_priority(const string& binary_op) 
{
	if (binary_op == "+") 
		return 1;
	if (binary_op == "-") 
		return 1;
	if (binary_op == "*") 
		return 2;
	if (binary_op == "/") 
		return 2;
	if (binary_op == "mod") 
		return 2;
	if (binary_op == "^") 
		return 3;
	return 0;
}

Expression Parser::parse_binary_expression(int min_priority) 
{
	auto left_expr = parse_simple_expression();

	for (;;) 
	{
		auto op = parse_token();
		auto priority = get_priority(op);
		if (priority <= min_priority) 
		{
			input -= op.size();
			return left_expr;
		}

		auto right_expr = parse_binary_expression(priority);
		left_expr = Expression(op, left_expr, right_expr);
	}
}

Expression Parser::parse() 
{
	return parse_binary_expression(0);
}

double eval(const Expression& e) 
{
	switch (e.args.size()) 
	{
	case 2: 
	{
		auto a = eval(e.args[0]);
		auto b = eval(e.args[1]);
		if (e.token == "+") 
			return a + b;
		if (e.token == "-") 
			return a - b;
		if (e.token == "*") 
			return a * b;
		if (e.token == "/") 
			return a / b;
		if (e.token == "^") 
			return pow(a, b);
		if (e.token == "mod") 
			return (int)a % (int)b;
		throw runtime_error("Unknown binary operator");
	}

	case 1: 
	{
		auto a = eval(e.args[0]);
		if (e.token == "+") 
			return +a;
		if (e.token == "-") 
			return -a;
		if (e.token == "abs") 
			return abs(a);
		if (e.token == "sin") 
			return sin(a);
		if (e.token == "cos") 
			return cos(a);
		throw runtime_error("Unknown unary operator");
	}

	case 0:
		return strtod(e.token.c_str(), nullptr);
	}

	throw runtime_error("Unknown expression type");
}

#endif // !MATHEXPRESSION_H_

