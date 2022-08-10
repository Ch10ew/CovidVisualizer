#include "Window.hpp"

#include "../ButtonOptions/ButtonOptions.hpp"
#include "../Dataset/Dataset.hpp"
#include "../Table/Table.hpp"

#include <SFML/Graphics.hpp>
#include <imgui-SFML.h>
#include <imgui.h>
#include <misc/cpp/imgui_stdlib.h>

#include <cstring>
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
    static const ImGuiWindowFlags WINDOW_FLAGS = ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoNav;

    ImGui::SFML::Update(window, deltaClock.restart()); // Update step for ImGui

#pragma region ImGui Window

    bool isTableOpen = true;
    ImGui::SetNextWindowPos(ImVec2(0.f, 0.f));
    ImGui::SetNextWindowSize(ImVec2(WINDOW_WIDTH, WINDOW_HEIGHT));
    ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
    ImGui::Begin("window", &isTableOpen, WINDOW_FLAGS);

#pragma region Options

    static ButtonOptions sButtonOptions;
    static int listboxCurrentSelection = 0;
    ButtonOptions buttonOptions = static_cast<ButtonOptions>(0);

    // Stack the flags for this iteration
    buttonOptions = buttonOptions | static_cast<ButtonOptions>(TOTAL_CONFIRMED * ImGui::Button("Display Total Confirmed Covid-19 Cases According to Country"));
    buttonOptions = buttonOptions | static_cast<ButtonOptions>(SUM_OF_CONFIRMED_WEEK * ImGui::Button("Compute the Sum of Confirmed Cases by Week for Country"));
    ImGui::SameLine();
    ImGui::Text("(Uses Country Dropdown)");
    buttonOptions = buttonOptions | static_cast<ButtonOptions>(SUM_OF_CONFIRMED_MONTH * ImGui::Button("Compute the Sum of Confirmed Cases by Month for Country"));
    ImGui::SameLine();
    ImGui::Text("(Uses Country Dropdown)");
    buttonOptions = buttonOptions | static_cast<ButtonOptions>(HIGHEST_LOWEST_DEATH * ImGui::Button("Find the Highest/Lowest Death Covid-19 Cases as Per Country"));
    buttonOptions = buttonOptions | static_cast<ButtonOptions>(HIGHEST_LOWEST_RECOVERED * ImGui::Button("Find the Highest/Lowest Recovered Covid-19 Cases as Per Country"));
    buttonOptions = buttonOptions | static_cast<ButtonOptions>(SEARCH_COUNTRY * ImGui::Button("Search/Locate the Country for Covid-19 Cases"));
    ImGui::SameLine();
    ImGui::Text("(Uses Country Dropdown)");

    std::vector<std::string> countryNamesStrVector = GetCountryNames();
    std::vector<const char*> countryNamesCharVector;
    for (int i = 0; i < countryNamesStrVector.size(); ++i)
    {
        countryNamesCharVector.push_back(countryNamesStrVector[i].c_str());
    }

    ImGui::ListBox("Country\n(single select)", &listboxCurrentSelection, countryNamesCharVector.data(), countryNamesCharVector.size());
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
    case SUM_OF_CONFIRMED_WEEK:
        TableSumOfConfirmedWeek(countryNamesStrVector[listboxCurrentSelection]);
        break;
    case SUM_OF_CONFIRMED_MONTH:
        TableSumOfConfirmedMonth(countryNamesStrVector[listboxCurrentSelection]);
        break;
    case HIGHEST_LOWEST_DEATH:
        TableHighestLowestDeath();
        break;
    case HIGHEST_LOWEST_RECOVERED:
        TableHighestLowestRecovered();
        break;
    case SEARCH_COUNTRY:
        TableSearchCountry(countryNamesStrVector[listboxCurrentSelection]);
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
