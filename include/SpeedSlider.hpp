/*
** EPITECH PROJECT, 2020
** SpeedSlider.hpp
** File description:
**
*/

#ifndef GAMEOFLIFE_SPEEDSLIDER_HPP
#define GAMEOFLIFE_SPEEDSLIDER_HPP

#include "BaseSlider.hpp"

class SpeedSlider : public BaseSlider {
public:
    SpeedSlider() = default;
    void onSlide() override;
private:
};

#endif //GAMEOFLIFE_SPEEDSLIDER_HPP
