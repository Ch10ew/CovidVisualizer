#include "Dataset.hpp"

#include "../Prolog/Prolog.hpp"
#include "../Util/DateUtils.hpp"
#include "../Util/StringUtils.hpp"

#include <csv.hpp>
#include <date/date.h>

#include <execution>
#include <fstream>
#include <functional>
#include <numeric>
#include <string>
#include <vector>

void co::BuildPrologFacts(const std::string& filename)
{
    // WHAT TO DO IN HERE
    // Write the numbers into data.pl
    std::ofstream datapl(filename);

    std::map<std::string, long> mapConfirmed = co::CalculateTotalConfirmed();
    std::for_each(
        mapConfirmed.begin(),
        mapConfirmed.end(),
        [&](const auto& kv)
        {
            std::string keyCopy = kv.first;
            // co::replace_all(keyCopy, ",", "");
            co::replace_all(keyCopy, "'", "\\'");
            datapl << "cases('" << keyCopy << "', " << kv.second << ").\n";
        });
}

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

std::map<std::string, long> co::CalculateTotalConfirmed()
{
    static std::map<std::string, long> data;

    if (data.empty())
    {
        data = CalculateTotal("resources/time_series_covid19_confirmed_global.csv");
    }

    return data;
}

std::map<std::string, std::vector<std::pair<std::string, long>>> co::CalculateTotalByWeek(std::string country)
{
    std::map<std::string, std::vector<std::pair<std::string, long>>> data;

    csv::CSVReader csvReader("resources/time_series_covid19_confirmed_global.csv");

    // Get headers from index 4 to end, these are the dates
    std::vector<std::string> colNames = csvReader.get_col_names();

    // Find out the dates to group, merge into `start date - end date` format
    std::vector<std::string> dateRanges = BuildDateRanges(colNames, DateCheckMonday, DateCheckSunday);

    // Summation into lists based on ranges based on headers
    CalculateCasesCount(csvReader, dateRanges, data, country);

    return data;
}

std::map<std::string, std::vector<std::pair<std::string, long>>> co::CalculateTotalByMonth()
{
    static std::map<std::string, std::vector<std::pair<std::string, long>>> data;

    if (data.empty())
    {
        csv::CSVReader csvReader("resources/time_series_covid19_confirmed_global.csv");

        // Get headers from index 4 to end, these are the dates
        std::vector<std::string> colNames = csvReader.get_col_names();

        // Find out the dates to group, merge into `start date - end date` format
        std::vector<std::string> dateRanges = BuildDateRanges(colNames, DateCheckFirstDayOfMonth, DateCheckLastDayOfMonth);

        // Summation into lists based on ranges based on headers
        CalculateCasesCount(csvReader, dateRanges, data);
    }

    return data;
}

std::map<std::string, std::pair<long, long>> co::CalculateHighestLowestDeath()
{
    static std::map<std::string, std::pair<long, long>> data;

    if (data.empty())
    {
        data = CalculateHighestLowest("resources/time_series_covid19_deaths_global.csv");
    }

    return data;
}

std::map<std::string, std::pair<long, long>> co::CalculateHighestLowestRecovered()
{
    static std::map<std::string, std::pair<long, long>> data;

    if (data.empty())
    {
        data = CalculateHighestLowest("resources/time_series_covid19_recovered_global.csv");
    }

    return data;
}

std::map<std::string, std::pair<long, long>> co::CalculateHighestLowest(std::string filename)
{
    std::map<std::string, std::pair<long, long>> data;

    std::map<std::string, std::vector<long>> rawData;

    csv::CSVReader csvReader(filename);

    // do processing
    csv::CSVRow row;

    while (csvReader.read_row(row))
    {
        std::vector<long> rawRowData;
        rawRowData.resize(row.size() - 4);
        std::transform(
            row.begin() + 4,
            row.end(),
            rawRowData.begin(),
            [](csv::CSVField e)
            {
                return e.template get<long>();
            });

        for (int i = rawRowData.size() - 1; i > 1; --i)
        {
            rawRowData[i] -= rawRowData[i - 1];
            if (rawRowData[i] < 0) // Broken data, reset to dataset minimum
            {
                rawRowData[i] = (i == rawRowData.size() - 1 ? 0 : *std::min_element(rawRowData.begin() + i + 1, rawRowData.end()));
            }

            // Accumulate from previous entry if country already exists, used for countries with state listed like Australia
            if (rawData.count(row[1].get()) > 0)
            {
                rawRowData[i] += rawData[row[1].get()][i];
            }
        }

        rawData[row[1].get()] = rawRowData;
    }

    std::for_each(
        rawData.begin(),
        rawData.end(),
        [&](const auto& kv)
        {
            std::pair<long, long>& rowData = data[kv.first];

            rowData.first = *std::min_element(rawData[kv.first].begin(), rawData[kv.first].end());
            rowData.second = *std::max_element(rawData[kv.first].begin(), rawData[kv.first].end());
        });

    return data;
}

