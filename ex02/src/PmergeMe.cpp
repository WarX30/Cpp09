#include "../include/PmergeMe.hpp"
#include "../include/color.hpp"
#include <algorithm>
#include <cstddef>
#include <cstdlib>
#include <iterator>
#include <limits>
#include <stdexcept>

PmergeMe::PmergeMe() {}

PmergeMe::PmergeMe(const PmergeMe &other) : _vec(other._vec), _deq(other._deq) {}

PmergeMe &PmergeMe::operator=(const PmergeMe &other)
{
	if (this != &other)
	{
		this->_vec = other._vec;
		this->_deq = other._deq;
	}
	return *this;
}

void PmergeMe::sortVector()
{
	if (this->_vec.size() <= 1)
		return ;

	std::vector<int> larger, smaller;
	bool hasOdd = (this->_vec.size() % 2 != 0);
	int oddElement = hasOdd ? this->_vec.back() : 0;

	size_t limit = hasOdd ? this->_vec.size() - 1: this->_vec.size();
	for (size_t i = 0; i < limit; i+= 2)
	{
		if (this->_vec[i] < this->_vec[i + 1]) {
			larger.push_back(this->_vec[i + 1]);
			smaller.push_back(this->_vec[i]);
		} else {
			larger.push_back(this->_vec[i]);
			smaller.push_back(this->_vec[i + 1]);
		}
	}
	this->_vec = larger;
	sortVector();
	larger = this->_vec;

	for (size_t i = 0; i < smaller.size(); i++) {
		std::vector<int>::iterator pos = std::lower_bound(larger.begin(), larger.end(), smaller[i]);
		larger.insert(pos, smaller[i]);
	}
	if (hasOdd) {
		std::vector<int>::iterator pos = std::lower_bound(larger.begin(), larger.end(), oddElement);
		larger.insert(pos, oddElement);		
	}
	this->_vec = larger;
}

PmergeMe::~PmergeMe() {}

void PmergeMe::parseInput(int argc, char **argv)
{
	for (int i = 1; i < argc; i++)
	{
		char *endptr;
		long num = std::strtol(argv[i], &endptr, 10);
		if (*endptr != '\0')
			throw std::runtime_error("Error: invalid input.");
		if (num <= 0)
			throw std::runtime_error("Error: only positive integers.");
		if (num > std::numeric_limits<int>::max())
			throw std::runtime_error("Error: integer overflow.");
		this->_vec.push_back(num);
		this->_deq.push_back(num);
	}
}

void PmergeMe::sort(){}
