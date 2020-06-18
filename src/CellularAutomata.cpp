/*
** EPITECH PROJECT, 2020
** CellularAutomata.hpp
** File description:
**
*/

#include "CellularAutomata.hpp"

CellularAutomata::CellularAutomata(const sf::Vector2u &screenSize, const sf::Vector2u &size)
    : _cellular(screenSize, size),
      _buttonMode(sf::Vector2f(0, 0))
{
    std::shared_ptr<sf::Font> font = AssetManager::get().loadFont("media/fonts/monofonto.ttf");

    _infoNbLiving = sf::Text("Living Cells: " + std::to_string(_cellular.getNbLivingCells()), *font);
    _infoSizeMap = sf::Text("SizeMap: " + std::to_string(_cellular.getSize().x) + "x" + std::to_string(_cellular.getSize().y), *font);
    _infoSizeMap.setPosition(0, 50);

    _buttonMode.setScale(0.25, 0.25);
    _buttonMode.setPosition(screenSize.x - _buttonMode.getGlobalBounds().width - 20, screenSize.y - _buttonMode.getGlobalBounds().height - 20);
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
            shape.setOutlineColor(sf::Color::Black);
            shape.setOutlineThickness(-0.5);
            target.draw(shape);
        }
    }
    target.draw(_infoNbLiving);
    target.draw(_infoSizeMap);
    target.draw(_buttonMode);
}

void CellularAutomata::handleEvent(const sf::Event &event)
{
    _cellular.handleEvent(event);
    _buttonMode.handleEvent(event);
}

void CellularAutomata::update(double dt)
{
    _cellular.update(dt);
    _buttonMode.update(dt);
    _infoNbLiving.setString("Living Cells: " + std::to_string(_cellular.getNbLivingCells()));
    _infoSizeMap.setString("SizeMap: " + std::to_string(_cellular.getSize().x) + "x" + std::to_string(_cellular.getSize().y));
}
