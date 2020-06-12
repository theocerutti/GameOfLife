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
#include <cstring>
#include <thread>
#include <chrono>
#include <algorithm>

class CellularAutomata : public sf::Drawable {
public:
    enum class StateCell : char {
        Live,
        Dead
    };

    enum class AutomataState : char {
        Editing,
        Processing
    };
public:
    CellularAutomata(const sf::Vector2u &screenSize, const sf::Vector2u &size);
    ~CellularAutomata();
    void invertCellState(int xRelative, int yRelativ);
    void update();
    void handleEvent(const sf::Event &event, const sf::Vector2i &posMouse);
    void draw(sf::RenderTarget &target, sf::RenderStates states) const;
private:
    StateCell getStateCell(int x, int y) const;
    void setStateCell(int x, int y, const StateCell &state);
    int getNbNeighborsLiving(int x, int y);
    StateCell getNeighbor(int x, int y, int xAdd, int yAdd);
private:
    StateCell _actual_cells_states;
    StateCell **_last_cells_states;
    std::vector<sf::RectangleShape> _cells;
    sf::Vector2u _screenSize;
    sf::Vector2u _size;
    sf::Vector2f _sizeCell;
    AutomataState _state{AutomataState::Editing};
};

#endif //GAMEOFLIFE_CELLULARAUTOMATA_HPP
