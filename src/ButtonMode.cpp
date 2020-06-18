/*
** EPITECH PROJECT, 2020
** ButtonMode.hpp
** File description:
**
*/

#include "ButtonMode.hpp"

ButtonMode::ButtonMode(const sf::Vector2f &pos)
    : BaseButton(),
      _startTexture(AssetManager::get().loadTexture("media/images/start.png")),
      _editTexture(AssetManager::get().loadTexture("media/images/pause.png"))
{
    setPosition(pos);
    setTexture(_startTexture.get());
}

void ButtonMode::onClick()
{
    setTexture((getTexture() == _startTexture.get() ? _editTexture.get() : _startTexture.get()));
}