/*
** EPITECH PROJECT, 2020
** BaseSlider.hpp
** File description:
**
*/

#include "BaseSlider.hpp"

BaseSlider::BaseSlider() : BaseSlider(sf::Vector2i(0, 0), nullptr, nullptr, nullptr)
{
}

BaseSlider::BaseSlider(const sf::Vector2i &pos, sf::Texture *textureBar, sf::Texture *textureProgress, sf::Font *font)
    : _textureBar(textureBar), _textureProgress(textureProgress), _font(font)
{
    _value = _percent = _maxValue - _minValue;
    if (textureBar)
        _barShape.setSize(sf::Vector2f(_textureBar->getSize().x, _textureBar->getSize().y));
    if (textureProgress)
        _progressShape.setSize(sf::Vector2f(_textureProgress->getSize().x, _textureProgress->getSize().y));
    if (textureProgress && textureBar)
        setFromPercent(_percent);
    if (font) {
        _minText.setFont(*_font);
        _maxText.setFont(*_font);
        _valueText.setFont(*_font);
    }
}

void BaseSlider::handleEvent(const sf::Event &event)
{
    if (event.mouseButton.button == sf::Mouse::Left) {
        if (getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
            float value = (event.mouseButton.x - getGlobalBounds().left) / static_cast<float>((getGlobalBounds().width)) * (_maxValue - _minValue) + _minValue;
            setFromPercent(value); // TODO: setFromPercent or setFromValue ???
            onSlide();
        }
    }
}

void BaseSlider::update(double dt)
{
    updateTexts();
}

void BaseSlider::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    //target.draw(_barShape, states);
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
    setFromPercent(Math::clamp2bounds(_minValue, _maxValue, value, 0, 100));
}

void BaseSlider::setFromPercent(float percent)
{
    percent = Math::clamp(percent, 0, 100);
    sf::IntRect rect = _progressShape.getTextureRect();

    rect.left = rect.width - (rect.width * ((percent - _minValue) / (_maxValue - _minValue)));
    _percent = percent;
    _progressShape.setTextureRect(rect);
}

sf::Texture *BaseSlider::getTextureProgress() const
{
    return (_textureProgress);
}

void BaseSlider::setTextureProgress(sf::Texture *textureProgress)
{
    _textureProgress = textureProgress;
    _progressShape.setTexture(_textureProgress, true);
    _progressShape.setSize(sf::Vector2f(_textureProgress->getSize().x, _textureProgress->getSize().y));
}

sf::Texture *BaseSlider::getTextureBar() const
{
    return (_textureBar);
}

void BaseSlider::setTextureBar(sf::Texture *textureBar)
{
    _textureBar = textureBar;
    _barShape.setTexture(_textureBar, true);
    _barShape.setSize(sf::Vector2f(_textureBar->getSize().x, _textureBar->getSize().y));
}

sf::Font *BaseSlider::getFont() const
{
    return (_font);
}

void BaseSlider::setFont(sf::Font *font)
{
    _font = font;
    if (font) {
        _minText.setFont(*_font);
        _maxText.setFont(*_font);
        _valueText.setFont(*_font);
    }
}
