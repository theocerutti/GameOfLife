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
    _sizeCell = {(float)screenSize.x / _size.x, (float)screenSize.y / _size.y};
    _actual_cells_states.resize(_size.x * _size.y);

    std::fill(_actual_cells_states.begin(), _actual_cells_states.end(), StateCell::Dead);
    _clockUpdate.restart();
}

void CellularArray::handleEvent(const sf::Event &event)
{
    static sf::Vector2i posMouse;
    static bool hold = false;

    if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
        hold = false;
    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
        posMouse.x = event.mouseButton.x;
        posMouse.y = event.mouseButton.y;
        hold = true;
    }
    if (event.type == sf::Event::MouseMoved && hold) {
        posMouse.x = event.mouseMove.x;
        posMouse.y = event.mouseMove.y;
    }

    if (hold && _state == AutomataState::Editing) {
        invertCellState(std::floor(posMouse.x / _sizeCell.x), std::floor(posMouse.y / _sizeCell.y));
    } else if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::P) {
        _state = AutomataState::Processing;
    } else if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::E) {
        _state = AutomataState::Editing;
    } else if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::C) {
        _state = AutomataState::Editing;
        std::fill(_actual_cells_states.begin(), _actual_cells_states.end(), StateCell::Dead);
        _nbLivingCells = 0;
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) {
        setMsUpdate(_msUpdate - 1);
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        setMsUpdate(_msUpdate + 1);
    }
}

void CellularArray::update()
{
    if (_state == AutomataState::Processing && _clockUpdate.getElapsedTime().asMilliseconds() > _msUpdate) {
        std::vector<std::tuple<int, int, StateCell>> states;
        for (int y = 0; y < _size.y; y++) {
            for (int x = 0; x < _size.x; x++) {
                int nbLivingNeightbors = getNbNeighborsLiving(x, y);
                const StateCell &state = getStateCell(x, y);
                if (state == StateCell::Dead && nbLivingNeightbors == 3) {
                    states.emplace_back(x, y, StateCell::Live);
                    _nbLivingCells += 1;
                } else if (state == StateCell::Live && nbLivingNeightbors > 3) {
                    states.emplace_back(x, y, StateCell::Dead);
                    _nbLivingCells -= 1;
                } else if (state == StateCell::Live && nbLivingNeightbors < 2) {
                    states.emplace_back(x, y, StateCell::Dead);
                    _nbLivingCells -= 1;
                }
            }
        }
        for (auto &state : states)
            setStateCell(std::get<0>(state), std::get<1>(state), std::get<2>(state));
        _clockUpdate.restart();
    }
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

void CellularArray::setMsUpdate(double ms)
{
    _msUpdate = ms;
    if (_msUpdate < 0)
        _msUpdate = 0;
}

double CellularArray::getMsUpdate() const
{
    return (_msUpdate);
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
