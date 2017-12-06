#pragma once
#include "../GameBaseScene.h"
#include "../Sprite.h"

extern cImageResourceContainer gLogoImageContainer;

enum eLogoIndex {
	eLogo_AM,
	eLogo_CLab,

	eLogo_TotalNum
};

class cLogoGameScene : public cGameBaseScene {
private:
	cTimer mTimer;
	cSprite mFade;	// フェードイン/アウト用
public:
	cLogoGameScene(iSceneChanger<eGameScene> *Changer);
	~cLogoGameScene();

	void Initialize() override;
	void Finalize() override;
	void Update() override;
	void Draw() override;
};