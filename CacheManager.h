#ifndef TEMA_3_POO_CACHEMANAGER_H
#define TEMA_3_POO_CACHEMANAGER_H

#include <map>
#include <string>
#include <SFML/Graphics.hpp>

using namespace std;

template <typename K, typename V>
class CacheManager {
private:
    map<K, V> cache;
public:
    CacheManager();
    V& get(const K& key);
    size_t size() const;
};

template <>
class CacheManager<string, sf::Font> {
private:
    std::map<string, sf::Font> cache;
public:
    CacheManager() = default;
    sf::Font& get(const string& key);
    size_t size() const;
};

//#include "CacheManager.hpp"

#endif //TEMA_3_POO_CACHEMANAGER_H