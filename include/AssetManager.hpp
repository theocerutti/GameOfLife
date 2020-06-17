/*
** EPITECH PROJECT, 2020
** AssetManager.hpp
** File description:
**
*/

#ifndef GAMEOFLIFE_ASSETMANAGER_HPP
#define GAMEOFLIFE_ASSETMANAGER_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <memory>
#include <unordered_map>

class AssetManager {
public:
    using AssetHash = std::size_t;
public:
    static AssetManager &get();

    /*
     *  @brief  Get asset and load it not in cache
     *
     *  /!\ Please assign the return value into a shared_ptr<T> or the cleanCache wont work properly
     */
    std::shared_ptr<sf::Font> loadFont(const std::string &path)
    {
        AssetHash hash = getHashFromPath(path);

        if (_fontsCache.find(hash) == _fontsCache.end()) {
            std::shared_ptr<sf::Font> newFont = std::make_shared<sf::Font>();
            newFont->loadFromFile(path);
            _fontsCache.insert({hash, newFont});
            return (newFont);
        } else {
            return (_fontsCache.at(hash));
        }
    }

    std::shared_ptr<sf::Texture> loadTexture(const std::string &path)
    {
        AssetHash hash = getHashFromPath(path);

        if (_fontsCache.find(hash) == _fontsCache.end()) {
            std::shared_ptr<sf::Texture> newTexture = std::make_shared<sf::Texture>();
            newTexture->loadFromFile(path);
            _texturesCache.insert({hash, newTexture});
            return (newTexture);
        } else {
            return (_texturesCache.at(hash));
        }
    }

    /*
     * Remove all pointers if there are not linked to any resource
     */
    void cleanCache();

private:
    template<typename T>
    void clean(std::unordered_map<AssetHash, std::shared_ptr<T>> &cache)
    {
        auto it = cache.begin();

        while (it != cache.end()) {
            if (it->second.unique()) {
                it = cache.erase(it);
            } else {
                ++it;
            }
        }
    }

    AssetHash getHashFromPath(const std::string &path);
private:
    std::unordered_map<AssetHash, std::shared_ptr<sf::Font>> _fontsCache;
    std::unordered_map<AssetHash, std::shared_ptr<sf::Texture>> _texturesCache;
};

#endif //GAMEOFLIFE_ASSETMANAGER_HPP
