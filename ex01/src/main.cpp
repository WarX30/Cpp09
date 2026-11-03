#include "../include/RPN.hpp"
#include "../include/color.hpp"

#include <iostream>
#include <string>
#include <exception>

static void printSection(const std::string &title)
{
    std::cout << "\n" << BOLD_ON YELLOW
              << "========== " << title << " =========="
              << RESET << std::endl;
}

static void testValidExpression(
    RPN &rpn, const std::string &expression, int expected)
{
    std::cout << CYAN << "Expression: " << expression << RESET;

    try
    {
        int result = rpn.evaluate(expression);
        std::cout << " | Result: " << GREEN << result << RESET;

        if (result == expected)
            std::cout << GREEN << " [OK]" << RESET << std::endl;
        else
            std::cout << RED << " [FAILED: expected "
                      << expected << "]" << RESET << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cout << RED << " [UNEXPECTED ERROR: "
                  << e.what() << "]" << RESET << std::endl;
    }
}

static void testInvalidExpression(
    RPN &rpn, const std::string &expression)
{
    std::cout << CYAN << "Expression: " << expression << RESET;

    try
    {
        int result = rpn.evaluate(expression);
        std::cout << RED << " [FAILED: accepted, result = "
                  << result << "]" << RESET << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cout << GREEN << " [OK: rejected - "
                  << e.what() << "]" << RESET << std::endl;
    }
}

static void testArithmetic(RPN &rpn)
{
    printSection("ARITHMETIC TESTS");

    testValidExpression(rpn, "0 0 +", 0);
    testValidExpression(rpn, "9 9 +", 18);
    testValidExpression(rpn, "9 9 *", 81);
    testValidExpression(rpn, "9 2 -", 7);
    testValidExpression(rpn, "2 9 -", -7);
    testValidExpression(rpn, "9 2 /", 4);
    testValidExpression(rpn, "2 9 /", 0);
    testValidExpression(rpn, "1 2 + 3 + 4 +", 10);
    testValidExpression(rpn, "1 2 + 3 4 + *", 21);
    testValidExpression(rpn, "5 1 2 + 4 * + 3 -", 14);
}

static void testInvalidFormat(RPN &rpn)
{
    printSection("INVALID FORMAT TESTS");

    testInvalidExpression(rpn, "");
    testInvalidExpression(rpn, " ");
    testInvalidExpression(rpn, " 1 2 +");
    testInvalidExpression(rpn, "1 2 + ");
    testInvalidExpression(rpn, "1  2 +");
    testInvalidExpression(rpn, "1 2+");
    testInvalidExpression(rpn, "12+");
    testInvalidExpression(rpn, "1 a +");
    testInvalidExpression(rpn, "1 2 &");
    testInvalidExpression(rpn, "10 2 +");
    testInvalidExpression(rpn, "1\t2 +");
}

static void testInvalidRPN(RPN &rpn)
{
    printSection("INVALID RPN TESTS");

    testInvalidExpression(rpn, "1 +");
    testInvalidExpression(rpn, "1 2 3 +");
    testInvalidExpression(rpn, "1 2 + +");
    testInvalidExpression(rpn, "1 0 /");
    testInvalidExpression(rpn, "1 2 + 3");
    testInvalidExpression(rpn, "+ 1 2");
}

static void testRepeatedEvaluation(RPN &rpn)
{
    printSection("REPEATED EVALUATION TEST");

    testValidExpression(rpn, "1 2 +", 3);
    testInvalidExpression(rpn, "1 2 3 +");
    testValidExpression(rpn, "8 2 -", 6);
    testValidExpression(rpn, "8 2 /", 4);
}

static void testCopyAndAssignment(RPN &original)
{
    printSection("COPY AND ASSIGNMENT TEST");

    RPN copy(original);
    RPN assigned;

    assigned = original;
    assigned = assigned;

    testValidExpression(copy, "5 1 2 + 4 * + 3 -", 14);
    testValidExpression(assigned, "8 2 -", 6);
}

int main(void)
{
    RPN rpn;

    testArithmetic(rpn);
    testInvalidFormat(rpn);
    testInvalidRPN(rpn);
    testRepeatedEvaluation(rpn);
    testCopyAndAssignment(rpn);

    printSection("ALL TESTS FINISHED");

    return 0;
}

// #include "../include/RPN.hpp"
//
// #include <iostream>
// #include <exception>
// #include <string>
//
// int main(int ac, char **av)
// {
//     if (ac != 2)
//     {
//         std::cerr << "Error" << std::endl;
//         return 1;
//     }
//
//     try
//     {
//         RPN rpn;
//         int result = rpn.evaluate(av[1]);
//
//         std::cout << result << std::endl;
//     }
//     catch (const std::exception &e)
//     {
//         (void)e;
//         std::cerr << "Error" << std::endl;
//         return 1;
//     }
//
//     return 0;
// }
