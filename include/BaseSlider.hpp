/*
** EPITECH PROJECT, 2020
** BaseSlider.hpp
** File description:
**
*/

#ifndef GAMEOFLIFE_BASESLIDER_HPP
#define GAMEOFLIFE_BASESLIDER_HPP

#include <SFML/Graphics.hpp>
#include <functional>
#include <memory>
#include "AssetManager.hpp"
#include "Math.hpp"

class BaseSlider : public sf::Drawable, public sf::Transformable {
public:
    BaseSlider() = default;
    BaseSlider(const sf::Vector2i &pos, sf::Texture *textureBar, sf::Texture *textureProgress);
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
    void update(double dt);
    void handleEvent(const sf::Event &event);
    void updateTexts();
    void setFromValue(float value);
    void setFromPercent(float percent);
    sf::Rect<float> getLocalBounds() const;
    sf::Rect<float> getGlobalBounds() const;
    virtual void onSlide() = 0;
private:
    float _value;
    float _percent;
    float _minValue{0};
    float _maxValue{100};
    sf::Text _minText;
    sf::Text _maxText;
    sf::Text _valueText;
    sf::RectangleShape _progressShape;
    sf::RectangleShape _barShape;
    sf::Texture *_textureProgress;
    sf::Texture *_textureBar;
};

#endif //GAMEOFLIFE_BASESLIDER_HPP
