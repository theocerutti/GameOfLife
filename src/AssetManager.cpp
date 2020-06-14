/*
** EPITECH PROJECT, 2020
** AssetManager.hpp
** File description:
**
*/

#include "AssetManager.hpp"

AssetManager &AssetManager::get()
{
    static AssetManager instance;

    return (instance);
}

void AssetManager::cleanCache()
{
    clean<sf::Font>(_fontsCache);
}

AssetManager::AssetHash AssetManager::getHashFromPath(const std::string &path)
{
    size_t index = path.find("media/");

    if (index == std::string::npos) {
        throw std::runtime_error("AssetManager: '" + path + "' needs to refer to a asset file in 'media/' folder");
    } else {
        std::string truncatedPath = path.substr(index);
        return (std::hash<std::string>{}(truncatedPath));
    }
}