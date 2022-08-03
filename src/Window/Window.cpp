#include "Window.hpp"
#include "../ButtonOptions/ButtonOptions.hpp"
#include "../Table/Table.hpp"

#include <SFML/Graphics.hpp>
#include <imgui-SFML.h>
#include <imgui.h>
#include <misc/cpp/imgui_stdlib.h>

#include <stdexcept>
#include <string>

void co::Run(const int width, const int height, const char* title)
{
    sf::RenderWindow window(sf::VideoMode(width, height), title, sf::Style::Titlebar | sf::Style::Close);
    window.setFramerateLimit(60);
    if (!ImGui::SFML::Init(window))
    {
        throw std::runtime_error("co::Run(): ImGui::SFML::Init() failed!");
    }

    sf::Clock deltaClock;
    while (window.isOpen())
    {
        Input(window, deltaClock);
        Update(window, deltaClock);
        Draw(window, deltaClock);
    }

    ImGui::SFML::Shutdown();
}

void co::Input(sf::RenderWindow& window, sf::Clock& deltaClock)
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        ImGui::SFML::ProcessEvent(window, event);

        if (event.type == sf::Event::Closed)
        {
            window.close();
        }
    }
}

void co::Update(sf::RenderWindow& window, sf::Clock& deltaClock)
{
    const int WINDOW_WIDTH = window.getSize().x;
    const int WINDOW_HEIGHT = window.getSize().y;
    static const ImGuiWindowFlags WINDOW_FLAGS = ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_AlwaysVerticalScrollbar;

    ImGui::SFML::Update(window, deltaClock.restart()); // Update step for ImGui

#pragma region ImGui Window

    bool isTableOpen = true;
    ImGui::SetNextWindowPos(ImVec2(0.f, 0.f));
    ImGui::SetNextWindowSize(ImVec2(WINDOW_WIDTH, WINDOW_HEIGHT));
    ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
    ImGui::Begin("window", &isTableOpen, WINDOW_FLAGS);

#pragma region Options

    static ButtonOptions sButtonOptions;
    static std::string rawCountryName = "";
    ButtonOptions buttonOptions = static_cast<ButtonOptions>(0);

    // Stack the flags for this iteration
    buttonOptions = buttonOptions | static_cast<ButtonOptions>(TOTAL_CONFIRMED * ImGui::Button("Display Total Confirmed Covid-19 Cases According to Country"));
    buttonOptions = buttonOptions | static_cast<ButtonOptions>(SUM_OF_CONFIRMED * ImGui::Button("Compute the Sum of Confirmed Cases by Week and Month for Each Country"));
    buttonOptions = buttonOptions | static_cast<ButtonOptions>(HIGHEST_LOWEST_DEATH_RECOVERED * ImGui::Button("Find the Highest/Lowest Death and Recovered Covid-19 Cases as Per Country"));
    buttonOptions = buttonOptions | static_cast<ButtonOptions>(SEARCH_COUNTRY * ImGui::Button("Search/Locate the Country for Covid-19 Cases"));
    ImGui::SameLine();
    ImGui::Text("Country: ");
    ImGui::SameLine();
    ImGui::InputText("Country Search Field", &rawCountryName);
    if (ImGui::Button("Reset"))
    {
        sButtonOptions = static_cast<ButtonOptions>(0);
    }

    // Get active flag only (mutually exclusivity for options)
    sButtonOptions = buttonOptions ? buttonOptions : sButtonOptions;

    /*// Debug
    std::cout << "Input: " << rawCountryName << std::endl;
    std::cout
        << "s1: " << bool(sButtonOptions & 0b00000001)
        << ", s2: " << bool(sButtonOptions & 0b00000010)
        << ", s3: " << bool(sButtonOptions & 0b00000100)
        << ", s4: " << bool(sButtonOptions & 0b00001000) << std::endl;*/

#pragma endregion // Options

#pragma region Table

    switch (sButtonOptions)
    {
    case TOTAL_CONFIRMED:
        TableTotalConfirmed();
        break;
    case SUM_OF_CONFIRMED:
        TableSumOfConfirmed();
        break;
    case HIGHEST_LOWEST_DEATH_RECOVERED:
        TableHighestLowestDeathRecovered();
        break;
    case SEARCH_COUNTRY:
        TableSearchCountry(rawCountryName);
        break;
    default:
        TableDefault();
    }

#pragma endregion // Table

    ImGui::End();
    ImGui::PopStyleVar();

#pragma endregion // ImGui Window
}

void co::Draw(sf::RenderWindow& window, sf::Clock& deltaClock)
{
    window.clear(sf::Color::White);
    ImGui::SFML::Render(window);
    window.display();
}
