/*
** EPITECH PROJECT, 2020
** CellularAutomata.hpp
** File description:
**
*/

#include "CellularAutomata.hpp"

CellularAutomata::CellularAutomata(const sf::Vector2u &screenSize, const sf::Vector2u &size) : _cellular(screenSize, size)
{
    std::shared_ptr<sf::Font> font = AssetManager::get().load<sf::Font>("media/fonts/monofonto.ttf");

    _info = sf::Text("Living Cells: " + std::to_string(_cellular.getNbLivingCells()), *font);
}

void CellularAutomata::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    const sf::Vector2u &size = _cellular.getSize();
    const sf::Vector2f &sizeCell = _cellular.getSizeCell();
    const std::vector<CellularArray::StateCell> &cells = _cellular.getActualCellsStates();

    for (int y = 0; y < size.y; y++) {
        for (int x = 0; x < size.x; x++) {
            sf::RectangleShape shape(sizeCell);
            shape.setPosition(sf::Vector2f(x * sizeCell.x, y * sizeCell.y));
            shape.setFillColor(cells.at(x + (y * size.y)) == CellularArray::StateCell::Live ? CLIVE_CELL : CDEAD_CELL);
            target.draw(shape);
        }
    }
    target.draw(_info);
}

void CellularAutomata::handleEvent(const sf::Event &event)
{
    _cellular.handleEvent(event);
}

void CellularAutomata::update(double dt)
{
    _cellular.update();
    _info.setString("Living Cells: " + std::to_string(_cellular.getNbLivingCells()));
}
