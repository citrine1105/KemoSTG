#pragma once
#include "../GameBaseScene.h"
#include "../ImageResource.h"
#include "../Sprite.h"

class cLogoGameScene : public cGameBaseScene {
private:
	cTimer mTimer;
	cImageResource mLogoImage;	// ロゴ画像(置き場所変えて)
	cSprite mFade;	// フェードイン/アウト用
public:
	cLogoGameScene(iSceneChanger<eGameScene> *Changer);
	~cLogoGameScene();

	void Initialize() override;
	void Finalize() override;
	void Update() override;
	void Draw() override;
};