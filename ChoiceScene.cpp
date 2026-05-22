#include "ChoiceScene.h"

ChoiceScene::ChoiceScene(const string& bgPath, const string& charPath, vector<Choice> choices,
                CacheManager<string, sf::Texture>& tm, CacheManager<string, sf::Font>& fm)
        : options(choices), charTexturePath(charPath), texMgr(tm), fontMgr(fm) {

    bgSprite.setTexture(texMgr.get(bgPath));

    charSprite.setPosition(400, 100);
    if (!charTexturePath.empty() && charTexturePath != "none") {
        charSprite.setTexture(texMgr.get(charTexturePath));
        charSprite.setColor(sf::Color(255, 255, 255, 255));
    } else {
        charSprite.setColor(sf::Color(255, 255, 255, 0));
    }

    for (size_t i = 0; i < options.size(); i++) {
        sf::RectangleShape rect(sf::Vector2f(440, 60));
        rect.setFillColor(sf::Color(20, 20, 20, 230));
        rect.setOutlineColor(sf::Color::White);
        rect.setOutlineThickness(2);
        rect.setPosition(420, 250 + (static_cast<float>(i) * 100));
        buttons.push_back(rect);

        sf::Text t(options[i].text, fontMgr.get("arial.ttf"), 22);
        t.setPosition(440, 265 + (static_cast<float>(i) * 100));
        labels.push_back(t);
    }
}

void ChoiceScene::handleInput(sf::Vector2f mousePos, bool clicked) {
    if (!clicked)
        return;
    for (size_t i = 0; i < buttons.size(); i++) {
        if (buttons[i].getGlobalBounds().contains(mousePos)) {
            setNextSceneID(options[i].targetID);
            setFinished(true);
        }
    }
}

void ChoiceScene::render(sf::RenderWindow& window) {
    window.draw(bgSprite);
    window.draw(charSprite);
    for (auto& b : buttons)
        window.draw(b);
    for (auto& l : labels)
        window.draw(l);
}
