#ifndef STRING_UTILS_H
#define STRING_UTILS_H

#include <sstream>
#include <string>
#include <vector>

namespace co
{
    std::vector<std::string> split(const std::string& input, const char delimiter)
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
}

#endif // STRING_UTILS_H