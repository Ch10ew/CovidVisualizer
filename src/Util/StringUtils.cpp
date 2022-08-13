#include "StringUtils.hpp"

#include <functional>
#include <sstream>
#include <string>
#include <vector>

std::vector<std::string> co::Split(const char& delimiter, const std::string& input)
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

std::function<std::vector<std::string>(const std::string& input)> co::CurrySplit(const char& delimiter)
{
    return [=](const std::string& input)
    {
        return Split(delimiter, input);
    };
}
