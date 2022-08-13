#include "DateUtils.hpp"

#include "StringUtils.hpp"

#include <date/date.h>

#include <functional>
#include <string>
#include <vector>

int co::getDaysInDateRange(const std::string& input)
{
    // Build slash splitter
    auto SlashSplit = co::CurrySplit('/');

    // Get Data
    std::vector<std::string> rawDates = Split('-', input);
    std::string lhsRawDate = rawDates[0].substr(0, rawDates[0].size() - 1);
    std::string rhsRawDate = rawDates[1].substr(1);

    // LHS
    std::vector<std::string> lhsDateVector = SlashSplit(lhsRawDate);
    unsigned int lhsD = std::stoi(lhsDateVector[1]);
    unsigned int lhsM = std::stoi(lhsDateVector[0]);
    int lhsY = std::stoi(lhsDateVector[2]);
    date::year_month_day lhsDate = date::day{lhsD} / date::month{lhsM} / date::year{lhsY};

    // RHS
    std::vector<std::string> rhsDateVector = SlashSplit(rhsRawDate);
    unsigned int rhsD = std::stoi(rhsDateVector[1]);
    unsigned int rhsM = std::stoi(rhsDateVector[0]);
    int rhsY = std::stoi(rhsDateVector[2]);
    date::year_month_day rhsDate = date::day{rhsD} / date::month{rhsM} / date::year{rhsY};

    // Calculate difference
    return (date::sys_days{rhsDate} - date::sys_days{lhsDate}).count();
}

bool co::DateCheckMonday(date::year_month_day date)
{
    return date::weekday{date} == date::weekday{1};
}

bool co::DateCheckSunday(date::year_month_day date)
{
    return date::weekday{date} == date::weekday{7};
}

bool co::DateCheckFirstDayOfMonth(date::year_month_day date)
{
    return date.day() == date::day{1};
}

bool co::DateCheckLastDayOfMonth(date::year_month_day date)
{
    return date == date::year_month_day{date.year() / date.month() / date::last};
}
