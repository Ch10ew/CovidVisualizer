#include "Dataset.hpp"

#include "../Structures/List.hpp"
#include "../Util/DateUtils.hpp"
#include "../Util/StringUtils.hpp"

#include <csv.hpp>
#include <date/date.h>

#include <execution>
#include <numeric>
#include <string>
#include <vector>

std::vector<std::string> co::GetCountryNames()
{
    static std::vector<std::string> data;

    if (data.empty())
    {
        csv::CSVReader csvReader("resources/time_series_covid19_confirmed_global.csv");

        // do processing
        csv::CSVRow row;

        while (csvReader.read_row(row))
        {
            data.push_back(row[1].get());
        }

        data.erase(
            std::unique(data.begin(), data.end()),
            data.end());
    }

    return data;
}

std::map<std::string, long> co::CalculateTotal()
{
    static std::map<std::string, long> data;

    if (data.empty())
    {
        csv::CSVReader csvReader("resources/time_series_covid19_confirmed_global.csv");

        // do processing
        csv::CSVRow row;

        while (csvReader.read_row(row))
        {
            data[row[1].get()] += row[row.size() - 1].template get<long>();
        }
    }

    return data;
}

std::vector<std::vector<std::string>> co::CalculateTotalByWeek()
{
    static std::vector<std::vector<std::string>> data;

    if (data.empty())
    {
        csv::CSVReader csvReader("resources/time_series_covid19_confirmed_global.csv");

        // Get headers from index 4 to end, these are the dates
        std::vector<std::string> colNames = csvReader.get_col_names();

        // Find out the dates to group, merge into `start date - end date` format
        std::vector<std::string> dateRanges = BuildDateRanges(colNames, DateCheckMonday, DateCheckSunday);

        // Add headers into data list
        std::vector<std::string> dateRangesCopy = dateRanges;
        dateRangesCopy.emplace(dateRangesCopy.begin(), "Country");
        data.push_back(dateRangesCopy);

        // Summation into lists based on ranges based on headers
        CalculateCasesCount(csvReader, dateRanges, data);
    }

    return data;
}

std::vector<std::vector<std::string>> co::CalculateTotalByMonth()
{
    static std::vector<std::vector<std::string>> data;

    if (data.empty())
    {
        csv::CSVReader csvReader("resources/time_series_covid19_confirmed_global.csv");

        // Get headers from index 4 to end, these are the dates
        std::vector<std::string> colNames = csvReader.get_col_names();

        // Find out the dates to group, merge into `start date - end date` format
        std::vector<std::string> dateRanges = BuildDateRanges(colNames, DateCheckFirstDayOfMonth, DateCheckLastDayOfMonth);

        // Add headers into data list
        std::vector<std::string> dateRangesCopy = dateRanges;
        dateRangesCopy.emplace(dateRangesCopy.begin(), "Country");
        data.push_back(dateRangesCopy);

        // Summation into lists based on ranges based on headers
        CalculateCasesCount(csvReader, dateRanges, data);
    }

    return data;
}

std::map<std::string, std::pair<long long, long long>> co::CalculateHighestLowestDeath()
{
    static std::map<std::string, std::pair<long long, long long>> data;

    if (data.empty())
    {
        csv::CSVReader csvReader("resources/time_series_covid19_deaths_global.csv");

        // do processing
        csv::CSVRow row;

        while (csvReader.read_row(row))
        {
            std::vector<long long> rawRowData;
            rawRowData.resize(row.size() - 4);
            std::transform(
                row.begin() + 4,
                row.end(),
                rawRowData.begin(),
                [](csv::CSVField e)
                {
                    return e.template get<long long>();
                });

            for (int i = rawRowData.size() - 1; i > 1; --i)
            {
                rawRowData[i] -= rawRowData[i - 1];
                rawRowData[i] = abs(rawRowData[i]);
            }

            std::pair<long long, long long>& rowData = data[row[1].get()];
            rowData.first = rowData.first ? *std::min_element(rawRowData.begin(), rawRowData.end()) : std::min(rowData.first, *std::min_element(rawRowData.begin(), rawRowData.end()));
            rowData.second = std::max(rowData.second, *std::max_element(rawRowData.begin(), rawRowData.end()));
        }
    }

    return data;
}

