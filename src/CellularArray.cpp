/*
** EPITECH PROJECT, 2020
** CellularArray.hpp
** File description:
**
*/

#include <iostream>
#include <cmath>
#include "../include/CellularArray.hpp"

CellularArray::CellularArray(const sf::Vector2u &screenSize, const sf::Vector2u &size) : _size(size)
{
    _sizeCell = {(float) screenSize.x / _size.x, (float) screenSize.y / _size.y};
    _actual_cells_states.resize(_size.x * _size.y);

    std::fill(_actual_cells_states.begin(), _actual_cells_states.end(), StateCell::Dead);
}

void CellularArray::update(double dt)
{
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
}

int CellularArray::getNbNeighborsLiving(int x, int y)
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

void CellularArray::setStateCell(int x, int y, const CellularArray::StateCell &state)
{
    int pos = x + (y * _size.y);

    if (state != _actual_cells_states.at(pos))
        _nbLivingCells += state == StateCell::Live ? 1 : -1;
    _actual_cells_states.at(x + (y * _size.y)) = state;
}

const CellularArray::StateCell &CellularArray::getStateCell(int x, int y) const
{
    return (_actual_cells_states.at(x + (y * _size.y)));
}

CellularArray::StateCell CellularArray::getNeighbor(int xCell, int yCell, int xAdd, int yAdd) const
{
    if (xCell + xAdd < 0 || yCell + yAdd < 0 || (xCell + xAdd) + ((yCell + yAdd) * _size.y) >= _size.x * _size.y)
        return (StateCell::Dead);
    return (getStateCell(xCell + xAdd, yCell + yAdd));
}

void CellularArray::invertCellState(int xRelative, int yRelativ)
{
    if (xRelative >= 0 && yRelativ >= 0 && xRelative + (yRelativ * _size.y) < _size.x * _size.y) {
        int pos = xRelative + (yRelativ * _size.y);
        const StateCell &actualCellState = _actual_cells_states.at(pos);

        if (actualCellState == StateCell::Dead) {
            _actual_cells_states.at(pos) = StateCell::Live;
            _nbLivingCells += 1;
        } else {
            _actual_cells_states.at(pos) = StateCell::Dead;
            _nbLivingCells -= 1;
        }
    }
}

const std::vector<CellularArray::StateCell> &CellularArray::getActualCellsStates() const
{
    return (_actual_cells_states);
}

void CellularArray::setActualCellsStates(const std::vector<StateCell> &actualCellsStates)
{
    _actual_cells_states = actualCellsStates;
}

const sf::Vector2u &CellularArray::getSize() const
{
    return (_size);
}

void CellularArray::setSize(const sf::Vector2u &size)
{
    _size = size;
}

const sf::Vector2f &CellularArray::getSizeCell() const
{
    return (_sizeCell);
}

void CellularArray::setSizeCell(const sf::Vector2f &sizeCell)
{
    _sizeCell = sizeCell;
}

std::size_t CellularArray::getNbLivingCells() const
{
    return (_nbLivingCells);
}

void CellularArray::clear()
{
    std::fill(_actual_cells_states.begin(), _actual_cells_states.end(), StateCell::Dead);
    _nbLivingCells = 0;
}
