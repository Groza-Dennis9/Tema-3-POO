#ifndef TEMA_3_POO_ENGINECONFIG_H
#define TEMA_3_POO_ENGINECONFIG_H

#include <string>

using namespace std;

class EngineConfig {
private:
    unsigned int windowWidth = 1200;
    unsigned int windowHeight = 720;
    string windowTitle = "C++ VN Engine";

    EngineConfig() = default;

public:
    EngineConfig(const EngineConfig&) = delete;
    EngineConfig& operator=(const EngineConfig&) = delete;
    EngineConfig(EngineConfig&&) = delete;
    EngineConfig& operator=(EngineConfig&&) = delete;

    static EngineConfig& getInstance();
    [[nodiscard]] unsigned int getWidth() const;
    [[nodiscard]] unsigned int getHeight() const;
    [[nodiscard]] string getTitle() const;
};


#endif //TEMA_3_POO_ENGINECONFIG_H