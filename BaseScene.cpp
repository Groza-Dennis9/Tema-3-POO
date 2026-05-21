#include "BaseScene.h"

[[nodiscard]] bool BaseScene::isFinished() const { return finished; }
void BaseScene::setFinished(bool val) { finished = val; }

[[nodiscard]] string BaseScene::getNextSceneID() const { return nextSceneID; }
void BaseScene::setNextSceneID(const string& id) { nextSceneID = id; }
