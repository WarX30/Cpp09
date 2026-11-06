#pragma once

#include <deque>
#include <vector>

class PmergeMe
{
	private:
		std::vector<int> _vec;
		std::deque<int>	_deq;
	
	// Methode
		void sortVector();
		void sortDeque();
	
	public:
		PmergeMe();
		PmergeMe(const PmergeMe &other);
		PmergeMe &operator=(const PmergeMe &other);
		~PmergeMe();
	
	// Methode
		void parseInput(int argc, char *argv[]);
		void sort();
		void displayBefore() const;
		void displayAfter() const;
};
