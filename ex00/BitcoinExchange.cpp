/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miwasa <miwasa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 15:29:37 by miwasa            #+#    #+#             */
/*   Updated: 2025/03/30 15:56:02 by miwasa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange() {}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &other) : _database(other._database) {}

BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &other) {
	if (this != &other) {
		_database = other._database;
	}
	return *this;
}

BitcoinExchange::~BitcoinExchange() {}

bool BitcoinExchange::isValidDate(const std::string &date) const {
	if (date.length() != 10) {
		return false;
	}
	if (date[4] != '-' || date[7] != '-') {
		return false;
	}
	int year, month, day;
	try {
		year = std::atoi(date.substr(0, 4).c_str());
		month = std::atoi(date.substr(5, 2).c_str());
		day = std::atoi(date.substr(8, 2).c_str());
	} catch (...) {
		return false;
	}
	if (year < 0 || month < 1 || month > 12 || day < 1 || day > 31) {
		return false;
	}
	if (month == 4 || month == 6 || month == 9 || month == 11) {
		if (day > 30) return false;
	} else if (month == 2) {
		bool isLeapYear = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
		if (day > (isLeapYear ? 29 : 28)) return false;
	}
	return true;
}

bool BitcoinExchange::isValidValue(const float value) const {
	return value >= 0 && value <= 1000;
}

std::string BitcoinExchange::findClosestDate(const std::string &date) const {
	std::map<std::string, float>::const_iterator it = _database.lower_bound(date);

	if (it != _database.end() && it->first == date) {
		return date;
	}
	if (it == _database.begin() && it->first > date) {
		return "";
	}
	if (it == _database.end() || it->first > date) {
		if (it != _database.begin()) {
			--it;
			return it->first;
		}
	}
	return it->first;
}


void BitcoinExchange::loadDatabase(const std::string &filename) {
	std::ifstream file(filename.c_str());
	if (!file.is_open()) {
		std::cerr << "Error: could not open database file." << std::endl;
		return;
	}
	std::string line;
	std::getline(file, line);
	while (std::getline(file, line)) {
		std::istringstream iss(line);
		std::string date;
		float value;
		if (std::getline(iss, date, ',') && iss >> value) {
			if (isValidDate(date)) {
				_database[date] = value;
			}
		}
	}
	file.close();
}

void BitcoinExchange::processInputFile(const std::string &filename) {
	std::ifstream file(filename.c_str());
	if (!file.is_open()) {
		std::cerr << "Error: could not open file." << std::endl;
		return;
	}
	std::string line;
	std::getline(file, line);
	while (std::getline(file, line)) {
		std::istringstream iss(line);
		std::string date;
		std::string separator;
		float value;
		if (std::getline(iss, date, '|') && (iss >> value)) {
			
			date.erase(0, date.find_first_not_of(" \t"));
			date.erase(date.find_last_not_of(" \t") + 1);	
			if (!isValidDate(date)) {
				std::cerr << "Error: bad input => " << date << std::endl;
				continue;
			}
			if (value < 0) {
				std::cerr << "Error: not a positive number." << std::endl;
				continue;
			}
			if (value > 1000) {
				std::cerr << "Error: too large a number." << std::endl;
				continue;
			}
			std::string closestDate = findClosestDate(date);
			if (closestDate.empty()) {
				std::cerr << "Error: no exchange rate available for " << date << std::endl;
				continue;
			}
			float rate = _database[closestDate];
			float result = value * rate;
			std::cout << date << " => " << value << " = " << result << std::endl;
		} else {
			std::cerr << "Error: bad input => " << line << std::endl;
		}
	}
	file.close();
}


float BitcoinExchange::getExchangeRate(const std::string &date) const {
	std::string closestDate = findClosestDate(date);
	if (closestDate.empty()) {
		return 0.0f;
	}
	std::map<std::string, float>::const_iterator it = _database.find(closestDate);
	if (it != _database.end()) {
		return it->second;
	}
	return 0.0f;
}
