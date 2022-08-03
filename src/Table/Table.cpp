#include "Table.hpp"

#include "../StringUtils/StringUtils.hpp"

#include <csv.hpp>
#include <imgui.h>
#include <misc/cpp/imgui_stdlib.h>

#include <iostream>
#include <string>
#include <vector>

void co::TableDefault()
{
    static const ImGuiTableFlags TABLE_FLAGS = ImGuiTableFlags_SizingStretchProp | ImGuiTableFlags_RowBg | ImGuiTableFlags_Resizable;

    ImGui::BeginTable("table", 1, TABLE_FLAGS);

    // @TODO: Probably can offset this to different functions to have different tables based on ticked options?
    ImGui::TableSetupColumn("Hi, please select an option above to start displaying data");
    ImGui::TableSetupScrollFreeze(0, 1);
    ImGui::TableHeadersRow();

    ImGui::TableNextRow();
    ImGui::TableSetColumnIndex(0);
    ImGui::Text("No data");

    ImGui::EndTable();
}

void co::TableTotalConfirmed()
{
    csv::CSVReader csvReader("resources/time_series_covid19_confirmed_global.csv");
}

void co::TableSumOfConfirmed()
{
}

void co::TableHighestLowestDeathRecovered()
{
}

void co::TableSearchCountry(std::string searchTerm)
{
}
