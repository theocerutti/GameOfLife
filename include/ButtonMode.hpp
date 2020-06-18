/*
** EPITECH PROJECT, 2020
** ButtonMode.hpp
** File description:
**
*/

#ifndef GAMEOFLIFE_BUTTONMODE_HPP
#define GAMEOFLIFE_BUTTONMODE_HPP

#include "BaseButton.hpp"

class CellularAutomata;
enum class AutomataState : char;

class ButtonMode : public BaseButton {
public:
    ButtonMode(CellularAutomata &cellularAutomata, const sf::Vector2f &pos);
    void onClick() override;
    void setStartTexture();
    void setEditingTexture();
    void setTextureFromState(const AutomataState &state);
private:
    std::shared_ptr<sf::Texture> _startTexture;
    std::shared_ptr<sf::Texture> _editTexture;
    CellularAutomata &_cellularAutomata;
};


#endif //GAMEOFLIFE_BUTTONMODE_HPP
