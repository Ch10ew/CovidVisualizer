#ifndef TABLE_HPP
#define TABLE_HPP

#include <string>

namespace co
{
    /**
     * @brief Default table setup meant to be used in co::Update().
     *
     * Called by co::Update().
     *
     * Contains no data.
     */
    void TableDefault();

    /**
     * @brief Display the total confirmed Covid-19 cases according to country.
     *
     * Called by co::Update().
     */
    void TableTotalConfirmed();

    /**
     * @brief Compute the sum of confirmed cases by week for the provided country.
     *
     * Called by co::Update().
     */
    void TableSumOfConfirmedWeek(std::string country);

    /**
     * @brief Compute the sum of confirmed cases by month for the provided country.
     *
     * Called by co::Update().
     */
    void TableSumOfConfirmedMonth(std::string country);

    /**
     * @brief Find the highest/lowest death Covid-19 cases as per country.
     *
     * Called by co::Update().
     */
    void TableHighestLowestDeath();

    /**
     * @brief Find the highest/lowest recovered Covid-19 cases as per country.
     *
     * Called by co::Update().
     */
    void TableHighestLowestRecovered();

    /**
     * @brief Search/locate the country for Covid-19 cases covering confirmed, death and recovered cases.
     *
     * Called by co::Update().
     *
     * @param searchTerm Filter
     */
    void TableSearchCountry(std::string country);
} // namespace co

#endif // TABLE_HPP
