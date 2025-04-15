#ifndef __CALCULATOR_HPP
#define __CALCULATOR_HPP

#include <string>
#include <vector>

bool isValidDouble(const std::string& s);
std::string addStrings(const std::string& a, const std::string& b);
std::vector<std::string> loadFileLines(const std::string& filename);
// this function should expect that `expression` has already been
// validated and thus throw no exceptions
double parse_number(const std::string &expression);

#endif // __CALCULATOR_HPP
