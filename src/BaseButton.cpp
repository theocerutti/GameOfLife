/*
** EPITECH PROJECT, 2020
** Button.hpp
** File description:
**
*/

#include "BaseButton.hpp"

BaseButton::BaseButton(const sf::Vector2f &pos, sf::Texture *texture) : _texture(texture)
{
    setPosition(pos);
    _shape.setTexture(_texture);
    _shape.setSize(sf::Vector2f(_texture->getSize().x, _texture->getSize().y));
}

void BaseButton::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    target.draw(_shape, states);
}

void BaseButton::handleEvent(const sf::Event &event)
{
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        _state = State::Holding;
    } else if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
        _state = State::Clicked;
        onClick();
    } else if (event.type == sf::Event::MouseMoved && getGlobalBounds().contains(event.mouseMove.x, event.mouseMove.y)) {
        _state = State::Hovered;
    } else {
        _state = State::Idle;
    }
}

void BaseButton::update(double dt)
{
    if (_state == State::Hovered) {
        _fadeValue += (_fadeValue >= 1 ? 0 : _fadeSpeed * dt);
        _shape.setFillColor(Math::lerpColor(sf::Color::Black, sf::Color::Red, _fadeValue));
    } else if (_state == State::Idle || _state == State::Holding) {
        _fadeValue -= (_fadeValue <= 0 ? 0 : _fadeSpeed * dt);
        _shape.setFillColor(Math::lerpColor(sf::Color::Black, sf::Color::Red, _fadeValue));
    }
}

sf::Rect<float> BaseButton::getLocalBounds() const
{
    float width = static_cast<float>(std::abs(_shape.getSize().x));
    float height = static_cast<float>(std::abs(_shape.getSize().y));

    return {0.f, 0.f, width, height};
}

sf::Rect<float> BaseButton::getGlobalBounds() const
{
    return (getTransform().transformRect(getLocalBounds()));
}

void BaseButton::setTexture(sf::Texture *texture)
{
    _texture = texture;
    _shape.setTexture(_texture);
    _shape.setSize(sf::Vector2f(_texture->getSize().x, _texture->getSize().y));
}

const sf::Texture *BaseButton::getTexture() const
{
    return (_texture);
}
