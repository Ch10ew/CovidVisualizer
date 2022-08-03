#ifndef BUTTON_OPTIONS_H
#define BUTTON_OPTIONS_H

namespace co
{
    enum ButtonOptions : char
    {
        TOTAL_CONFIRMED = 1,
        SUM_OF_CONFIRMED = 2,
        HIGHEST_LOWEST_DEATH_RECOVERED = 4,
        SEARCH_COUNTRY = 8,
    };

    inline ButtonOptions operator|(ButtonOptions a, ButtonOptions b)
    {
        return static_cast<ButtonOptions>(static_cast<int>(a) | static_cast<int>(b));
    }
} // namespace co

#endif // BUTTON_OPTIONS_H