#include <imgui-SFML.h>
#include <imgui.h>

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>

#include <csv.h>

#include <SWI-Prolog.h>
#include <SWI-Stream.h>

#include <iostream>

int main(int argc, char** argv)
{
    const int WINDOW_WIDTH = 640;
    const int WINDOW_HEIGHT = 480;
    std::cout << "Hello World!" << std::endl;

    PL_initialise(argc, argv);

    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "ImGui + SFML = <3", sf::Style::Titlebar | sf::Style::Close);
    window.setFramerateLimit(60);
    if (!ImGui::SFML::Init(window))
    {
        return -1;
    }

    sf::Clock deltaClock;
    while (window.isOpen())
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

        ImGui::SFML::Update(window, deltaClock.restart());

        // Table Headers
        bool isTableOpen = true;
        ImGui::SetNextWindowPos(ImVec2(0.f, 0.f));
        ImGui::SetNextWindowSize(ImVec2(WINDOW_WIDTH, WINDOW_HEIGHT));
        ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
        static ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_AlwaysVerticalScrollbar | ImGuiWindowFlags_AlwaysAutoResize;
        static ImGuiTableFlags table_flags = ImGuiTableFlags_SizingStretchProp | ImGuiTableFlags_RowBg | ImGuiTableFlags_Resizable;
        ImGui::Begin("Table test", &isTableOpen, window_flags);
        ImGui::BeginTable("Table?", 3, table_flags);

        io::CSVReader<3> in("../test.csv");
        std::string headers[3]{""};
        in.read_row(headers[0], headers[1], headers[2]);
        ImGui::TableSetupColumn(headers[0].c_str(), ImGuiTableColumnFlags_NoHide);
        ImGui::TableSetupColumn(headers[1].c_str());
        ImGui::TableSetupColumn(headers[2].c_str());
        ImGui::TableSetupScrollFreeze(0, 1);
        ImGui::TableHeadersRow();

        // Table Data
        int data[3] = {0, 0, 0};
        for (int row = 0; row < 100; ++row)
        {
            in.read_row(data[0], data[1], data[2]);
            ImGui::TableNextRow();
            for (int col = 0; col < 3; ++col)
            {
                ImGui::TableSetColumnIndex(col);
                ImGui::Text("%d", data[col]);
            }
        }

        // Table End
        ImGui::EndTable();
        ImGui::End();
        ImGui::PopStyleVar();

        window.clear(sf::Color::White);
        ImGui::SFML::Render(window);
        window.display();
    }

    ImGui::SFML::Shutdown();

    return 0;
}
