/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miwasa <miwasa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 22:46:29 by miwasa            #+#    #+#             */
/*   Updated: 2025/03/12 22:46:46 by miwasa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string>

class RPN {
public:
	RPN(const std::string &expression);
	bool evaluate(double &result) const;

private:
	std::string _expression;
};
