/*
** EPITECH PROJECT, 2020
** Button.hpp
** File description:
**
*/

#ifndef GAMEOFLIFE_BASEBUTTON_HPP
#define GAMEOFLIFE_BASEBUTTON_HPP

#include <SFML/Graphics.hpp>
#include <functional>
#include <memory>
#include "AssetManager.hpp"
#include "Math.hpp"

class BaseButton : public sf::Drawable, public sf::Transformable {
public:
    enum class State {
        Idle,
        Clicked,
        Holding,
        Hovered
    };
public:
    BaseButton() = default;
    BaseButton(const sf::Vector2f &pos, sf::Texture *texture);
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
    void update(double dt);
    void handleEvent(const sf::Event &event);
    virtual void onClick() = 0;
    void setTexture(sf::Texture *texture);
    const sf::Texture *getTexture() const;
    sf::Rect<float> getLocalBounds() const;
    sf::Rect<float> getGlobalBounds() const;
    const sf::Color &getFromColorFade() const;
    void setFromColorFade(const sf::Color &fromColorFade);
    const sf::Color &getToColorFade() const;
    void setToColorFade(const sf::Color &toColorFade);
    double getFadeSpeed() const;
    void setFadeSpeed(double fadeSpeed);
private:
    sf::Texture *_texture{nullptr};
    sf::RectangleShape _shape;
    State _state{State::Idle};
    sf::Color _fromColorFade{sf::Color::Black};
    sf::Color _toColorFade{sf::Color::White};
    double _fadeValue{0};
    double _fadeSpeed{0.003};
};

#endif //GAMEOFLIFE_BASEBUTTON_HPP
