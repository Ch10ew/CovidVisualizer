#include "Table.hpp"

#include "../Dataset/Dataset.hpp"

#include <csv.hpp>
#include <imgui.h>
#include <misc/cpp/imgui_stdlib.h>

#include <map>
#include <string>
#include <vector>

void co::TableDefault()
{
    static const ImGuiTableFlags TABLE_FLAGS = ImGuiTableFlags_SizingStretchProp | ImGuiTableFlags_Resizable | ImGuiTableFlags_ScrollY;

    ImGui::BeginTable("table", 1, TABLE_FLAGS);

    ImGui::TableSetupColumn("Hi, please select an option above to start displaying data");
    ImGui::TableSetupScrollFreeze(0, 1);
    ImGui::TableHeadersRow();

    ImGui::TableNextRow();
    ImGui::TableSetColumnIndex(0);
    ImGui::Text("Disclaimer I am not a data scientist and no context was given with the data other than");
    ImGui::TableNextRow();
    ImGui::TableSetColumnIndex(0);
    ImGui::Text("the source");

    ImGui::EndTable();
}

void co::TableTotalConfirmed()
{
    static const ImGuiTableFlags TABLE_FLAGS = ImGuiTableFlags_SizingStretchProp | ImGuiTableFlags_RowBg | ImGuiTableFlags_Resizable | ImGuiTableFlags_ScrollX | ImGuiTableFlags_ScrollY;

    std::map<std::string, long> data = CalculateTotalConfirmed();

    ImGui::BeginTable("table", 2, TABLE_FLAGS);

    ImGui::TableSetupColumn("Country");
    ImGui::TableSetupColumn("Total Confirmed");
    ImGui::TableSetupScrollFreeze(0, 1);
    ImGui::TableHeadersRow();

    std::for_each(
        data.begin(),
        data.end(),
        [](const auto& kv)
        {
            ImGui::TableNextRow();
            ImGui::TableSetColumnIndex(0);
            ImGui::Text(kv.first.c_str());
            ImGui::TableSetColumnIndex(1);
            ImGui::Text(std::to_string(kv.second).c_str());
        });

    ImGui::EndTable();
}

void co::TableSumOfConfirmedWeek(std::string country)
{
    static const ImGuiTableFlags TABLE_FLAGS = ImGuiTableFlags_SizingStretchProp | ImGuiTableFlags_RowBg | ImGuiTableFlags_Resizable | ImGuiTableFlags_ScrollX | ImGuiTableFlags_ScrollY;

    std::vector<std::vector<std::string>> data = co::CalculateTotalByWeek();

    ImGui::BeginTable("table", 2, TABLE_FLAGS);

    // @TODO: Modify to display by row; headers: Week, Cases Confirmed
    ImGui::TableSetupColumn("Week");
    ImGui::TableSetupColumn("Cases Confirmed");
    ImGui::TableSetupScrollFreeze(0, 1);
    ImGui::TableHeadersRow();

    std::vector<std::string> rowData;
    std::for_each(
        data.begin(),
        data.end(),
        [&](std::vector<std::string> e)
        {
            if (e[0] == country)
            {
                rowData = e;
            }
        });

    for (int i = 1; i < data[0].size(); ++i)
    {
        ImGui::TableNextRow();
        ImGui::TableSetColumnIndex(0);
        ImGui::Text(data[0][i].c_str());
        ImGui::TableSetColumnIndex(1);
        ImGui::Text(rowData[i].c_str());
    }

    ImGui::EndTable();
}

void co::TableSumOfConfirmedMonth(std::string country)
{
    static const ImGuiTableFlags TABLE_FLAGS = ImGuiTableFlags_SizingStretchProp | ImGuiTableFlags_RowBg | ImGuiTableFlags_Resizable | ImGuiTableFlags_ScrollX | ImGuiTableFlags_ScrollY;

    std::vector<std::vector<std::string>> data = co::CalculateTotalByMonth();

    ImGui::BeginTable("table", 2, TABLE_FLAGS);

    // @TODO: Modify to display by row; headers: Month, Cases Confirmed
    ImGui::TableSetupColumn("Month");
    ImGui::TableSetupColumn("Cases Confirmed");
    ImGui::TableSetupScrollFreeze(0, 1);
    ImGui::TableHeadersRow();

    std::vector<std::string> rowData;
    std::for_each(
        data.begin(),
        data.end(),
        [&](std::vector<std::string> e)
        {
            if (e[0] == country)
            {
                rowData = e;
            }
        });

    for (int i = 1; i < data[0].size(); ++i)
    {
        ImGui::TableNextRow();
        ImGui::TableSetColumnIndex(0);
        ImGui::Text(data[0][i].c_str());
        ImGui::TableSetColumnIndex(1);
        ImGui::Text(rowData[i].c_str());
    }

    ImGui::EndTable();
}

