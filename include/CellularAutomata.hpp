/*
** EPITECH PROJECT, 2020
** CellularAutomata.hpp
** File description:
**
*/

#ifndef GAMEOFLIFE_CELLULARAUTOMATA_HPP
#define GAMEOFLIFE_CELLULARAUTOMATA_HPP

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "CellularArray.hpp"
#include "AssetManager.hpp"
#include <cstring>
#include <thread>
#include <chrono>
#include <algorithm>

#define CDEAD_CELL sf::Color(100, 100, 100)
#define CLIVE_CELL sf::Color(225, 225, 225)

enum class AutomataState : char {
    Editing,
    Processing
};

class CellularAutomata : public sf::Drawable {
public:
    CellularAutomata(const sf::Vector2u &screenSize, const sf::Vector2u &size);
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
    void handleEvent(const sf::Event &event);
    void update(double dt);
private:
    CellularArray _cellular;
    sf::Text _info;
};


#endif //GAMEOFLIFE_CELLULARAUTOMATA_HPP
