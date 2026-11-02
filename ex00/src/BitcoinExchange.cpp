#include "../include/BitcoinExchange.hpp"
#include "../include/color.hpp"

#include <cstddef>
#include <cstdio>
#include <iostream>
#include <fstream>
#include <map>
#include <sstream>
#include <stdexcept>
#include <string>

BitcoinExchange::BitcoinExchange()
{
	std::cout << BOLD_ON YELLOW << "Default constructor called"
			  << BOLD_OFF << std::endl;
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &other) : _DB(other._DB)
{
	std::cout << BOLD_ON YELLOW << "A copy constructor called"
			  << BOLD_OFF << std::endl;
}

BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &other)
{
	if (this != &other)
		this->_DB = other._DB;
	std::cout << BOLD_ON YELLOW << "A assignement operator called"
			  << BOLD_OFF << std::endl;
	return (*this);
}

BitcoinExchange::~BitcoinExchange()
{
	std::cout <<  BOLD_ON RED << "A destructor called"
			  << BOLD_OFF << std::endl;
}

void BitcoinExchange::loadDataBase(const std::string &filename)
{
	std::ifstream file(filename.c_str());

	if (!file.is_open())
		throw std::runtime_error("Error: could not open database file.");

	std::string line;
	std::getline(file, line);
	while (std::getline(file, line))
	{
		std::size_t pos = line.find(',');
		if (pos == std::string::npos)
			continue;
		std::string date = line.substr(0, pos);
		std::string priceStr = line.substr(pos + 1);

		std::istringstream iss(priceStr);
		float price;
		if (iss >> price)
			this->_DB[date] = price;
	}
	file.close();
}

static bool isValidDate(const std::string &date)
{
	if (date.length() != 10)
		return false;
	if (date[4] != '-' || date[7] != '-')
		return false;
	int year, month, day;
	if (sscanf(date.c_str(), "%4d-%2d-%2d", &year, &month, &day) != 3)
		return false;
	if (year < 1 || (month < 1 || month > 12) || day < 1)
		return false;
	int daysInMonth[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	bool isLeapYear = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
	if (isLeapYear)
		daysInMonth[2] = 29;
	return day <= daysInMonth[month];
}

static bool isValidValue(const std::string &str, float &value)
{
	std::istringstream iss(str);
	std::string extra;

	if (!(iss >> value))
		return false;
	if (iss >> extra)
		return false;
	return true;
}

void BitcoinExchange::processInput(const std::string &filename)
{
	std::ifstream file(filename.c_str());

	if (!file.is_open())
		throw std::runtime_error("Error: could not open file.");
	
	std::string line;
	std::getline(file, line);
	while (std::getline(file, line))
	{
		std::size_t pos = line.find(" | ");
		if (pos == std::string::npos){
			std::cerr << CYAN << "Error: bad input => "
					  << line << RESET << std::endl;
			continue;
		}

		std::string date = line.substr(0, pos);
		if (!isValidDate(date)){
			std::cerr << CYAN << "Error: bad input => "
					  << date << RESET << std::endl;
			continue;
		}

		std::string valueStr = line.substr(pos + 3);
		float value;
		if (!isValidValue(valueStr, value)){
			std::cerr << CYAN << "Error: bad input => "
					  << valueStr << RESET << std::endl;
			continue;
		}
		if (value < 0){
			std::cerr << CYAN << "Error: not a positive number."
					  << RESET << std::endl;
			continue;
		}
		if (value > 1000){
			std::cerr << CYAN << "Error: too large a number."
					  << RESET << std::endl;
			continue;
		}

		if (this->_DB.empty())
		{
			std::cerr << CYAN << "Error: database is empty."
					  << RESET << std::endl;
			continue;
		}

		std::map<std::string , float>::iterator it = this->_DB.lower_bound(date);
		if (it == this->_DB.end() || it->first != date)
		{
			if (it == this->_DB.begin()){
				std::cerr << CYAN << "Error: date too early" << RESET << std::endl;
				continue;
			}
			--it;
		}
		float rate = it->second;
		std::cout << GREEN << date << " => " << value << " = "
				  << (value * rate) << RESET << std::endl;
	}
	file.close();
}
