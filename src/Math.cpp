/*
** EPITECH PROJECT, 2020
** Math.hpp
** File description:
**
*/

#include "Math.hpp"

sf::Color Math::lerpColor(const sf::Color &from, const sf::Color &to, double f)
{
    f = Math::clamp(f, 0, 1);
    return (sf::Color(
            lerp(from.r, to.r, f),
            lerp(from.g, to.g, f),
            lerp(from.b, to.b, f)
    ));
}

void Math::fastLerpColor(sf::Color &result, const sf::Color &from, const sf::Color &to, double f)
{
    result.r = lerp(from.r, to.r, f);
    result.g = lerp(from.g, to.g, f);
    result.b = lerp(from.b, to.b, f);
}