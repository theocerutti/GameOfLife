/*
** EPITECH PROJECT, 2020
** Button.hpp
** File description:
**
*/

#include <Button.hpp>

Button::Button(const sf::Vector2f &pos, const std::string &texturePath, const std::function<void()> &callback)
    : _shape(),
      _callback(callback),
      _texture(AssetManager::get().loadTexture(texturePath))
{
    setPosition(pos);
    setScale(0.5, 0.5);
    _shape.setTexture(_texture.get());
    _shape.setSize(sf::Vector2f(_texture->getSize().x, _texture->getSize().y));
}

void Button::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    target.draw(_shape, states);
}

void Button::handleEvent(const sf::Event &event)
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

void Button::update(double dt)
{
    if (_state == State::Hovered) {
        _fadeValue += (_fadeValue >= 1 ? 0 : _fadeSpeed * dt);
        _shape.setFillColor(Math::lerpColor(sf::Color::Black, sf::Color::Red, _fadeValue));
    } else if (_state == State::Idle) {
        _fadeValue -= (_fadeValue <= 0 ? 0 : _fadeSpeed * dt);
        _shape.setFillColor(Math::lerpColor(sf::Color::Black, sf::Color::Red, _fadeValue));
    }
}

void Button::onClick()
{
    if (_callback)
        _callback();
}

sf::Rect<float> Button::getLocalBounds() const
{
    float width = static_cast<float>(std::abs(_shape.getSize().x));
    float height = static_cast<float>(std::abs(_shape.getSize().y));

    return sf::Rect<float>(0.f, 0.f, width, height);
}

sf::Rect<float> Button::getGlobalBounds() const
{
    return (getTransform().transformRect(getLocalBounds()));
}