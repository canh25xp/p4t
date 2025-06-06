#pragma once

#include <string>
#include <array>
#include <vector>

class STDHelpers {
public:
    static bool EndsWith(const std::string &str, const std::string &checkStr);
    static bool StartsWith(const std::string &str, const std::string &checkStr);
    static bool Contains(const std::string &str, const std::string &subStr);
    static void Erase(std::string &source, const std::string &subStr);
    static void StripSurrounding(std::string &source, const char c);

    // Split the source into two strings at the first character 'c' after position 'startAt'.  The 'c' character is
    // not included in the returned strings.  Text before the 'startAt' will not be included.
    static std::array<std::string, 2> SplitAt(const std::string &source, const char c, const size_t startAt = 0);
    static std::vector<std::string> SplitOnDelim(const std::string &source, const char delim);
};