std::map<std::string, std::pair<long long, long long>> co::CalculateHighestLowestRecovered()
{
    static std::map<std::string, std::pair<long long, long long>> data;

    if (data.empty())
    {
        csv::CSVReader csvReader("resources/time_series_covid19_recovered_global.csv");

        // do processing
        csv::CSVRow row;

        while (csvReader.read_row(row))
        {
            std::vector<long long> rawRowData;
            rawRowData.resize(row.size() - 4);
            std::transform(
                row.begin() + 4,
                row.end(),
                rawRowData.begin(),
                [](csv::CSVField e)
                {
                    return e.template get<long long>();
                });

            for (int i = rawRowData.size() - 1; i > 1; --i)
            {
                rawRowData[i] -= rawRowData[i - 1];
                rawRowData[i] = abs(rawRowData[i]);
            }

            std::pair<long long, long long>& rowData = data[row[1].get()];
            rowData.first = rowData.first ? *std::min_element(rawRowData.begin(), rawRowData.end()) : std::min(rowData.first, *std::min_element(rawRowData.begin(), rawRowData.end()));
            rowData.second = std::max(rowData.second, *std::max_element(rawRowData.begin(), rawRowData.end()));
        }
    }

    return data;
}

template <class T>
std::vector<std::string> co::BuildDateRanges(const std::vector<std::string>& colNames, T startDateRangeCondition, T endDateRangeCondition)
{
    std::vector<std::string> dateRanges;
    std::for_each(
        colNames.begin() + 4,
        colNames.end(),
        [&](std::string e)
        {
            std::vector<std::string> dateVector = Split('/', e);
            unsigned int d = std::stoi(dateVector[1]);
            unsigned int m = std::stoi(dateVector[0]);
            int y = std::stoi(dateVector[2]);
            date::year_month_day a = date::day{d} / date::month{m} / date::year{y};

            // Add initial date
            if (dateRanges.empty())
            {
                dateRanges.push_back(e);
            }

            if (startDateRangeCondition(a))
            {
                dateRanges.push_back(e);
            }
            else if (endDateRangeCondition(a))
            {
                dateRanges.back().append(" - " + e);
            }
        });

    // In case there are dates left
    if (dateRanges.back().find('-') == std::string::npos)
    {
        dateRanges.back().append(" - " + colNames.back());
    }

    return dateRanges;
}

void co::CalculateCasesCount(csv::CSVReader& csvReader, std::vector<std::string>& dateRanges, std::vector<std::vector<std::string>>& data)
{
    csv::CSVRow row;

    while (csvReader.read_row(row))
    {
        // std::vector<int> rawRowData;
        // std::vector<std::string> rowData;
        co::List<int> rawRowData;
        std::vector<std::string> rowData;

        // I have no solution for this using iterators
        /*for (int i = 4, k = 0; i < row.size(); ++i, ++k)
        {
            rawRowData.push_back(row[i].template get<int>());
            int days = getDaysInDateRange(dateRanges[k]);
            for (int j = 0; j < days; ++j)
            {
                ++i;
            }
            rawRowData.back() -= row[i].template get<int>();
            rawRowData.back() = abs(rawRowData.back());
        }*/
        for (int i = 4, k = 0; i < row.size(); ++i, ++k)
        {
            rawRowData.InsertTail(row[i].template get<int>());
            int days = getDaysInDateRange(dateRanges[k]);
            for (int j = 0; j < days; ++j)
            {
                ++i;
            }
            rawRowData.Tail() -= row[i].template get<int>();
            rawRowData.Tail() = abs(rawRowData.Tail());
        }

        // rowData.resize(rawRowData.size()); // allocate space
        rowData.resize(rawRowData.Size()); // allocate space
        std::transform(
            rawRowData.begin(),
            rawRowData.end(),
            rowData.begin(),
            [](int e)
            {
                return std::to_string(e);
            });

        rowData.emplace(rowData.begin(), row[1].get());

        data.push_back(rowData);
    }
}
