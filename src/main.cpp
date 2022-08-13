#include "Dataset/Dataset.hpp"
#include "Prolog/Prolog.hpp"
#include "Window/Window.hpp"

#include <SWI-Prolog.h>
#include <SWI-cpp.h>

#include <iostream>

int main(int argc, char** argv)
{
    // Settings
    const int WINDOW_WIDTH = 640;
    const int WINDOW_HEIGHT = 480;
    const char WINDOW_TITLE[] = "CovidVisualizer";

    // Write Prolog Facts. Needs to be done at this point of time due to the Prolog
    // instance working like a command prompt terminal
    co::BuildPrologFacts("resources/data.pl");

    // Initialize the Prolog Engine
    PlEngine& e = co::GetPrologEngine(argv[0]);

    // Actual Window
    co::Run(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE);

    return 0;
}
