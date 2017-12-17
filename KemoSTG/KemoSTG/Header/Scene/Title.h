#pragma once
#include "../Scene.h"
#include "../Sprite.h"

enum eTitleIndex {
	eTitle_Logo,
	eTitle_Back,
	eTitle_Guide,

	eTitle_TotalNum
};

extern cImageResourceContainer gTitleImageContainer;

class cTitleScene : public cScene {
protected:
	cTimer mMessageFlash;
	cSprite mMessageFade;
	cSprite mFade;
	bool fNext;
public:
	cTitleScene(iSceneChanger<eScene> *Changer);
	void Initialize() override;
	void Finalize() override;
	void Update() override;
	void Draw() override;
};