#ifndef TEMA_3_POO_CHOICESCENE_H
#define TEMA_3_POO_CHOICESCENE_H

#include "CacheManager.h"
#include "BaseScene.h"
#include <SFML/Graphics.hpp>
#include <vector>

using namespace std;

struct Choice {
    string text;
    string targetID;
};

class ChoiceScene : public BaseScene {
private:
    vector<Choice> options;
    vector<sf::RectangleShape> buttons;
    vector<sf::Text> labels;
    sf::Sprite bgSprite, charSprite;

    string charTexturePath;
    CacheManager<string, sf::Texture>& texMgr;
    CacheManager<string, sf::Font>& fontMgr;

public:
    ChoiceScene(const string& bgPath, const string& charPath, vector<Choice> choices,
                CacheManager<string, sf::Texture>& tm, CacheManager<string, sf::Font>& fm);

    void handleInput(sf::Vector2f mousePos, bool clicked) override;
    void update() override {}

    void render(sf::RenderWindow& window) override;
};

#endif //TEMA_3_POO_CHOICESCENE_H