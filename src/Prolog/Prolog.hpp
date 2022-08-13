#ifndef PROLOG_HPP
#define PROLOG_HPP

#include <SWI-Prolog.h>
#include <SWI-cpp.h>

#include <iostream>
#include <string>

namespace co
{
    std::string PrologSortCases(PlEngine& e);

    PlEngine& GetPrologEngine(std::string executableName);
} // namespace co

#endif // PROLOG_HPP