void co::TableHighestLowestDeath()
{
    static const ImGuiTableFlags TABLE_FLAGS = ImGuiTableFlags_SizingStretchProp | ImGuiTableFlags_RowBg | ImGuiTableFlags_Resizable | ImGuiTableFlags_ScrollX | ImGuiTableFlags_ScrollY;

    std::map<std::string, std::pair<long, long>> data = co::CalculateHighestLowestDeath();

    ImGui::BeginTable("table", 3, TABLE_FLAGS);

    // @TODO: Modify to display by row; headers: Week, Cases Confirmed
    ImGui::TableSetupColumn("Country");
    ImGui::TableSetupColumn("Lowest");
    ImGui::TableSetupColumn("Highest");
    ImGui::TableSetupScrollFreeze(0, 1);
    ImGui::TableHeadersRow();

    std::for_each(
        data.begin(),
        data.end(),
        [](const auto& kv)
        {
            ImGui::TableNextRow();
            ImGui::TableSetColumnIndex(0);
            ImGui::Text(kv.first.c_str());
            ImGui::TableSetColumnIndex(1);
            ImGui::Text(std::to_string(kv.second.first).c_str());
            ImGui::TableSetColumnIndex(2);
            ImGui::Text(std::to_string(kv.second.second).c_str());
        });

    ImGui::EndTable();
}

void co::TableHighestLowestRecovered()
{
    static const ImGuiTableFlags TABLE_FLAGS = ImGuiTableFlags_SizingStretchProp | ImGuiTableFlags_RowBg | ImGuiTableFlags_Resizable | ImGuiTableFlags_ScrollX | ImGuiTableFlags_ScrollY;

    std::map<std::string, std::pair<long, long>> data = co::CalculateHighestLowestRecovered();

    ImGui::BeginTable("table", 3, TABLE_FLAGS);

    // @TODO: Modify to display by row; headers: Week, Cases Confirmed
    ImGui::TableSetupColumn("Country");
    ImGui::TableSetupColumn("Lowest");
    ImGui::TableSetupColumn("Highest");
    ImGui::TableSetupScrollFreeze(0, 1);
    ImGui::TableHeadersRow();

    std::for_each(
        data.begin(),
        data.end(),
        [](const auto& kv)
        {
            ImGui::TableNextRow();
            ImGui::TableSetColumnIndex(0);
            ImGui::Text(kv.first.c_str());
            ImGui::TableSetColumnIndex(1);
            ImGui::Text(std::to_string(kv.second.first).c_str());
            ImGui::TableSetColumnIndex(2);
            ImGui::Text(std::to_string(kv.second.second).c_str());
        });

    ImGui::EndTable();
}

void co::TableSearchCountry(std::string country)
{
    static const ImGuiTableFlags TABLE_FLAGS = ImGuiTableFlags_SizingStretchProp | ImGuiTableFlags_RowBg | ImGuiTableFlags_Resizable | ImGuiTableFlags_ScrollX | ImGuiTableFlags_ScrollY;

    std::map<std::string, std::vector<long>> data = CalculateConfirmedDeathRecovered();

    ImGui::BeginTable("table", 4, TABLE_FLAGS);

    ImGui::TableSetupColumn("Country");
    ImGui::TableSetupColumn("Total Confirmed");
    ImGui::TableSetupColumn("Total Deaths");
    ImGui::TableSetupColumn("Total Recovered");
    ImGui::TableSetupScrollFreeze(0, 1);
    ImGui::TableHeadersRow();

    if (data.find(country) != data.end())
    {
        ImGui::TableNextRow();
        ImGui::TableSetColumnIndex(0);
        ImGui::Text(country.c_str());
        ImGui::TableSetColumnIndex(1);
        ImGui::Text(std::to_string(data[country][0]).c_str());
        ImGui::TableSetColumnIndex(2);
        ImGui::Text(std::to_string(data[country][1]).c_str());
        ImGui::TableSetColumnIndex(3);
        ImGui::Text(std::to_string(data[country][2]).c_str());
    }

    ImGui::EndTable();
}

void co::TableSortCountry()
{
    static const ImGuiTableFlags TABLE_FLAGS = ImGuiTableFlags_SizingStretchProp | ImGuiTableFlags_RowBg | ImGuiTableFlags_Resizable | ImGuiTableFlags_ScrollX | ImGuiTableFlags_ScrollY;

    std::vector<std::pair<std::string, long>> data = co::ProcessPrologResult();

    ImGui::BeginTable("table", 2, TABLE_FLAGS);

    // @TODO: Modify to display by row; headers: Week, Cases Confirmed
    ImGui::TableSetupColumn("Country");
    ImGui::TableSetupColumn("Cases Confirmed");
    ImGui::TableSetupScrollFreeze(0, 1);
    ImGui::TableHeadersRow();

    std::for_each(
        data.begin(),
        data.end(),
        [](const auto& pair)
        {
            ImGui::TableNextRow();
            ImGui::TableSetColumnIndex(0);
            ImGui::Text(pair.first.c_str());
            ImGui::TableSetColumnIndex(1);
            ImGui::Text(std::to_string(pair.second).c_str());
        });

    ImGui::EndTable();
}
