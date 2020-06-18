/*
** EPITECH PROJECT, 2020
** BaseSlider.hpp
** File description:
**
*/

#include "BaseSlider.hpp"

BaseSlider::BaseSlider(const sf::Vector2i &pos, sf::Texture *textureBar, sf::Texture *textureProgress)
{
    _value = _percent = _minValue - _maxValue;
    _textureBar = textureBar;
    _textureProgress = textureProgress;
    _barShape.setSize(sf::Vector2f(_textureBar->getSize().x, _textureBar->getSize().y));
    _progressShape.setSize(sf::Vector2f(_textureProgress->getSize().x, _textureProgress->getSize().y));
    setFromPercent(_percent);
}

void BaseSlider::handleEvent(const sf::Event &event)
{
}

void BaseSlider::update(double dt)
{
    updateTexts();
}

void BaseSlider::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    target.draw(_barShape, states);
    target.draw(_progressShape, states);
    target.draw(_minText, states);
    target.draw(_maxText, states);
    target.draw(_valueText, states);
}

void BaseSlider::updateTexts()
{
    _minText.setString(std::to_string(_minValue));
    _maxText.setString(std::to_string(_maxValue));
    _valueText.setString(std::to_string(_value));
}

sf::Rect<float> BaseSlider::getLocalBounds() const
{
    float width = static_cast<float>(std::abs(_barShape.getSize().x));
    float height = static_cast<float>(std::abs(_barShape.getSize().y));

    return {0.f, 0.f, width, height};
}

sf::Rect<float> BaseSlider::getGlobalBounds() const
{
    return (getTransform().transformRect(getLocalBounds()));
}

void BaseSlider::setFromValue(float value)
{
    value = Math::clamp(value, _minValue, _maxValue);
}

void BaseSlider::setFromPercent(float percent)
{
    percent = Math::clamp(percent, 0, 100);
    sf::IntRect rect = _progressShape.getTextureRect();

    rect.width = rect.width * ((percent - _minValue) / (_maxValue - _minValue));
    _percent = percent;
    _progressShape.setTextureRect(rect);
}
