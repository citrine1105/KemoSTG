#pragma once
#include "../GameBaseScene.h"
#include "../Timer.h"

class cNoticeGameScene : public cGameBaseScene {
private:
	cTimer mTimer;
public:
	cNoticeGameScene(iSceneChanger<eGameScene> *Changer);
	~cNoticeGameScene();

	void Initialize() override;
	void Finalize() override;
	void Update() override;
	void Draw() override;
};