#pragma once
#include "../Scene.h"
#include "../Sprite.h"
#include "../GameSceneManager.h"

extern cFontContainer gGameFontContainer;

enum eGameFontIndex {
	eGameFont_Interface,	// インターフェース
	eGameFont_Word,		// セリフ

	eGameFont_TotalNum	// 総要素数
};

class cGameScene : public cScene {
protected:
	int mGameScreen;
	cGameSceneManager mGame;

	cImageResource mBackgroundImage;

	cSprite mFade;
public:
	cGameScene(iSceneChanger<eScene> *Changer);
	~cGameScene();

	void Initialize() override;
	void Finalize() override;
	void Update() override;
	void Draw() override;
};