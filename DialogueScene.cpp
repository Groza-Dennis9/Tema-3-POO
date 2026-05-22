#include "DialogueScene.h"
#include "GameEngine.h"

DialogueScene::DialogueScene(const shared_ptr<GameEngine>& engine, vector<DialogueLine> data, const string& next,
                             CacheManager<string, sf::Texture>& tm, CacheManager<string, sf::Font>& fm, CacheManager<string, sf::SoundBuffer>& sm)
    : script(data), engineRef(engine), texMgr(tm), fontMgr(fm), soundMgr(sm) {
    setNextSceneID(next);

    nameText.setFont(fontMgr.get("arial.ttf"));
    nameText.setPosition(120, 485);
    nameText.setFillColor(sf::Color::Yellow);

    bodyText.setFont(fontMgr.get("arial.ttf"));
    bodyText.setPosition(120, 535);
    bodyText.setCharacterSize(24);

    charSprite.setPosition(400, 100);

    textBoxBackground.setSize(sf::Vector2f(1080.0f, 180.0f));
    textBoxBackground.setPosition(100.0f, 470.0f);
    textBoxBackground.setFillColor(sf::Color(20, 20, 20, 220));
    textBoxBackground.setOutlineColor(sf::Color(255, 255, 255, 180));
    textBoxBackground.setOutlineThickness(2.0f);

    if (!script.empty()) {
        if (auto enginePtr = engineRef.lock()) {
            enginePtr->updateBGM(script[0].bgMusic);
        }
        playSound(script[0].voiceClip);
    }
}

void DialogueScene::playSound(const string& path) {
    if (!path.empty() && path != "none") {
        try {
            soundPlayer.setBuffer(soundMgr.get(path));
            soundPlayer.play();
        } catch (...) {}
    }
}

void DialogueScene::handleInput(sf::Vector2f mousePos, bool clicked) {
    if (!clicked) {
        return;
    }

    if (step < script.size() - 1) {
        step++;
        if (auto enginePtr = engineRef.lock()) {
            enginePtr->updateBGM(script[step].bgMusic);
        }
        playSound(script[step].voiceClip);
    }
    else setFinished(true);
}

void DialogueScene::update() {
    if (script.empty()) return;

    if (!script[step].bg.empty() && script[step].bg != "none") {
        bgSprite.setTexture(texMgr.get(script[step].bg));
        bgSprite.setColor(sf::Color(255, 255, 255, 255));
    }
    else
        bgSprite.setColor(sf::Color::Black);

    if (!script[step].character.empty() && script[step].character != "none") {
        charSprite.setTexture(texMgr.get(script[step].character));
        charSprite.setColor(sf::Color(255, 255, 255, 255));
    }
    else
        charSprite.setColor(sf::Color(255, 255, 255, 0));

    nameText.setString(script[step].name);
    bodyText.setString(script[step].text);
}

void DialogueScene::render(sf::RenderWindow& window) {
    window.draw(bgSprite);
    window.draw(charSprite);
    window.draw(textBoxBackground);
    window.draw(nameText);
    window.draw(bodyText);
}