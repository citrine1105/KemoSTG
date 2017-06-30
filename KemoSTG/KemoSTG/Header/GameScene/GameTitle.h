#pragma once
#include "../GameBaseScene.h"
#include "../ImageResource.h"
#include "../Sprite.h"

class cTitleGameScene : public cGameBaseScene {
private:
	cTimer mTimer;
	cImageResource mImage;	// タイトル画像(置き場所変えて)
	cSprite mFade;	// フェードイン/アウト用
public: 
	cTitleGameScene(iSceneChanger<eGameScene> *Changer);
	~cTitleGameScene();

	void Initialize() override;
	void Finalize() override;
	void Update() override;
	void Draw() override;
};