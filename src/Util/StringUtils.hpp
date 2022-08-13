#ifndef STRING_UTILS_HPP
#define STRING_UTILS_HPP

#include <functional>
#include <string>
#include <vector>

namespace co
{
    std::vector<std::string> Split(const char& delimiter, const std::string& input);

    std::function<std::vector<std::string>(const std::string& input)> CurrySplit(const char& delimiter);

    inline std::string& TrimLeft(const std::string& delimiters, std::string& s)
    {
        s.erase(0, s.find_first_not_of(delimiters));
        return s;
    }

    inline std::string& TrimRight(const std::string& delimiters, std::string& s)
    {
        s.erase(s.find_last_not_of(delimiters) + 1);
        return s;
    }

    inline std::size_t replace_all(std::string& s, std::string_view from, std::string_view to)
    {
        std::size_t count{};

        for (std::string::size_type pos{};
             s.npos != (pos = s.find(from.data(), pos, from.length()));
             pos += to.length(), ++count)
        {
            s.replace(pos, from.length(), to.data(), to.length());
        }

        return count;
    }
} // namespace co

#endif // STRING_UTILS_HPP
