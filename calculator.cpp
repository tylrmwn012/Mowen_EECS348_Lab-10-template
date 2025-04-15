#include "calculator.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cctype>

// verify that the string is a valid double
bool validDouble(const std::string& s) {
    bool hasDecimalPoint = false;
    size_t start = 0;

    if (s[0] == '+' || s[0] == '-') {
        start = 1;
    }

    bool hasDigit = false;
    for (size_t i = start; i < s.length(); ++i) {
        if (isdigit(s[i])) {
            hasDigit = true;
        } else if (s[i] == '.' && !hasDecimalPoint) {
            hasDecimalPoint = true;
        } else {
            return false;  
        }
    }

    return hasDigit && (hasDecimalPoint ? s.find('.') < s.length() - 1 : true);
}

// add string-represented numbers if valid
std::string addStrings(const std::string& a, const std::string& b) {

    bool isNegative = false;
    std::string result;

    size_t maxLength = std::max(a.length(), b.length());
    int carry = 0;
    for (int i = maxLength - 1; i >= 0; --i) {
        int digitA = (i < a.length() && std::isdigit(a[i])) ? a[i] - '0' : 0;
        int digitB = (i < b.length() && std::isdigit(b[i])) ? b[i] - '0' : 0;

        int sum = digitA + digitB + carry;
        carry = sum / 10;
        result.insert(result.begin(), (sum % 10) + '0');
    }

    if (carry > 0) {
        result.insert(result.begin(), carry + '0');
    }

    return result;
}

// load file lines into vector of strings
std::vector<std::string> loadLines(const std::string& filename) {
    std::vector<std::string> lines;
    std::ifstream file(filename);

    if (!file) {
        std::cerr << "Could not open the file " << filename << std::endl;
        return lines;
    }

    std::string line;
    while (std::getline(file, line)) {
        lines.push_back(line);
    }

    return lines;
}

double parse_number(const std::string &expression) {
    return std::stod(expression);
}
