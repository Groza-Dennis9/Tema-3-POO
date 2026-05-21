#include "EngineConfig.h"

EngineConfig& EngineConfig::getInstance() {
    static EngineConfig instance;
    return instance;
}

[[nodiscard]] unsigned int EngineConfig::getWidth() const { return windowWidth; }
[[nodiscard]] unsigned int EngineConfig::getHeight() const { return windowHeight; }
[[nodiscard]] string EngineConfig::getTitle() const { return windowTitle; }