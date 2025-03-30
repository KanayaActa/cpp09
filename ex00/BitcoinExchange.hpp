#pragma once

#include <iostream>
#include <string>
#include <map>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <iomanip>
#include <limits>

class BitcoinExchange {
private:
	std::map<std::string, float> _database;

	bool isValidDate(const std::string &date) const;
	bool isValidValue(const float value) const;
	std::string findClosestDate(const std::string &date) const;

public:
	BitcoinExchange();
	BitcoinExchange(const BitcoinExchange &other);
	BitcoinExchange &operator=(const BitcoinExchange &other);
	~BitcoinExchange();

	void loadDatabase(const std::string &filename);
	void processInputFile(const std::string &filename);
	float getExchangeRate(const std::string &date) const;
};

