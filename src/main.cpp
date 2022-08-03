#include "Window/Window.hpp"

#include <iostream>

int main(int argc, char** argv)
{
    const int WINDOW_WIDTH = 640;
    const int WINDOW_HEIGHT = 480;
    const char WINDOW_TITLE[] = "CovidVisualizer";

    co::Run(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE);

    return 0;
}
