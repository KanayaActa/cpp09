/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miwasa <miwasa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 22:16:17 by miwasa            #+#    #+#             */
/*   Updated: 2025/03/12 22:17:09 by miwasa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <map>
#include <string>

class BitcoinExchange {
public:
	BitcoinExchange(const std::string& dbFilename);
	float getRateForDate(const std::string& date) const;
private:
	std::map<std::string, float> _db;
	void loadDatabase(const std::string& dbFilename);
};
