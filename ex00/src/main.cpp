#include "../include/BitcoinExchange.hpp"
#include "../include/color.hpp"

#include <iostream>
#include <fstream>
#include <stdexcept>
#include <string>
#include <cstdio>

static void printSection(const std::string &title)
{
    std::cout << "\n" << BOLD_ON << YELLOW
              << "========== " << title << " =========="
              << RESET << std::endl;
}

static void createDatabase(const std::string &filename)
{
    std::ofstream file(filename.c_str());

    file << "date,exchange_rate\n";
    file << "2024-01-01,10\n";
    file << "2024-01-05,20\n";
    file << "2024-01-10,30\n";
    file << "2024-01-15,40\n";
    file << "2024-02-29,50\n";
    file.close();
}

static void createInput(const std::string &filename)
{
    std::ofstream file(filename.c_str());

    file << "date | value\n";

    // Valid dates
    file << "2024-01-01 | 10\n";
    file << "2024-01-05 | 2\n";
    file << "2024-01-07 | 5\n";
    file << "2024-01-12 | 3.5\n";
    file << "2024-01-20 | 1000\n";

    // Date validation
    file << "2024-02-29 | 10\n";
    file << "2023-02-29 | 10\n";
    file << "1900-02-29 | 10\n";
    file << "2000-02-29 | 10\n";
    file << "2024-13-01 | 10\n";
    file << "2024-04-31 | 10\n";
    file << "2024-00-10 | 10\n";
    file << "202A-01-15 | 10\n";
    file << "2024-1-15 | 10\n";

    // Value validation
    file << "2024-01-20 | 0\n";
    file << "2024-01-20 | -5\n";
    file << "2024-01-20 | 1000.01\n";
    file << "2024-01-20 | abc\n";
    file << "2024-01-20 | 42abc\n";
    file << "2024-01-20 | 42 100\n";

    // Input format validation
    file << "2024-01-20 100\n";
    file << "not-a-date | 10\n";

    // Database lookup
    file << "2023-12-31 | 10\n";
    file << "2024-01-08 | 10\n";
    file << "2024-01-30 | 10\n";

    file.close();
}

static void testDatabase()
{
    printSection("DATABASE TEST");

    BitcoinExchange exchange;

    try
    {
        exchange.loadDataBase("test_database.csv");
        std::cout << GREEN << "Database loaded successfully."
                  << RESET << std::endl;

        exchange.processInput("test_input.txt");
    }
    catch (const std::exception &e)
    {
        std::cerr << RED << e.what() << RESET << std::endl;
    }
}

static void testEmptyDatabase()
{
    printSection("EMPTY DATABASE TEST");

    std::ofstream file("empty_database.csv");
    file << "date,exchange_rate\n";
    file.close();

    BitcoinExchange exchange;

    try
    {
        exchange.loadDataBase("empty_database.csv");
        exchange.processInput("test_input.txt");
    }
    catch (const std::exception &e)
    {
        std::cerr << RED << e.what() << RESET << std::endl;
    }
}

static void testMissingFiles()
{
    printSection("MISSING FILE TEST");

    BitcoinExchange exchange;

    try
    {
        exchange.loadDataBase("missing_database.csv");
    }
    catch (const std::exception &e)
    {
        std::cout << GREEN << "Expected exception: "
                  << e.what() << RESET << std::endl;
    }

    try
    {
        exchange.processInput("missing_input.txt");
    }
    catch (const std::exception &e)
    {
        std::cout << GREEN << "Expected exception: "
                  << e.what() << RESET << std::endl;
    }
}

static void testCopyAndAssignment()
{
    printSection("COPY AND ASSIGNMENT TEST");

    BitcoinExchange original;
    original.loadDataBase("test_database.csv");

    std::cout << CYAN << "\nCopy constructor:" << RESET << std::endl;
    BitcoinExchange copy(original);
    copy.processInput("test_input.txt");

    std::cout << CYAN << "\nAssignment operator:" << RESET << std::endl;
    BitcoinExchange assigned;
    assigned = original;
    assigned.processInput("test_input.txt");

    std::cout << CYAN << "\nSelf assignment:" << RESET << std::endl;
    assigned = assigned;
}

int main()
{
    createDatabase("test_database.csv");
    createInput("test_input.txt");

    testDatabase();
    testEmptyDatabase();
    testMissingFiles();
    testCopyAndAssignment();

    printSection("TESTS FINISHED");

    return 0;
}
