#include "calculator.hpp"
#include <fstream>
#include <cctype>
#include <algorithm>

// Utility: Check if a string is a valid double number (without using std::stod)
bool isValidDouble(const std::string& s) {
    int i = 0;
    int n = s.size();

    if (n == 0) return false;

    // Optional sign
    if (s[i] == '+' || s[i] == '-') i++;
    if (i == n) return false;

    bool hasDigits = false;
    while (i < n && isdigit(s[i])) {
        i++;
        hasDigits = true;
    }

    // Optional decimal point
    if (i < n && s[i] == '.') {
        i++;
        bool hasDecimalDigits = false;
        while (i < n && isdigit(s[i])) {
            i++;
            hasDecimalDigits = true;
        }
        return hasDigits && hasDecimalDigits && i == n;
    }

    return hasDigits && i == n;
}

// Utility: Pad two strings with zeros to the same length
void padStrings(std::string &a, std::string &b, bool afterDecimal = true) {
    size_t posA = a.find('.');
    size_t posB = b.find('.');

    if (posA == std::string::npos) {
        a += ".0";
        posA = a.find('.');
    }
    if (posB == std::string::npos) {
        b += ".0";
        posB = b.find('.');
    }

    int intLenA = posA;
    int intLenB = posB;
    int fracLenA = a.length() - posA - 1;
    int fracLenB = b.length() - posB - 1;

    // Pad integer part
    if (intLenA < intLenB) a = std::string(intLenB - intLenA, '0') + a;
    else if (intLenB < intLenA) b = std::string(intLenA - intLenB, '0') + b;

    // Pad fractional part
    if (fracLenA < fracLenB) a += std::string(fracLenB - fracLenA, '0');
    else if (fracLenB < fracLenA) b += std::string(fracLenA - fracLenB, '0');
}

// Utility: Remove leading/trailing zeros and dot if needed
std::string cleanResult(std::string s) {
    // Remove trailing zeros after decimal
    if (s.find('.') != std::string::npos) {
        while (!s.empty() && s.back() == '0') s.pop_back();
        if (!s.empty() && s.back() == '.') s.pop_back();
    }

    // Remove leading zeros before decimal or digits
    int i = 0;
    bool negative = false;
    if (!s.empty() && s[0] == '-') {
        negative = true;
        i++;
    }
    while (i + 1 < (int)s.size() && s[i] == '0' && s[i+1] != '.') s.erase(i, 1);

    return negative ? "-" + s.substr(i) : s.substr(i);
}

// Perform string-based addition of two valid double strings
std::string addStrings(const std::string& aOrig, const std::string& bOrig) {
    std::string a = aOrig;
    std::string b = bOrig;

    bool negA = a[0] == '-';
    bool negB = b[0] == '-';

    if (a[0] == '+' || a[0] == '-') a = a.substr(1);
    if (b[0] == '+' || b[0] == '-') b = b.substr(1);

    padStrings(a, b);

    size_t dotPos = a.find('.');
    a.erase(dotPos, 1);
    b.erase(dotPos, 1);

    std::string result;
    int carry = 0;

    if (negA == negB) {
        for (int i = (int)a.size() - 1; i >= 0; i--) {
            int digit = (a[i] - '0') + (b[i] - '0') + carry;
            result += (digit % 10) + '0';
            carry = digit / 10;
        }
        if (carry) result += (carry + '0');
        std::reverse(result.begin(), result.end());
        result.insert(result.begin() + dotPos, '.');
        if (negA) result = "-" + result;
        return cleanResult(result);
    } else {
        // Use subtraction logic: a - b or b - a
        // Here we just assume a is the larger number and subtract accordingly
        // Full implementation of negative logic is complex, can be added if needed
        return "Signed addition not yet supported for opposite signs";
    }
}

// Load lines from file into vector
std::vector<std::string> loadFileLines(const std::string& filename) {
    std::vector<std::string> lines;
    std::ifstream file(filename);
    std::string line;

    while (std::getline(file, line)) {
        while (!line.empty() && isspace(line.back())) line.pop_back();
        while (!line.empty() && isspace(line.front())) line.erase(line.begin());
        if (!line.empty()) lines.push_back(line);
    }

    return lines;
}

// Dummy implementation (unused in string-based calc)
double parse_number(const std::string& expression) {
    return 0.0;  // Not used
}
