/*
** EPITECH PROJECT, 2020
** CellularAutomata.hpp
** File description:
**
*/

#include <iostream>
#include <cmath>
#include "../include/CellularAutomata.hpp"

CellularAutomata::CellularAutomata(const sf::Vector2u &screenSize, const sf::Vector2u &size) : _screenSize(screenSize), _size(size)
{
    _sizeCell = {(float)_screenSize.x / _size.x, (float)_screenSize.y / _size.y};
    _actual_cells_states.resize(_size.x * _size.y);

    std::fill(_actual_cells_states.begin(), _actual_cells_states.end(), StateCell::Dead);
    _clockUpdate.restart();
}

void CellularAutomata::handleEvent(const sf::Event &event)
{
    if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left && _state == AutomataState::Editing) {
        invertCellState(std::floor(event.mouseButton.x / _sizeCell.x), std::floor(event.mouseButton.y / _sizeCell.y));
    } else if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::P) {
        _state = AutomataState::Processing;
    } else if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::E) {
        _state = AutomataState::Editing;
    }
}

void CellularAutomata::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    for (int y = 0; y < _size.y; y++) {
        for (int x = 0; x < _size.x; x++) {
            sf::RectangleShape shape(_sizeCell);
            shape.setPosition(sf::Vector2f(x * _sizeCell.x, y * _sizeCell.y));
            shape.setFillColor(_actual_cells_states.at(x + (y * _size.y)) == StateCell::Live ? CLIVE_CELL : CDEAD_CELL);
            target.draw(shape);
        }
    }
}

void CellularAutomata::update()
{
    if (_state == AutomataState::Processing && _clockUpdate.getElapsedTime().asMilliseconds() > _msUpdate) {
        std::vector<std::tuple<int, int, StateCell>> states;
        for (int y = 0; y < _size.y; y++) {
            for (int x = 0; x < _size.x; x++) {
                int nbLivingNeightbors = getNbNeighborsLiving(x, y);
                const StateCell &state = getStateCell(x, y);
                if (state == StateCell::Dead && nbLivingNeightbors == 3) {
                    states.emplace_back(x, y, StateCell::Live);
                } else if (state == StateCell::Live && nbLivingNeightbors > 3) {
                    states.emplace_back(x, y, StateCell::Dead);
                } else if (state == StateCell::Live && nbLivingNeightbors < 2) {
                    states.emplace_back(x, y, StateCell::Dead);
                }
            }
        }
        for (auto &state : states)
            setStateCell(std::get<0>(state), std::get<1>(state), std::get<2>(state));
        _clockUpdate.restart();
    }
}

int CellularAutomata::getNbNeighborsLiving(int x, int y)
{
    int nbLiving = 0;

    nbLiving += getNeighbor(x, y, 1, 0) == StateCell::Live;
    nbLiving += getNeighbor(x, y, 1, 1) == StateCell::Live;
    nbLiving += getNeighbor(x, y, 0, 1) == StateCell::Live;
    nbLiving += getNeighbor(x, y, -1, 0) == StateCell::Live;
    nbLiving += getNeighbor(x, y, -1, -1) == StateCell::Live;
    nbLiving += getNeighbor(x, y, 0, -1) == StateCell::Live;
    nbLiving += getNeighbor(x, y, 1, -1) == StateCell::Live;
    nbLiving += getNeighbor(x, y, -1, 1) == StateCell::Live;
    return (nbLiving);
}

void CellularAutomata::setStateCell(int x, int y, const CellularAutomata::StateCell &state)
{
    _actual_cells_states.at(x + (y * _size.y)) = state;
}

const CellularAutomata::StateCell &CellularAutomata::getStateCell(int x, int y) const
{
    return (_actual_cells_states.at(x + (y * _size.y)));
}

CellularAutomata::StateCell CellularAutomata::getNeighbor(int xCell, int yCell, int xAdd, int yAdd) const
{
    if (xCell + xAdd < 0 || yCell + yAdd < 0 || (xCell + xAdd) + ((yCell + yAdd) * _size.y) >= _size.x * _size.y)
        return (StateCell::Dead);
    return (getStateCell(xCell + xAdd, yCell + yAdd));
}

void CellularAutomata::invertCellState(int xRelative, int yRelativ)
{
    if (xRelative >= 0 && yRelativ >= 0 && xRelative + (yRelativ * _size.y) < _size.x * _size.y) {
        StateCell cellState = _actual_cells_states.at(xRelative + (yRelativ * _size.y));

        _actual_cells_states.at(xRelative + (yRelativ * _size.y)) = cellState == StateCell::Live ? StateCell::Dead : StateCell::Live;
    }
}