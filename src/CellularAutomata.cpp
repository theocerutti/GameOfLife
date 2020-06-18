/*
** EPITECH PROJECT, 2020
** CellularAutomata.hpp
** File description:
**
*/

#include "CellularAutomata.hpp"

CellularAutomata::CellularAutomata(const sf::Vector2u &screenSize, const sf::Vector2u &size)
    : _cellular(screenSize, size),
      _buttonMode(*this, sf::Vector2f(0, 0))
{
    std::shared_ptr<sf::Font> font = AssetManager::get().loadFont("media/fonts/monofonto.ttf");

    _infoNbLiving = sf::Text("Living Cells: " + std::to_string(_cellular.getNbLivingCells()), *font);
    _infoSizeMap = sf::Text("SizeMap: " + std::to_string(_cellular.getSize().x) + "x" + std::to_string(_cellular.getSize().y), *font);
    _infoSizeMap.setPosition(0, 50);

    _buttonMode.setScale(0.2f, 0.2f);
    _buttonMode.setPosition(screenSize.x - _buttonMode.getGlobalBounds().width - 20, screenSize.y - _buttonMode.getGlobalBounds().height - 20);

    _clockUpdate.restart();
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
    target.draw(_sliderSpeed);
}

void CellularAutomata::handleEvent(const sf::Event &event)
{
    static sf::Vector2i posMouse;
    static bool hold = false;
    static sf::Vector2i latestRelativPos;

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

    sf::Vector2i actualRelativPos(std::floor(posMouse.x / _cellular.getSizeCell().x), std::floor(posMouse.y / _cellular.getSizeCell().y));
    if (hold && _state == AutomataState::Editing && latestRelativPos != actualRelativPos) {
        latestRelativPos = actualRelativPos;
        _cellular.invertCellState(latestRelativPos.x, latestRelativPos.y);
    } else if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::P) {
        setState(AutomataState::Processing);
    } else if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::E) {
        setState(AutomataState::Editing);
    } else if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::C) {
        setState(AutomataState::Editing);
        _cellular.clear();
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) {
        setMsUpdate(getMsUpdate() - 1);
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        setMsUpdate(getMsUpdate() + 1);
    }
    _buttonMode.handleEvent(event);
}

void CellularAutomata::update(double dt)
{
    if (_state == AutomataState::Processing && _clockUpdate.getElapsedTime().asMilliseconds() >= getMsUpdate()) {
        _cellular.update(dt);
        _clockUpdate.restart();
    }
    _buttonMode.update(dt);
    _infoNbLiving.setString("Living Cells: " + std::to_string(_cellular.getNbLivingCells()));
    _infoSizeMap.setString("SizeMap: " + std::to_string(_cellular.getSize().x) + "x" + std::to_string(_cellular.getSize().y));
}

AutomataState CellularAutomata::getState() const
{
    return (_state);
}

void CellularAutomata::setState(const AutomataState &state)
{
    if (_state != state) {
        _state = state;
        _buttonMode.setTextureFromState(_state);
    }
}

void CellularAutomata::setMsUpdate(double ms)
{
    _msUpdate = ms;
    if (_msUpdate < 0)
        _msUpdate = 0;
}

double CellularAutomata::getMsUpdate() const
{
    return (_msUpdate);
}