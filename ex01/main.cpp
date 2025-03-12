/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miwasa <miwasa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 22:47:35 by miwasa            #+#    #+#             */
/*   Updated: 2025/03/12 22:47:58 by miwasa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"
#include <iostream>

int main(int argc, char **argv) {
	if (argc != 2) {
		std::cerr << "Error\n";
		return 1;
	}
	RPN rpn(argv[1]);
	double result;
	if (!rpn.evaluate(result)) {
		std::cerr << "Error\n";
		return 1;
	}
	std::cout << result << std::endl;
	return 0;
}
