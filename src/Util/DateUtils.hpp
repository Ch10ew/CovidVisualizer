#ifndef DATE_UTILS_HPP
#define DATE_UTILS_HPP

#include "StringUtils.hpp"

#include <date/date.h>

#include <string>
#include <vector>

namespace co
{
    /**
     * @brief Get the number of days in the given date range
     *
     * @param input Date range in the format `start date - end date`, where date is in the format `M/D/YY`
     * @return int days in the given date range
     */
    int getDaysInDateRange(const std::string& input);

    bool DateCheckMonday(date::year_month_day date);

    bool DateCheckSunday(date::year_month_day date);

    bool DateCheckFirstDayOfMonth(date::year_month_day date);

    bool DateCheckLastDayOfMonth(date::year_month_day date);
}

#endif // DATE_UTILS_HPP
