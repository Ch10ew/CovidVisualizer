#include "Prolog.hpp"

#include "../Dataset/Dataset.hpp"

#include <SWI-Prolog.h>
#include <SWI-cpp.h>

#include <string>
#include <vector>

std::string co::PrologSortCases(PlEngine& engine)
{
    try
    {

#pragma region Prolog Interface

        // WHAT TO DO IN PROLOG
        // (1) call `consult('data.pl').`
        PlTermv dataConsultArgv(1);
        dataConsultArgv[0] = "resources/data.pl";
        PlCall("consult", dataConsultArgv);

        // (2) call `consult('sort.pl').`
        PlTermv sortConsultArgv(1);
        sortConsultArgv[0] = "resources/sort.pl";
        PlCall("consult", sortConsultArgv);

        // (2.5) Make prolog print in full?
        PlTermv printSettingsArgv(2);
        printSettingsArgv[0] = "answer_write_options";
        printSettingsArgv[1] = "[ quoted(true), portray(true), spacing(next_argument) ]";
        PlCall("set_prolog_flag", printSettingsArgv);

        // (3) call `getSorted().`
        PlTermv av(1);
        PlCall("get_sorted", av);

#pragma endregion

        // WHAT TO DO IN HERE
        // Process results
        std::string rawResult = (char*)av[0];
        return rawResult;
    }
    catch (PlException& e)
    {
        std::cerr << (char*)e << std::endl;
    }

    return "";
}

/**
 * @brief Get persistent prolog engine instance.
 *
 * Please use this instead of creating a new PlEngine.
 *
 * @param argv argv supplied into program. PlEngine needs the executable name.
 * @return PlEngine& Reference to persistent prolog engine instance.
 */
PlEngine& co::GetPrologEngine(std::string executableName)
{
    static std::string arg;
    if (!executableName.empty())
    {
        arg = executableName;
    }

    std::vector<char> cstr(arg.c_str(), arg.c_str() + arg.size() + 1);
    static PlEngine engine(cstr.data());
    return engine;
}
