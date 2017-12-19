#pragma once
#include "../GameBaseScene.h"
#include "../Scene/Game.h"
#include "../GameManager.h"
#include "../Sprite.h"
#include "../SelectTimer.h"

class cNameEntryGameScene : public cGameBaseScene {
private:
	cTimer mSceneTimer;	// 経過時間
	cSelectTimer mTimer;	// 残り時間カウント用

	std::array<std::tstring, 6> mItem;
	std::array<std::array<std::tstring, 6>, 2> mResult;

	std::array<cSprite, 6> mItemFade;

	std::array<cSprite, 2> mCursor;
public:
	cNameEntryGameScene(iSceneChanger<eGameScene> *Changer);
	~cNameEntryGameScene();

	void Initialize() override;
	void Finalize() override;
	void Update() override;
	void Draw() override;
};