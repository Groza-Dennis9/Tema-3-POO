#include <iostream>
#include "GameEngine.h"

using namespace std;

int main() {
    try {
        auto engine = make_shared<GameEngine>();
        engine->init();
        engine->run();
    }
    catch (const exception& e) {
        cerr << "Eroare critica: " << e.what() << "\n";
    }
    return 0;
}