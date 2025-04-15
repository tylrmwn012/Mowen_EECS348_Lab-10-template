#include "calculator.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cctype>

// Function to check if a string is a valid double
bool isValidDouble(const std::string& s) {
    bool hasDecimalPoint = false;
    size_t start = 0;

    // Check for optional '+' or '-' sign at the beginning
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
            return false;  // Invalid character encountered
        }
    }

    // A valid double must have at least one digit and if it has a decimal, it must have digits after it
    return hasDigit && (hasDecimalPoint ? s.find('.') < s.length() - 1 : true);
}

// Function to add two string-represented numbers (assumes valid double strings)
std::string addStrings(const std::string& a, const std::string& b) {
    // Simple algorithm to add two string numbers (without converting to double)
    // We will do this by aligning decimal points and adding digit by digit

    // Handle the sign and integer/decimal parts separately
    bool isNegative = false;
    std::string result;

    // Add both numbers digit by digit (starting from the right)
    size_t maxLength = std::max(a.length(), b.length());
    int carry = 0;
    for (int i = maxLength - 1; i >= 0; --i) {
        int digitA = (i < a.length() && std::isdigit(a[i])) ? a[i] - '0' : 0;
        int digitB = (i < b.length() && std::isdigit(b[i])) ? b[i] - '0' : 0;

        int sum = digitA + digitB + carry;
        carry = sum / 10;
        result.insert(result.begin(), (sum % 10) + '0');
    }

    // Handle the case where the sum has a carry left
    if (carry > 0) {
        result.insert(result.begin(), carry + '0');
    }

    return result;
}

// Function to load file lines into a vector of strings
std::vector<std::string> loadFileLines(const std::string& filename) {
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

// Function to parse a number string into a double (for further validation or usage)
double parse_number(const std::string &expression) {
    return std::stod(expression);
}