std::map<std::string, std::vector<long>> co::CalculateConfirmedDeathRecovered()
{
    static std::map<std::string, std::vector<long>> data;

    if (data.empty())
    {
        std::map<std::string, long> dataConfirmed = CalculateTotal("resources/time_series_covid19_confirmed_global.csv");
        std::map<std::string, long> dataDeaths = CalculateTotal("resources/time_series_covid19_deaths_global.csv");
        std::map<std::string, long> dataRecovered = CalculateTotal("resources/time_series_covid19_recovered_global.csv");

        std::vector<std::string> countryNames = GetCountryNames();
        std::for_each(
            countryNames.begin(),
            countryNames.end(),
            [&](std::string& e)
            {
                std::vector<long> count;
                count.push_back(dataConfirmed[e]);
                count.push_back(dataDeaths[e]);
                count.push_back(dataRecovered[e]);
                data[e] = count;
            });
    }

    return data;
}

std::vector<std::pair<std::string, long>> co::ProcessPrologResult()
{
    static std::vector<std::pair<std::string, long>> data;

    if (data.empty())
    {
        std::map<std::string, long> mapConfirmed = co::CalculateTotalConfirmed();
        std::string result = co::PrologSortCases(co::GetPrologEngine(""));
        co::TrimLeft("[", result);
        co::TrimRight("]", result);

        csv::CSVFormat format;
        format.delimiter(',')
            .quote('\'');
        auto csvResult = csv::parse(result, format);
        for (const std::string& s : csvResult.get_col_names())
        {
            std::pair<std::string, long> tmp(s, mapConfirmed[s]);
            data.push_back(tmp);
        }
    }

    return data;
}

std::vector<std::string> co::BuildDateRanges(const std::vector<std::string>& colNames, std::function<bool(date::year_month_day)> startDateRangeCondition, std::function<bool(date::year_month_day)> endDateRangeCondition)
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

void co::CalculateCasesCount(csv::CSVReader& csvReader, std::vector<std::string>& dateRanges, std::map<std::string, std::vector<std::pair<std::string, long>>>& data)
{
    csv::CSVRow row;

    while (csvReader.read_row(row))
    {
        std::vector<std::pair<std::string, long>> rawRowData;

        // I have no solution for this using iterators
        for (int i = 4, k = 0; i < row.size(); ++i, ++k)
        {
            rawRowData.push_back(std::pair(dateRanges[k], row[i].template get<long>()));
            int days = getDaysInDateRange(dateRanges[k]);
            for (int j = 0; j < days; ++j)
            {
                ++i;
            }
            (rawRowData.end() - 1)->second -= row[i].template get<long>();
            (rawRowData.end() - 1)->second = abs((rawRowData.end() - 1)->second);

            // Accumulate from previous entry if country already exists, used for countries with state listed like Australia
            if (data.count(row[1].get()) > 0)
            {
                (rawRowData.end() - 1)->second += data[row[1].get()][k].second;
            }
        }

        data[row[1].get()] = rawRowData;
    }
}

void co::CalculateCasesCount(csv::CSVReader& csvReader, std::vector<std::string>& dateRanges, std::map<std::string, std::vector<std::pair<std::string, long>>>& data, std::string country)
{
    csv::CSVRow row;

    while (csvReader.read_row(row))
    {
        if (row[1].get() == country)
        {
            std::vector<std::pair<std::string, long>> rawRowData;

            // I have no solution for this using iterators
            for (int i = 4, k = 0; i < row.size(); ++i, ++k)
            {
                rawRowData.push_back(std::pair(dateRanges[k], row[i].template get<long>()));
                int days = getDaysInDateRange(dateRanges[k]);
                for (int j = 0; j < days; ++j)
                {
                    ++i;
                }
                (rawRowData.end() - 1)->second -= row[i].template get<long>();
                (rawRowData.end() - 1)->second = abs((rawRowData.end() - 1)->second);

                // Accumulate from previous entry if country already exists, used for countries with state listed like Australia
                if (data.count(row[1].get()) > 0)
                {
                    (rawRowData.end() - 1)->second += data[row[1].get()][k].second;
                }
            }

            data[row[1].get()] = rawRowData;
        }
    }
}

std::map<std::string, long> co::CalculateTotal(const std::string& filename)
{
    std::map<std::string, long> data;

    csv::CSVReader csvReader(filename);

    // do processing
    csv::CSVRow row;

    while (csvReader.read_row(row))
    {
        std::vector<long> rowData;
        rowData.resize(row.size() - 4);
        std::transform(
            row.begin() + 4,
            row.end(),
            rowData.begin(),
            [](csv::CSVField e)
            {
                return e.template get<long>();
            });

        data[row[1].get()] += *std::max_element(rowData.begin(), rowData.end());
    }

    return data;
}
