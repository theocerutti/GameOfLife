/*
** EPITECH PROJECT, 2020
** CellularAutomata.hpp
** File description:
**
*/

#ifndef GAMEOFLIFE_CELLULARAUTOMATA_HPP
#define GAMEOFLIFE_CELLULARAUTOMATA_HPP

#include "CellularArray.hpp"
#include "AssetManager.hpp"
#include "ButtonMode.hpp"
#include "SpeedSlider.hpp"

#define CDEAD_CELL sf::Color(100, 100, 100)
#define CLIVE_CELL sf::Color(225, 225, 225)

enum class AutomataState {
    Editing = 0,
    Processing = 1
};

class CellularAutomata : public sf::Drawable {
public:
    CellularAutomata(const sf::Vector2u &screenSize, const sf::Vector2u &size);
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
    void handleEvent(const sf::Event &event);
    void update(double dt);
    AutomataState getState() const;
    void setState(const AutomataState &state);
    void setMsUpdate(double ms);
    float getMsUpdate() const;
    float *getMsUpdatePtr();
private:
    CellularArray _cellular;
    sf::Text _infoNbLiving;
    sf::Text _infoSizeMap;
    ButtonMode _buttonMode;
    AutomataState _state{AutomataState::Editing};
    sf::Clock _clockUpdate;
    float _msUpdate{500};
};


#endif //GAMEOFLIFE_CELLULARAUTOMATA_HPP
