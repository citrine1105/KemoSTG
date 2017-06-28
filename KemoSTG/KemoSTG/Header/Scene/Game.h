#pragma once
#include "../Scene.h"

class cGameScene : public cScene {
public:
	cGameScene(iSceneChanger<eScene> *Changer);
	void Initialize() override;
	void Finalize() override;
	void Update() override;
	void Draw() override;
};