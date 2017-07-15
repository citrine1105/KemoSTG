#pragma once
#include "../Scene.h"
#include "../Sprite.h"

class cTitleScene : public cScene {
protected:
	cTimer mMessageAnimation;
	cSprite mFade;
	bool fNext;
public:
	cTitleScene(iSceneChanger<eScene> *Changer);
	void Initialize() override;
	void Finalize() override;
	void Update() override;
	void Draw() override;
};