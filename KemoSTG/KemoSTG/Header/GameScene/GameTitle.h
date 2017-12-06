#pragma once
#include "../GameBaseScene.h"
#include "../ImageResource.h"
#include "../Sprite.h"

enum eGameTitleIndex {
	eGameTitle_Logo,
	eGameTitle_Background,

	eGameTitle_TotalNum
};

extern cImageResourceContainer gGameTitleImageContainer;

class cTitleGameScene : public cGameBaseScene {
private:
	cTimer mTimer;
	cSprite mFade;	// フェードイン/アウト用
public: 
	cTitleGameScene(iSceneChanger<eGameScene> *Changer);
	~cTitleGameScene();

	void Initialize() override;
	void Finalize() override;
	void Update() override;
	void Draw() override;
};