#pragma once
#include "../GameBaseScene.h"
#include "../ImageResourceContainer.h"
#include "../Sprite.h"
#include "../SelectTimer.h"

class cMainGameScene : public cGameBaseScene {
private:
	cTimer mTimer;
	cSprite mBackground;
	cSelectTimer mBossTimer;
public:
	cMainGameScene(iSceneChanger<eGameScene> *Changer);
	~cMainGameScene();

	void Initialize() override;
	void Finalize() override;
	void Update() override;
	void Draw() override;
};