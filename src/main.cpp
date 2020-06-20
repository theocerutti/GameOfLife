#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "CellularAutomata.hpp"
#include "ImGUI/imgui.h"
#include "ImGUI/imconfig.h"
#include "ImGUI/imgui-SFML.h"

void setupImGUI(CellularAutomata &cellularAutomata)
{
    ImGui::Begin("Parameters", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
    ImGui::PushItemWidth(200);
    if (cellularAutomata.getState() == AutomataState::Processing)
        ImGui::SliderFloat("Speed", cellularAutomata.getMsUpdatePtr(), 0, 1000, "%.3f ms");
    else
        ImGui::Text("Start process to set animation speed.");
    ImGui::End();
    //ImGui::ShowDemoWindow();
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 800), "GameOfLife", sf::Style::Titlebar | sf::Style::Close);
    window.setFramerateLimit(60);

    ImGui::SFML::Init(window);

    CellularAutomata cellularAutomata(window.getSize(), sf::Vector2u(100, 100));

    sf::Clock deltaClock;
    double deltaTime = 0;
    while (window.isOpen()) {
        sf::Event event{};
        while (window.pollEvent(event)) {
            ImGui::SFML::ProcessEvent(event);
            if (event.type == sf::Event::Closed)
                window.close();
            cellularAutomata.handleEvent(event);
        }

        ImGui::SFML::Update(window, deltaClock.restart());
        cellularAutomata.update(deltaTime);

        setupImGUI(cellularAutomata);

        window.clear();
        window.draw(cellularAutomata);
        ImGui::SFML::Render(window);
        window.display();
        deltaTime = deltaClock.restart().asMilliseconds();
    }
    ImGui::SFML::Shutdown();
    return (0);
}