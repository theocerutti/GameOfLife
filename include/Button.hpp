/*
** EPITECH PROJECT, 2020
** Button.hpp
** File description:
**
*/

#ifndef GAMEOFLIFE_BUTTON_HPP
#define GAMEOFLIFE_BUTTON_HPP

#include <SFML/Graphics.hpp>
#include <AssetManager.hpp>
#include <Math.hpp>
#include <functional>
#include <memory>

class Button : public sf::Drawable, public sf::Transformable {
public:
    enum class State {
        Idle,
        Clicked,
        Holding,
        Hovered
    };
public:
    Button(const sf::Vector2f &pos, const std::string &texturePath, const std::function<void()> &callback = nullptr);
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
    void update(double dt);
    void handleEvent(const sf::Event &event);
    void onClick();
    sf::Rect<float> getLocalBounds() const;
    sf::Rect<float> getGlobalBounds() const;
private:
    const std::shared_ptr<sf::Texture> _texture;
    sf::RectangleShape _shape;
    State _state;
    std::function<void()> _callback;
    double _fadeValue{0};
    double _fadeSpeed{0.003};
};

#endif //GAMEOFLIFE_BUTTON_HPP
