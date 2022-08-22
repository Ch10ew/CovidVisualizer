#ifndef DATASET_HPP
#define DATASET_HPP

#include <csv.hpp>
#include <date/date.h>

#include <fstream>
#include <functional>
#include <map>
#include <string>
#include <vector>

namespace co
{
    /**
     * @brief Writes prolog facts of cases in `filename`.
     *
     * @param filename File to write to.
     */
    void BuildPrologFacts(const std::string& filename);

    /**
     * @brief Get unique country names in dataset.
     *
     * @return std::vector<std::string> Country names
     */
    std::vector<std::string> GetCountryNames();

    /**
     * @brief Get total confirmed Covid-19 cases according to country.
     *
     * @return std::map<std::string, long> Map of Country - Total Confirmed Cases
     */
    std::map<std::string, long> CalculateTotalConfirmed();

    /**
     * @brief Compute the sum of confirmed cases by week for each country.
     *
     * @return std::map<std::string, std::vector<std::pair<std::string, long>>> Map of country to data
     */
    std::map<std::string, std::vector<std::pair<std::string, long>>> CalculateTotalByWeek(std::string country);

    /**
     * @brief Compute the sum of confirmed cases by month for each country.
     *
     * @return std::map<std::string, std::vector<std::pair<std::string, long>>> Map of country to data
     */
    std::map<std::string, std::vector<std::pair<std::string, long>>> CalculateTotalByMonth();

    /**
     * @brief Find the highest & lowest death count for each country.
     *
     * Headers are as follows: Country, Lowest Death, Highest Death
     *
     * @return std::map<std::string, std::pair<long, long>> Data
     */
    std::map<std::string, std::pair<long, long>> CalculateHighestLowestDeath();

    /**
     * @brief Find the highest & lowest recovered count for each country.
     *
     * Headers are as follows: Country, Lowest Recovered, Highest Recovered
     *
     * @return std::map<std::string, std::pair<long, long>> Data
     */
    std::map<std::string, std::pair<long, long>> CalculateHighestLowestRecovered();

    /**
     * @brief [INTERNAL] Find the highest & lowest count for each country based on the file given.
     *
     * Headers are as follows: Country, Lowest, Highest
     *
     * @param filename File to read from
     * @return std::map<std::string, std::pair<long, long>> Data
     */
    std::map<std::string, std::pair<long, long>> CalculateHighestLowest(std::string filename);

    /**
     * @brief Find the total confirmed, death, recovered count for each country.
     *
     * Headers for data are as follows: Confirmed, Deaths, Recovered
     *
     * @return std::map<std::string, std::vector<long>> Map of Country - Data
     */
    std::map<std::string, std::vector<long>> CalculateConfirmedDeathRecovered();

    /**
     * @brief Uses Prolog to sort the countries by cases, which Prolog will return a string in the sorted order.
     *
     * @return std::vector<std::pair<std::string, long>> Sorted List of Countries by Confirmed Cases
     */
    std::vector<std::pair<std::string, long>> ProcessPrologResult();

    /**
     * @brief [INTERNAL] Build Date Ranges.
     *
     * Find out the dates to group, merge into `start date - end date` format
     *
     * @tparam T boolean returning function that takes a `date::year_month_day` argument
     * @param colNames reference to column names (to extract dates from)
     * @param startDateRangeCondition condition to start a date range
     * @param endDateRangeCondition condition to end a date range
     * @return std::vector<std::string>
     */
    std::vector<std::string> BuildDateRanges(const std::vector<std::string>& colNames, std::function<bool(date::year_month_day)> startDateRangeCondition, std::function<bool(date::year_month_day)> endDateRangeCondition);

    /**
     * @brief [INTERNAL] Summation of confirmed cases count into lists based on ranges based on headers
     *
     * @param csvReader reference to initialized csvreader instance
     * @param dateRanges reference to initialized dateRange
     * @param data reference to initialized data
     */
    void CalculateCasesCount(csv::CSVReader& csvReader, std::vector<std::string>& dateRanges, std::map<std::string, std::vector<std::pair<std::string, long>>>& data);

    /**
     * @brief [INTERNAL] Summation of confirmed cases count into lists based on ranges based on headers
     *
     * Overload for specific country
     *
     * @param csvReader reference to initialized csvreader instance
     * @param dateRanges reference to initialized dateRange
     * @param data reference to initialized data
     * @param country country to filter
     */
    void CalculateCasesCount(csv::CSVReader& csvReader, std::vector<std::string>& dateRanges, std::map<std::string, std::vector<std::pair<std::string, long>>>& data, std::string country);

    /**
     * @brief [INTERNAL] Get
     *
     * @return std::map<std::string, long> Map of Country - Total X Cases
     */
    std::map<std::string, long> CalculateTotal(const std::string& filename);
} // namespace co

#endif // DATASET_HPP
