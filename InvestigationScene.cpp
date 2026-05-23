#include "InvestigationScene.h"

InvestigationScene::InvestigationScene(const shared_ptr<GameEngine>& engine, vector<View> vData, const string& next,
                       CacheManager<string, sf::Texture>& tm, CacheManager<string, sf::Font>& fm)
        : views(vData), engineRef(engine), texMgr(tm), fontMgr(fm) {
    setNextSceneID(next);

    uiBackground.setSize(sf::Vector2f(1080.0f, 100.0f));
    uiBackground.setPosition(100.0f, 590.0f);
    uiBackground.setFillColor(sf::Color(15, 15, 15, 220));
    uiBackground.setOutlineColor(sf::Color(255, 255, 255, 140));
    uiBackground.setOutlineThickness(2.0f);

    uiMsg.setFont(fontMgr.get("arial.ttf"));
    uiMsg.setPosition(130, 620);
    uiMsg.setCharacterSize(22);
    uiMsg.setFillColor(sf::Color::White);

    promptOverlay.setSize(sf::Vector2f(1280, 720));
    promptOverlay.setFillColor(sf::Color(0, 0, 0, 180));
    promptText.setFont(fontMgr.get("arial.ttf"));
    promptText.setString("Do you wish to get the medication?");
    promptText.setPosition(430, 250);

    yesBtn.setSize(sf::Vector2f(150, 60)); yesBtn.setFillColor(sf::Color(40, 140, 40));
    yesBtn.setPosition(450, 350);
    yesText.setFont(fontMgr.get("arial.ttf")); yesText.setString("Yes");
    yesText.setPosition(505, 362);

    noBtn.setSize(sf::Vector2f(150, 60)); noBtn.setFillColor(sf::Color(140, 40, 40));
    noBtn.setPosition(720, 350);
    noText.setFont(fontMgr.get("arial.ttf")); noText.setString("Not now");
    noText.setPosition(740, 362);
}

void InvestigationScene::handleInput(sf::Vector2f mousePos, bool clicked) {
    if (!clicked)
        return;
    if (isPrompting) {
        if (yesBtn.getGlobalBounds().contains(mousePos))
            setFinished(true);
        if (noBtn.getGlobalBounds().contains(mousePos))
            isPrompting = false;
        return;
    }
    auto& v = views[currentView];
        for (int i = 0; i < static_cast<int>(v.hotspots.size()); i++) {
            if (v.hotspots[i].contains(mousePos)) {
                if (i == v.exitIndex)
                    isPrompting = true;
                else
                    uiMsg.setString(v.messages[i]);
                return;
            }
        }

    if (mousePos.x < 150 && currentView > 0) {
        currentView--;
        uiMsg.setString("");
        return;
    }

    if (mousePos.x > 1130 && currentView < 2) {
        currentView++;
        uiMsg.setString("");
        return;
    }
}

void InvestigationScene::update() {
    bgSprite.setTexture(texMgr.get(views[currentView].bg));
}

void InvestigationScene::render(sf::RenderWindow& window) {
    window.draw(bgSprite);

    if (!uiMsg.getString().isEmpty()) {
        window.draw(uiBackground);
        window.draw(uiMsg);
    }

    if (debugMode) {
        for (const auto& rect : views[currentView].hotspots) {
            sf::RectangleShape debugRect;
            debugRect.setPosition(rect.left, rect.top);
            debugRect.setSize(sf::Vector2f(rect.width, rect.height));
            debugRect.setFillColor(sf::Color(255, 0, 0, 80));
            debugRect.setOutlineColor(sf::Color::Red);
            debugRect.setOutlineThickness(1.5f);
            window.draw(debugRect);
        }
    }

    if (isPrompting) {
        window.draw(promptOverlay); window.draw(promptText);
        window.draw(yesBtn); window.draw(noBtn);
        window.draw(yesText); window.draw(noText);
    }
}