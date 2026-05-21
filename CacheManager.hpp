#ifndef CACHE_MANAGER_HPP
#define CACHE_MANAGER_HPP

#include "CacheManager.h"
#include <type_traits>
#include <iostream>

template <typename K, typename V>
CacheManager<K, V>::CacheManager() {
    static_assert(is_class_v<V>, "Parametrul V trebuie sa fie o clasa de tip resursa SFML.");
}

template <typename K, typename V>
V& CacheManager<K, V>::get(const K& key) {
    if (cache.find(key) == cache.end()) {
        if constexpr (is_same_v<V, sf::SoundBuffer>) {
            if (!cache[key].loadFromFile(key)) {
                throw ResourceLoadException(key + " (Tip: SoundBuffer)");
            }
        } else if constexpr (is_same_v<V, sf::Texture>) {
            if (!cache[key].loadFromFile(key)) {
                throw ResourceLoadException(key + " (Tip: Texture)");
            }
        } else {
            if (!cache[key].loadFromFile(key)) {
                throw ResourceLoadException(key);
            }
        }
    }
    return cache[key];
}

template <typename K, typename V>
size_t CacheManager<K, V>::size() const {
    return cache.size();
}


template <>
inline sf::Font& CacheManager<std::string, sf::Font>::get(const std::string& key) {
    if (cache.find(key) == cache.end()) {
        if (!cache[key].loadFromFile(key)) {
            std::cerr << "[Cache] Font defect, se incearca fallback arial.ttf...\n";
            if (!cache[key].loadFromFile("arial.ttf")) {
                throw ResourceLoadException("arial.ttf ca fallback");
            }
        }
    }
    return cache[key];
}

template <>
inline size_t CacheManager<std::string, sf::Font>::size() const {
    return cache.size();
}

#endif // CACHE_MANAGER_HPP