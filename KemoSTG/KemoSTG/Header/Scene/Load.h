#pragma once
#include "../Scene.h"

class cLoadScene : public cScene {
public:
	cLoadScene(iSceneChanger<eScene> *Changer);
	void Initialize() override;
	void Finalize() override;
	void Update() override;
	void Draw() override;
};