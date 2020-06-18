/*
** EPITECH PROJECT, 2020
** ButtonMode.hpp
** File description:
**
*/

#ifndef GAMEOFLIFE_BUTTONMODE_HPP
#define GAMEOFLIFE_BUTTONMODE_HPP

#include "BaseButton.hpp"

class ButtonMode : public BaseButton {
public:
    ButtonMode(const sf::Vector2f &pos);
    void onClick() override;
private:
    std::shared_ptr<sf::Texture> _startTexture;
    std::shared_ptr<sf::Texture> _editTexture;
};


#endif //GAMEOFLIFE_BUTTONMODE_HPP
