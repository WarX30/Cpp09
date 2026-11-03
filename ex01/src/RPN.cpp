#include "../include/RPN.hpp"
#include <cctype>
#include <cstddef>
#include <stdexcept>

RPN::RPN() {}

RPN::RPN(const RPN &other) : _stack(other._stack) {}

RPN	&RPN::operator=(const RPN &other) {
	if (this != &other)
		this->_stack = other._stack;
	return *this;
}

RPN::~RPN() {}

bool RPN::isOperator(char c) const
{
	return (c == '-' || c == '+' || c == '*' || c == '/');
}

int RPN::applyOperator(int a, int b, char op)
{
	switch (op)
	{
		case '+': return a + b;
		case '-': return a - b;
		case '*': return a * b;
		case '/':
			if (b == 0)
				throw std::runtime_error("Error");
			return a / b;
	}
	throw std::runtime_error("Error");
}

static bool isValidFormatExpression(const std::string &expression)
{
    if (expression.empty())
        return false;

    for (std::size_t i = 0; i < expression.length(); i++)
    {
        char c = expression[i];

        if (std::isdigit(static_cast<unsigned char>(c))
            || c == '+' || c == '-' || c == '*' || c == '/')
        {
            if (i + 1 < expression.length()
                && expression[i + 1] != ' ')
                return false;
        }
        else if (c == ' ')
        {
            if (i == 0 || i + 1 == expression.length())
                return false;
            if (expression[i + 1] == ' ')
                return false;
        }
        else
            return false;
    }
    return true;
}

int RPN::evaluate(const std::string &expression)
{
	if (!isValidFormatExpression(expression))
		throw std::runtime_error("Error");
	while (!this->_stack.empty())
		this->_stack.pop();
	for (std::size_t i = 0; i < expression.length(); i++)
	{
		char c = expression[i];

		if (c == ' ')
			continue;
		if (std::isdigit(static_cast<unsigned char>(c)))
			this->_stack.push(c - '0');
		else if (isOperator(c))
		{
			if (this->_stack.size() < 2)
				throw std::runtime_error("Error");
			int a = this->_stack.top(); this->_stack.pop();
			int b = this->_stack.top(); this->_stack.pop();
			this->_stack.push(applyOperator(b, a, c));
		}
		else
			throw std::runtime_error("Error");
	}
	if (this->_stack.size() != 1)
		throw std::runtime_error("Error");
	return this->_stack.top();
}
