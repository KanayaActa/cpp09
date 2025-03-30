/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miwasa <miwasa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 22:46:29 by miwasa            #+#    #+#             */
/*   Updated: 2025/03/30 15:31:10 by miwasa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <iostream>
#include <string>
#include <stack>
#include <sstream>
#include <cctype>
#include <stdexcept>

class RPN {
private:
	std::stack<int> _stack;

	bool isOperator(char c) const;
	int performOperation(int a, int b, char op) const;

public:
	RPN();
	RPN(const RPN &other);
	RPN &operator=(const RPN &other);
	~RPN();

	int calculate(const std::string &expression);
};
