#ifndef STRING_UTILS_HPP
#define STRING_UTILS_HPP

#include <sstream>
#include <string>
#include <vector>

namespace co
{
    std::vector<std::string> Split(const char delimiter, const std::string& input)
    {
        std::stringstream ss(input);
        std::vector<std::string> result;
        std::string item;
        while (std::getline(ss, item, delimiter))
        {
            result.push_back(item);
        }
        return result;
    }

    auto CurrySplit(const char delimiter)
    {
        return [=](const std::string& input)
        {
            return Split(delimiter, input);
        };
    }
}

#endif // STRING_UTILS_HPP
