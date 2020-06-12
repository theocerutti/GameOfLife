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
    _actual_cells_states =  new StateCell *[_size.y];
    _last_cells_states =  new StateCell *[_size.y];

    for (int y = 0; y < _size.y; y++) {
        _actual_cells_states[y] = new StateCell[_size.x]{StateCell::Live};
        _last_cells_states[y] = new StateCell[_size.x]{StateCell::Live};
        for (int x = 0; x < _size.x; x++) {
            _cells.emplace_back(_sizeCell);
            _cells.back().setPosition(sf::Vector2f(x * _sizeCell.x, y * _sizeCell.y));
            _cells.back().setFillColor(sf::Color::White);
        }
    }
}

CellularAutomata::~CellularAutomata()
{
    for (int y = 0; y < _size.y; y++) {
        delete[] _actual_cells_states[y];
        delete[] _last_cells_states[y];
    }
    delete[] _actual_cells_states;
    delete[] _last_cells_states;
}

void CellularAutomata::handleEvent(const sf::Event &event, const sf::Vector2i &posMouse)
{
    if (event.type == sf::Event::MouseButtonReleased) {
        invertCellState(std::floor(posMouse.x / _sizeCell.x), std::floor(posMouse.y / _sizeCell.y));
    } else if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::P) {
        _state = AutomataState::Processing;
    } else if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::E) {
        _state = AutomataState::Editing;
    }
}

void CellularAutomata::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    /*for (auto &cell : _cells)
        target.draw(cell);*/
    for (int y = 0; y < _size.y; y++) {
        for (int x = 0; x < _size.x; x++) {
            sf::RectangleShape shape(_sizeCell);
            shape.setPosition(sf::Vector2f(x * _sizeCell.x, y * _sizeCell.y));
            shape.setFillColor(_actual_cells_states[y][x] == StateCell::Live ? sf::Color::White : sf::Color::Black);
            target.draw(shape);
        }
    }
}

void CellularAutomata::update()
{
    if (_state == AutomataState::Processing) {
        std::memcpy(_last_cells_states, _actual_cells_states,  sizeof(*_actual_cells_states) * _size.x * _size.y);
        for (int y = 0; y < _size.y; y++) {
            for (int x = 0; x < _size.x; x++) {
                int nbLivingNeightbors = getNbNeighborsLiving(x, y);
                if (getStateCell(x, y) == StateCell::Dead && nbLivingNeightbors == 3) {
                    setStateCell(x, y, StateCell::Live);
                } else if (getStateCell(x, y) == StateCell::Live && (nbLivingNeightbors != 2 && nbLivingNeightbors != 3)) {
                    setStateCell(x, y, StateCell::Dead);
                } else if (nbLivingNeightbors == 3) {
                    setStateCell(x, y, StateCell::Live);
                } else if (nbLivingNeightbors < 2 || nbLivingNeightbors > 3)
                    setStateCell(x, y, StateCell::Dead);
            }
        }
        std::memcpy(_actual_cells_states, _last_cells_states, sizeof(*_actual_cells_states) * _size.x * _size.y);
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
}

int CellularAutomata::getNbNeighborsLiving(int x, int y)
{
    int nbLiving = 0;

    nbLiving += getNeighbor(x, y, 1, 0) == StateCell::Dead;
    nbLiving += getNeighbor(x, y, 1, 1) == StateCell::Dead;
    nbLiving += getNeighbor(x, y, 0, 1) == StateCell::Dead;
    nbLiving += getNeighbor(x, y, -1, 0) == StateCell::Dead;
    nbLiving += getNeighbor(x, y, -1, -1) == StateCell::Dead;
    nbLiving += getNeighbor(x, y, 0, -1) == StateCell::Dead;
    nbLiving += getNeighbor(x, y, 1, -1) == StateCell::Dead;
    nbLiving += getNeighbor(x, y, -1, 1) == StateCell::Dead;
    return (nbLiving);
}

void CellularAutomata::setStateCell(int x, int y, const CellularAutomata::StateCell &state)
{
    _last_cells_states[y][x] = state;
}

CellularAutomata::StateCell CellularAutomata::getStateCell(int x, int y) const
{
    return (_last_cells_states[y][x]);
}

CellularAutomata::StateCell CellularAutomata::getNeighbor(int xCell, int yCell, int xAdd, int yAdd)
{
    //std::cout << "x: " << xCell + xAdd << " " << ", y:" << yCell + yAdd << std::endl;
    if (xCell + xAdd < 0 || yCell + yAdd < 0 || yCell + xAdd >= _size.x || yCell + yAdd >= _size.y)
        return (StateCell::Dead);
    return (getStateCell(xCell + xAdd, yCell + yAdd));
}

void CellularAutomata::invertCellState(int xRelative, int yRelativ)
{
    if (xRelative >= 0 && yRelativ >= 0 && xRelative + (yRelativ * _size.y) < _cells.size()) {
        const sf::Color &color = _cells.at(xRelative + (yRelativ * _size.y)).getFillColor();

        _actual_cells_states[yRelativ][xRelative] = (color == sf::Color::Black ? StateCell::Live : StateCell::Dead); // TODO: faire attention aux erreurs memoires à proteger!
        _last_cells_states[yRelativ][xRelative] = (color == sf::Color::Black ? StateCell::Live : StateCell::Dead);
        _cells.at(xRelative + (yRelativ * _size.y)).setFillColor(color == sf::Color::Black ? sf::Color::White : sf::Color::Black);
    }
}