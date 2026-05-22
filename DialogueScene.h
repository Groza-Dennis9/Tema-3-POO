#ifndef TEMA_3_POO_DIALOGUESCENE_H
#define TEMA_3_POO_DIALOGUESCENE_H

#include "CacheManager.h"
#include "BaseScene.h"
#include <SFML/Audio.hpp>
#include <memory>
#include <vector>

using namespace std;

class GameEngine;

struct DialogueLine {
    string name, text, bg, character, voiceClip, bgMusic;
};

class DialogueScene : public BaseScene {
private:
    vector<DialogueLine> script;
    size_t step = 0;
    sf::Text nameText, bodyText;
    sf::Sprite bgSprite, charSprite;
    sf::RectangleShape textBoxBackground;

    sf::Sound soundPlayer;

    weak_ptr<GameEngine> engineRef;

    CacheManager<string, sf::Texture>& texMgr;
    CacheManager<string, sf::Font>& fontMgr;
    CacheManager<string, sf::SoundBuffer>& soundMgr;

    void playSound(const string& path);

public:
    DialogueScene(const shared_ptr<GameEngine>& engine, vector<DialogueLine> data, const string& next,
        CacheManager<string, sf::Texture>& tm, CacheManager<string, sf::Font>& fm, CacheManager<string, sf::SoundBuffer>& sm);

    void handleInput(sf::Vector2f mousePos, bool clicked) override;
    void update() override;
    void render(sf::RenderWindow& window) override;
};


#endif //TEMA_3_POO_DIALOGUESCENE_H