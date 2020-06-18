/*
** EPITECH PROJECT, 2020
** SpeedSlider.hpp
** File description:
**
*/

#include "SpeedSlider.hpp"


SpeedSlider::SpeedSlider(const sf::Vector2f &pos)
    : BaseSlider(),
      _textureProgress(AssetManager::get().loadTexture("media/images/slider_progress.png")),
      _textureBar(AssetManager::get().loadTexture("media/images/slider_bar.png")),
      _font(AssetManager::get().loadFont("media/fonts/monofonto.ttf"))
{
    setPosition(pos);
    setTextureBar(_textureBar.get());
    setTextureProgress(_textureProgress.get());
    setFont(_font.get());
}

void SpeedSlider::onSlide()
{
}