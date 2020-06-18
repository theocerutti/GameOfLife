/*
** EPITECH PROJECT, 2020
** SpeedSlider.hpp
** File description:
**
*/

#ifndef GAMEOFLIFE_SPEEDSLIDER_HPP
#define GAMEOFLIFE_SPEEDSLIDER_HPP

#include "BaseSlider.hpp"

class SpeedSlider : public BaseSlider {
public:
    explicit SpeedSlider(const sf::Vector2f &pos);
    void onSlide() override;
private:
    std::shared_ptr<sf::Texture> _textureProgress;
    std::shared_ptr<sf::Texture> _textureBar;
    std::shared_ptr<sf::Font> _font;
};

#endif //GAMEOFLIFE_SPEEDSLIDER_HPP
