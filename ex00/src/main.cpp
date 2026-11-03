// #include "../include/BitcoinExchange.hpp"
// #include "../include/color.hpp"
//
// #include <iostream>
// #include <fstream>
// #include <exception>
// #include <string>
//
// static void printSection(const std::string &title)
// {
//     std::cout << "\n" << BOLD_ON YELLOW
//               << "========== " << title << " =========="
//               << RESET << std::endl;
// }
//
// static void createDatabase(const std::string &filename)
// {
//     std::ofstream file(filename.c_str());
//
//     if (!file.is_open())
//         throw std::runtime_error("Cannot create test database.");
//
//     file << "date,exchange_rate\n";
//
//     file << "2024-01-01,10\n";
//     file << "2024-01-05,20\n";
//     file << "2024-01-10,30\n";
//     file << "2024-01-15,40\n";
//     file << "2024-02-29,50\n";
//
//     // Duplicate date: the original value must remain unchanged.
//     file << "2024-01-01,99\n";
//
//     // Invalid database entries.
//     file << "2024-01-XX,30\n";
//     file << "2024-01-02,abc\n";
//     file << "2024-01-03,12abc\n";
//     file << "2024-01-04,-10\n";
//     file << "invalid_line\n";
//
//     file.close();
// }
//
// static void createInput(const std::string &filename)
// {
//     std::ofstream file(filename.c_str());
//
//     if (!file.is_open())
//         throw std::runtime_error("Cannot create test input.");
//
//     file << "date | value\n";
//
//     // Valid dates and values.
//     file << "2024-01-01 | 10\n";
//     file << "2024-01-05 | 2\n";
//     file << "2024-01-07 | 5\n";
//     file << "2024-01-12 | 3.5\n";
//     file << "2024-01-20 | 1000\n";
//     file << "2024-02-29 | 10\n";
//     file << "2024-01-01 | 0\n";
//     file << "2024-01-01 | 0.001\n";
//
//     // Invalid calendar dates.
//     file << "2023-02-29 | 10\n";
//     file << "1900-02-29 | 10\n";
//     file << "2024-02-30 | 10\n";
//     file << "2024-13-01 | 10\n";
//     file << "2024-04-31 | 10\n";
//     file << "2024-00-10 | 10\n";
//     file << "2024-1-01 | 10\n";
//     file << "abcd-01-01 | 10\n";
//
//     // Valid leap-year cases.
//     file << "2000-02-29 | 10\n";
//     file << "2024-02-29 | 10\n";
//
//     // Invalid values.
//     file << "2024-01-01 | -5\n";
//     file << "2024-01-01 | -0.5\n";
//     file << "2024-01-01 | 1000.01\n";
//     file << "2024-01-01 | 1001\n";
//     file << "2024-01-01 | abc\n";
//     file << "2024-01-01 | 42abc\n";
//     file << "2024-01-01 | 42 100\n";
//     file << "2024-01-01 |\n";
//
//     // Invalid input format.
//     file << "2024-01-20 100\n";
//     file << "2024-01-01|10\n";
//     file << "2024-01-01 | 10 | 20\n";
//     file << "not-a-date | 10\n";
//
//     // Database lookup boundaries.
//     file << "2023-12-31 | 10\n";
//     file << "2024-01-08 | 10\n";
//     file << "2024-03-01 | 10\n";
//
//     file.close();
// }
//
// static void testDatabase()
// {
//     printSection("DATABASE AND INPUT TESTS");
//
//     BitcoinExchange btc;
//
//     btc.loadDataBase("test_database.csv");
//     btc.processInput("test_input.txt");
// }
//
// static void testEmptyDatabase()
// {
//     printSection("EMPTY DATABASE TEST");
//
//     std::ofstream file("empty_database.csv");
//     if (!file.is_open())
//         throw std::runtime_error("Cannot create empty database.");
//
//     file << "date,exchange_rate\n";
//     file.close();
//
//     BitcoinExchange btc;
//
//     btc.loadDataBase("empty_database.csv");
//     btc.processInput("test_input.txt");
// }
//
// static void testMissingDatabase()
// {
//     printSection("MISSING DATABASE TEST");
//
//     BitcoinExchange btc;
//
//     try
//     {
//         btc.loadDataBase("missing_database.csv");
//         std::cout << RED << "ERROR: missing database was accepted."
//                   << RESET << std::endl;
//     }
//     catch (const std::exception &e)
//     {
//         std::cout << GREEN << "Expected exception: "
//                   << e.what() << RESET << std::endl;
//     }
// }
//
// static void testMissingInput()
// {
//     printSection("MISSING INPUT TEST");
//
//     BitcoinExchange btc;
//
//     try
//     {
//         btc.loadDataBase("test_database.csv");
//         btc.processInput("missing_input.txt");
//         std::cout << RED << "ERROR: missing input was accepted."
//                   << RESET << std::endl;
//     }
//     catch (const std::exception &e)
//     {
//         std::cout << GREEN << "Expected exception: "
//                   << e.what() << RESET << std::endl;
//     }
// }
//
// static void testCopyAndAssignment()
// {
//     printSection("COPY AND ASSIGNMENT TEST");
//
//     BitcoinExchange original;
//     original.loadDataBase("test_database.csv");
//
//     BitcoinExchange copy(original);
//     BitcoinExchange assigned;
//
//     assigned = original;
//     assigned = assigned;
//
//     std::cout << GREEN << "Copy and assignment completed."
//               << RESET << std::endl;
//
//     std::cout << CYAN << "Checking copied objects:"
//               << RESET << std::endl;
//
//     copy.processInput("copy_input.txt");
//     assigned.processInput("copy_input.txt");
// }
//
// int main(void)
// {
//     try
//     {
//         createDatabase("test_database.csv");
//         createInput("test_input.txt");
//
//         // A small input file for copy tests.
//         std::ofstream file("copy_input.txt");
//         if (!file.is_open())
//             throw std::runtime_error("Cannot create copy input.");
//
//         file << "date | value\n";
//         file << "2024-01-01 | 2\n";
//         file << "2024-01-08 | 3\n";
//         file.close();
//
//         testDatabase();
//         testEmptyDatabase();
//         testMissingDatabase();
//         testMissingInput();
//         testCopyAndAssignment();
//     }
//     catch (const std::exception &e)
//     {
//         std::cerr << RED << "Fatal test error: "
//                   << e.what() << RESET << std::endl;
//         return 1;
//     }
//
//     printSection("ALL TESTS FINISHED");
//     return 0;
// }


#include "../include/BitcoinExchange.hpp"

#include <iostream>
#include <exception>

int main(int ac, char **av)
{
    if (ac != 2)
    {
        std::cerr << "Usage: ./btc <input_file>" << std::endl;
        return 1;
    }

    BitcoinExchange btc;

    try
    {
        btc.loadDataBase("data.csv");
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
        return 1;
    }

    try
    {
        btc.processInput(av[1]);
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
        return 1;
    }

    return 0;
}
