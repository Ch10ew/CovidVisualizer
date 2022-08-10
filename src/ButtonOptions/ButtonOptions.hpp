#ifndef BUTTON_OPTIONS_H
#define BUTTON_OPTIONS_H

namespace co
{
    enum ButtonOptions : char
    {
        TOTAL_CONFIRMED = 1,
        SUM_OF_CONFIRMED_WEEK = 2,
        SUM_OF_CONFIRMED_MONTH = 4,
        HIGHEST_LOWEST_DEATH = 8,
        HIGHEST_LOWEST_RECOVERED = 16,
        SEARCH_COUNTRY = 32,
    };

    inline ButtonOptions operator|(ButtonOptions a, ButtonOptions b)
    {
        return static_cast<ButtonOptions>(static_cast<int>(a) | static_cast<int>(b));
    }
} // namespace co

#endif // BUTTON_OPTIONS_H