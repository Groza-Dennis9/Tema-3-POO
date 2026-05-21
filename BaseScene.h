#ifndef TEMA_3_POO_BASESCENE_H
#define TEMA_3_POO_BASESCENE_H

#include <SFML/Graphics.hpp>

using namespace std;

class BaseScene {
private:
    bool finished = false;
    string nextSceneID = "";

public:
    virtual ~BaseScene() = default;
    virtual void handleInput(sf::Vector2f mousePos, bool clicked) = 0;
    virtual void update() = 0;
    virtual void render(sf::RenderWindow& window) = 0;

    [[nodiscard]] bool isFinished() const;
    void setFinished(bool val);

    [[nodiscard]] string getNextSceneID() const;
    void setNextSceneID(const string& id);
};

#endif //TEMA_3_POO_BASESCENE_H