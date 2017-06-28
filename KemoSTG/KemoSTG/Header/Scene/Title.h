#pragma once
#include "../Scene.h"

class cTitleScene : public cScene {
public:
	cTitleScene(iSceneChanger<eScene> *Changer);
	void Initialize() override;
	void Finalize() override;
	void Update() override;
	void Draw() override;
};