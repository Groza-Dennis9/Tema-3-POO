#ifndef TEMA_3_POO_GAMEENGINE_H
#define TEMA_3_POO_GAMEENGINE_H

#include "DialogueScene.h"
#include "InvestigationScene.h"
#include "EngineConfig.h"
#include "ChoiceScene.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <memory>

class GameEngine : public std::enable_shared_from_this<GameEngine> {
private:
    sf::RenderWindow window;
    unique_ptr<BaseScene> currentScene;

    CacheManager<string, sf::Texture> texManager;
    CacheManager<string, sf::Font> fontManager;
    CacheManager<string, sf::SoundBuffer> soundManager;

    sf::Music globalBGM;
    string currentPlayingBGMPath = "";

public:
    GameEngine();

    void init();

    void updateBGM(const string& path);

    template <typename SceneType, typename... Args>
    unique_ptr<SceneType> createScene(Args&&... args) {
        return make_unique<SceneType>(forward<Args>(args)...);
    }

    void goToScene(const string& id);

    void run();
};

#endif //TEMA_3_POO_GAMEENGINE_H