#ifndef TABLE_H
#define TABLE_H

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
     * @brief Compute the sum of confirmed cases by week and month for each country.
     *
     * Called by co::Update().
     */
    void TableSumOfConfirmed();

    /**
     * @brief Find the highest/lowest death and recovered Covid-19 cases as per country.
     *
     * Called by co::Update().
     */
    void TableHighestLowestDeathRecovered();

    /**
     * @brief Search/locate the country for Covid-19 cases covering confirmed, death and recovered cases.
     *
     * Called by co::Update().
     *
     * @param searchTerm Filter
     */
    void TableSearchCountry(std::string searchTerm);
} // namespace co

#endif // TABLE_H
