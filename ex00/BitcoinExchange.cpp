/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miwasa <miwasa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 22:15:58 by miwasa            #+#    #+#             */
/*   Updated: 2025/03/12 22:42:12 by miwasa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
#include <cstdlib>

BitcoinExchange::BitcoinExchange(const std::string& dbFilename) {
	loadDatabase(dbFilename);
}

void BitcoinExchange::loadDatabase(const std::string& dbFilename) {
	std::ifstream file(dbFilename.c_str());
	if (!file.is_open()) {
		std::cerr << "Error: could not open database file.\n";
		return;
	}
	std::string line;
	std::getline(file, line);
	while (std::getline(file, line)) {
		std::istringstream iss(line);
		std::string date;
		std::string rateStr;
		if (std::getline(iss, date, ',') && std::getline(iss, rateStr)) {
			float rate = std::atof(rateStr.c_str());
			_db[date] = rate;
		}
	}
}

float BitcoinExchange::getRateForDate(const std::string& date) const {
	std::map<std::string, float>::const_iterator it = _db.find(date);
	if (it != _db.end())
		return it->second;
	it = _db.lower_bound(date);
	if (it == _db.begin()) {
		return -1.0f;
	}
	--it;
	return it->second;
}
