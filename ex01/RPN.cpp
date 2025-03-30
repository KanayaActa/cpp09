/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miwasa <miwasa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 15:30:31 by miwasa            #+#    #+#             */
/*   Updated: 2025/03/30 15:32:26 by miwasa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

RPN::RPN() {}

RPN::RPN(const RPN &other) : _stack(other._stack) {}

RPN &RPN::operator=(const RPN &other) {
	if (this != &other) {
		_stack = other._stack;
	}
	return *this;
}

RPN::~RPN() {}

bool RPN::isOperator(char c) const {
	return c == '+' || c == '-' || c == '*' || c == '/';
}

int RPN::performOperation(int a, int b, char op) const {
	switch (op) {
		case '+': return a + b;
		case '-': return a - b;
		case '*': return a * b;
		case '/':
			if (b == 0) {
				throw std::runtime_error("Error: Division by zero");
			}
			return a / b;
		default:
			throw std::runtime_error("Error: Invalid operator");
	}
}


int RPN::calculate(const std::string &expression) {
	std::istringstream iss(expression);
	std::string token;

	while (!_stack.empty()) {
		_stack.pop();
	}
	while (iss >> token) {
		if (token.length() == 1 && std::isdigit(token[0])) {
			_stack.push(token[0] - '0');
		}
		else if (token.length() == 1 && isOperator(token[0])) {
			if (_stack.size() < 2) {
				throw std::runtime_error("Error: Not enough operands");
			}
			int b = _stack.top();
			_stack.pop();
			int a = _stack.top();
			_stack.pop();
			
			_stack.push(performOperation(a, b, token[0]));
		}
		else {
			throw std::runtime_error("Error: Invalid token");
		}
	}
	if (_stack.size() != 1) {
		throw std::runtime_error("Error: Too many operands");
	}
	return _stack.top();
}