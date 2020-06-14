/*
** EPITECH PROJECT, 2020
** CellularArray.hpp
** File description:
**
*/

#ifndef GAMEOFLIFE_CELLULARARRAY_HPP
#define GAMEOFLIFE_CELLULARARRAY_HPP

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <cstring>
#include <thread>
#include <chrono>
#include <algorithm>

#define CDEAD_CELL sf::Color(100, 100, 100)
#define CLIVE_CELL sf::Color(225, 225, 225)

class CellularArray {
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
    CellularArray(const sf::Vector2u &screenSize, const sf::Vector2u &size);
    void invertCellState(int xRelative, int yRelativ);
    void update();
    void handleEvent(const sf::Event &event);
    void setMsUpdate(double ms);
    double getMsUpdate() const;
    const std::vector<StateCell> &getActualCellsStates() const;
    void setActualCellsStates(const std::vector<StateCell> &actualCellsStates);
    const sf::Vector2u &getSize() const;
    void setSize(const sf::Vector2u &size);
    const sf::Vector2f &getSizeCell() const;
    void setSizeCell(const sf::Vector2f &sizeCell);
    std::size_t getNbLivingCells() const;
private:
    const StateCell &getStateCell(int x, int y) const;
    void setStateCell(int x, int y, const StateCell &state);
    int getNbNeighborsLiving(int x, int y);
    StateCell getNeighbor(int x, int y, int xAdd, int yAdd) const;
private:
    sf::Clock _clockUpdate;
    double _msUpdate{500};
    std::vector<StateCell> _actual_cells_states;
    sf::Vector2u _size;
    sf::Vector2f _sizeCell;
    std::size_t _nbLivingCells{0};
    AutomataState _state{AutomataState::Editing};
};

#endif //GAMEOFLIFE_CELLULARARRAY_HPP
