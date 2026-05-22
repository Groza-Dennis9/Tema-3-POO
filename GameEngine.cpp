#include "GameEngine.h"

GameEngine::GameEngine() : window(sf::VideoMode(EngineConfig::getInstance().getWidth(), EngineConfig::getInstance().getHeight()),
        EngineConfig::getInstance().getTitle()) {
    window.setFramerateLimit(60);
}

void GameEngine::init() {
    goToScene("Start");
}

void GameEngine::updateBGM(const string& path) {
    if (path.empty() || path == "none") {
        globalBGM.stop();
        currentPlayingBGMPath = "";
        return;
    }
    if (path == currentPlayingBGMPath) return;

    globalBGM.stop();
    if (globalBGM.openFromFile(path)) {
        globalBGM.setLoop(true);
        globalBGM.setVolume(40.0f);
        globalBGM.play();
        currentPlayingBGMPath = path;
    }
}

void GameEngine::goToScene(const string& id) {
    auto self = shared_from_this();

    if (id == "Start") {
        currentScene = createScene<DialogueScene>(self, vector<DialogueLine>{
            {"Narrator", "Test for a dialogue scene.", "assets/images/4823ee026d76ff19217045121c984a27.jpg", "none", "none", "none"},
            {"Test", "Ready for a decision?", "assets/images/4823ee026d76ff19217045121c984a27.jpg", "assets/images/1_sprite.png", "assets/sounds/rainy-footsteps.ogg", "assets/sounds/take-a-load-off.ogg"}
        }, "Decision1", texManager, fontManager, soundManager);
    }
    else
        if (id == "Decision1") {
        currentScene = createScene<ChoiceScene>(
            "assets/images/4823ee026d76ff19217045121c984a27.jpg",
            "assets/images/3_sprite.png",
            vector<Choice>{{"Go to Invastigate.", "Investigate"}, {"Return to Start", "Start"}},
            texManager, fontManager);
    }
    else if (id == "Investigate") {
        View center;
        center.bg = "assets/images/c2a72d6249b578e890e9af3fb57389fe.jpg";
        center.hotspots.push_back(sf::FloatRect(500, 300, 200, 200));
        center.messages.push_back("New thing here!");
        center.hotspots.push_back(sf::FloatRect(100, 100, 100, 500));
        center.messages.push_back("");
        center.exitIndex = 1;

        View left;
        left.bg = "assets/images/4823ee026d76ff19217045121c984a27.jpg";
        left.hotspots.push_back(sf::FloatRect(100, 300, 50, 100));
        left.messages.push_back("Asset at left 1");
        left.hotspots.push_back(sf::FloatRect(500, 100, 100, 20));
        left.messages.push_back("Asset at left 2");

        View right;
        right.bg = "assets/images/ecc820dbdcc6966745e3e8c1a33bf853.jpg";
        right.hotspots.push_back(sf::FloatRect(100, 300, 50, 100));
        right.messages.push_back("Asset at right 1");
        right.hotspots.push_back(sf::FloatRect(500, 100, 100, 20));
        right.messages.push_back("Asset at right 2");

        currentScene = createScene<InvestigationScene>(
            self,
            vector<View>{left, center, right},
            "Start",
            texManager,
            fontManager
        );
    }
}

void GameEngine::run() {
    while (window.isOpen()) {
        sf::Event event;
        bool clicked = false;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) window.close();
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                clicked = true;
            }
        }

        sf::Vector2f mPos = static_cast<sf::Vector2f>(sf::Mouse::getPosition(window));
        if (currentScene) {
            currentScene->handleInput(mPos, clicked);
            currentScene->update();
            window.clear();
            currentScene->render(window);
            window.display();
            if (currentScene->isFinished()) goToScene(currentScene->getNextSceneID());
        }
    }
}

