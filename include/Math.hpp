/*
** EPITECH PROJECT, 2020
** Math.hpp
** File description:
**
*/

#ifndef GAMEOFLIFE_MATH_HPP
#define GAMEOFLIFE_MATH_HPP

#include <SFML/Graphics.hpp>
#include <cmath>

namespace Math {
    double constexpr lerp(double a, double b, double f)
    {
        return a + f * (b - a);
    }

    /*
     * Calculate the variation rate
     * Take a value between b1Min and b1Max (b1Min <= x b1Max)
     * and recalculate x between b2Min and b2Max
     */
    double constexpr clamp2bounds(double b1Min, double b1Max, double x, double b2Min, double b2Max)
    {
        return (b2Min + (x - b1Min) * ((b2Max - b2Max) / (b1Max - b1Min)));
    }

    sf::Color lerpColor(const sf::Color &from, const sf::Color &to, double f);

    void fastLerpColor(sf::Color &result, const sf::Color &from, const sf::Color &to, double f);

    double constexpr fade(double t)
    {
        return (t * t * t * (t * (t * 6 - 15) + 10));
    }

    double constexpr grad(int hash, double x, double y, double z)
    {
        const std::uint8_t h = hash & 15;
        const double u = h < 8 ? x : y;
        const double v = h < 4 ? y : h == 12 || h == 14 ? x : z;
        return ((h & 1) == 0 ? u : -u) + ((h & 2) == 0 ? v : -v);
    }

    double constexpr clamp(double n, double lower, double upper)
    {
        return (std::max(lower, std::min(n, upper)));
    }

    int constexpr fastfloor(double x)
    {
        return (x > 0 ? (int) x : (int) x - 1);
    }

    double constexpr dot(int const g[3], double x, double y)
    {
        return (g[0] * x + g[1] * y);
    }
}

#endif //GAMEOFLIFE_MATH_HPP
