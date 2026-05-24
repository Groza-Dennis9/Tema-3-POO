#ifndef TEMA_3_POO_INVESTIGATIONSCENE_H
#define TEMA_3_POO_INVESTIGATIONSCENE_H

#include "BaseScene.h"
#include "CacheManager.h"
#include <string>
#include <vector>
#include <memory>

using namespace std;

class GameEngine;

struct View {
    string bg;
    vector<sf::FloatRect> hotspots;
    vector<string> messages;
    int exitIndex = -1;
};

class InvestigationScene : public BaseScene {
private:
    vector<View> views;
    int currentView = 1;
    sf::Sprite bgSprite;
    sf::Text uiMsg;
    sf::RectangleShape uiBackground;

    weak_ptr<GameEngine> engineRef;

    CacheManager<string, sf::Texture>& texMgr;
    CacheManager<string, sf::Font>& fontMgr;

    bool isPrompting = false;
    sf::RectangleShape yesBtn, noBtn, promptOverlay;
    sf::Text yesText, noText, promptText;
    // bool debugMode = true;

public:
    InvestigationScene(const shared_ptr<GameEngine>& engine, vector<View> vData, const string& next,
                       CacheManager<string, sf::Texture>& tm, CacheManager<string, sf::Font>& fm);

    void handleInput(sf::Vector2f mousePos, bool clicked) override;

    void update() override;

    void render(sf::RenderWindow& window) override;
};


#endif //TEMA_3_POO_INVESTIGATIONSCENE_H