#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "CellularAutomata.hpp"

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 800), "GameOfLife", sf::Style::Titlebar | sf::Style::Close);
    CellularAutomata cellularAutomata(window.getSize(), sf::Vector2u(100, 100));

    while (window.isOpen()) {
        sf::Event event{};
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            cellularAutomata.handleEvent(event);
        }
        window.clear();
        cellularAutomata.update();
        window.draw(cellularAutomata);
        window.display();
    }
    return (0);
}