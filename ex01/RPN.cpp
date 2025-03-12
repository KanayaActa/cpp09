/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miwasa <miwasa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 22:46:56 by miwasa            #+#    #+#             */
/*   Updated: 2025/03/12 22:47:25 by miwasa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"
#include <stack>
#include <sstream>
#include <iostream>
#include <cstdlib>

RPN::RPN(const std::string &expression) : _expression(expression) {}

bool RPN::evaluate(double &result) const {
	std::istringstream iss(_expression);
	std::stack<double> stk;
	std::string token;

	while (iss >> token) {
		if (token == "+" || token == "-" || token == "*" || token == "/") {
			if (stk.size() < 2) {
				return false;
			}
			double right = stk.top();
			stk.pop();
			double left = stk.top();
			stk.pop();
			double res = 0.0;
			if (token == "+")
				res = left + right;
			else if (token == "-")
				res = left - right;
			else if (token == "*")
				res = left * right;
			else if (token == "/") {
				if (right == 0)
					return false;
				res = left / right;
			}
			stk.push(res);
		}
		else {
			char* endptr = 0;
			double num = std::strtod(token.c_str(), &endptr);
			if (*endptr != '\0') {
				return false;
			}
			stk.push(num);
		}
	}
	if (stk.size() != 1)
		return false;
	result = stk.top();
	return true;
}
