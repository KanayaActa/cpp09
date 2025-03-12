/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miwasa <miwasa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 22:16:48 by miwasa            #+#    #+#             */
/*   Updated: 2025/03/12 22:42:41 by miwasa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>

int main(int argc, char* argv[]) {
	if (argc != 2) {
		std::cerr << "Error: could not open file.\n";
		return 1;
	}

	BitcoinExchange exchange("data.csv");

	std::ifstream input(argv[1]);
	if (!input.is_open()) {
		std::cerr << "Error: could not open file.\n";
		return 1;
	}

	std::string line;
	std::getline(input, line);

	while (std::getline(input, line)) {
		std::istringstream iss(line);
		std::string date, valueStr;
		if (!std::getline(iss, date, '|') || !std::getline(iss, valueStr)) {
			std::cerr << "Error: bad input => " << line << "\n";
			continue;
		}

		float value = std::atof(valueStr.c_str());
		if (value < 0) {
			std::cerr << "Error: not a positive number.\n";
			continue;
		}
		if (value > 1000) {
			std::cerr << "Error: too large a number.\n";
			continue;
		}

		float rate = exchange.getRateForDate(date);
		if (rate < 0) {
			std::cerr << "Error: bad input => " << date << "\n";
			continue;
		}

		std::cout << date << " => " << value << " = " << (value * rate) << "\n";
	}

	return 0;
}
