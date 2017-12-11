#pragma once
#include "../GameBaseScene.h"
#include "../Player.h"
#include "../Enemy.h"

class cDebugGameScene : public cGameBaseScene {
protected:

public:
	cDebugGameScene(iSceneChanger<eGameScene> *Changer);
	~cDebugGameScene();

	void Initialize() override;
	void Finalize() override;
	void Update() override;
	void Draw() override;
};