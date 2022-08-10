#ifndef DATASET_HPP
#define DATASET_HPP

#include <csv.hpp>

#include <map>
#include <string>
#include <vector>

namespace co
{
    /**
     * @brief Get unique country names in dataset.
     *
     * @return std::vector<std::string> Country names
     */
    std::vector<std::string> GetCountryNames();

    /**
     * @brief Get total confirmed Covid-19 cases according to country.
     *
     * @return std::vector<std::string> Map of Country - Total Confirmed Cases
     */
    std::map<std::string, long> CalculateTotal();

    /**
     * @brief Compute the sum of confirmed cases by week for each country.
     *
     * Headers are as follows: Country, Week 1, Week 2, ...
     *
     * @return std::vector<std::vector<std::string>> First vector is headers, second vector onwards is data
     */
    std::vector<std::vector<std::string>> CalculateTotalByWeek();

    /**
     * @brief Compute the sum of confirmed cases by month for each country.
     *
     * Headers are as follows: Country, Month 1, Month 2, ...
     *
     * @return std::vector<std::vector<std::string>> First vector is headers, second vector onwards is data
     */
    std::vector<std::vector<std::string>> CalculateTotalByMonth();

    /**
     * @brief Find the highest & lowest death count for each country.
     *
     * Headers are as follows: Country, Lowest Death, Highest Death, Lowest Recovered, Highest Recovered
     *
     * @return std::vector<std::vector<std::string>> Data
     */
    std::map<std::string, std::pair<long long, long long>> CalculateHighestLowestDeath();

    /**
     * @brief Find the highest & lowest recovered count for each country.
     *
     * Headers are as follows: Country, Lowest Recovered, Highest Recovered
     *
     * @return std::vector<std::vector<std::string>> Data
     */
    std::map<std::string, std::pair<long long, long long>> CalculateHighestLowestRecovered();

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
    template <class T>
    std::vector<std::string> BuildDateRanges(const std::vector<std::string>& colNames, T startDateRangeCondition, T endDateRangeCondition);

    /**
     * @brief [INTERNAL] Summation of confirmed cases count into lists based on ranges based on headers
     *
     * @param csvReader reference to initialized csvreader instance
     * @param dateRanges reference to initialized dateRange
     * @param data reference to initialized data
     */
    void CalculateCasesCount(csv::CSVReader& csvReader, std::vector<std::string>& dateRanges, std::vector<std::vector<std::string>>& data);
} // namespace co

#endif // DATASET_HPP
