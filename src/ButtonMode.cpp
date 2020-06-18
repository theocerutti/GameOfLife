/*
** EPITECH PROJECT, 2020
** ButtonMode.hpp
** File description:
**
*/

#include "ButtonMode.hpp"
#include "CellularAutomata.hpp"

ButtonMode::ButtonMode(CellularAutomata &cellularAutomata, const sf::Vector2f &pos)
    : BaseButton(),
      _startTexture(AssetManager::get().loadTexture("media/images/start.png")),
      _editTexture(AssetManager::get().loadTexture("media/images/pause.png")),
      _cellularAutomata(cellularAutomata)
{
    setPosition(pos);
    setTextureFromState(AutomataState::Editing);
}

void ButtonMode::onClick()
{
    if (getTexture() == _startTexture.get()) {
        setEditingTexture();
        _cellularAutomata.setState(AutomataState::Processing);
    } else if (getTexture() == _editTexture.get()) {
        setStartTexture();
        _cellularAutomata.setState(AutomataState::Editing);
    }
}

void ButtonMode::setStartTexture()
{
    setTexture(_startTexture.get());
}

void ButtonMode::setEditingTexture()
{
    setTexture(_editTexture.get());
}

void ButtonMode::setTextureFromState(const AutomataState &state)
{
    if (state == AutomataState::Editing) {
        setStartTexture();
    } else if (state == AutomataState::Processing) {
        setEditingTexture();
    }
}