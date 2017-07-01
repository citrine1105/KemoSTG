#pragma once
#include "Include.h"
#include "SceneChanger.h"
#include "VirtualPad.h"

#define GAME_SCREEN_WIDTH 480	// ゲーム画面幅
#define GAME_SCREEN_HEIGHT 640	// ゲーム画面高さ

enum eGameScene {
	eGameScene_Notice,
	eGameScene_Logo,
	eGameScene_Title,
	eGameScene_Demo,
	eGameScene_Select,
	eGameScene_Instruction,
	eGameScene_Game,
	eGameScene_NameEntry,
	eGameScene_Ranking,
	eGameScene_None
};

class cGameBaseScene : public iInitialization, iActivity {
protected:
	iSceneChanger<eGameScene> *pSceneChanger;	// シーン切り替えインターフェース

	static cVirtualPad **ppVirtualPad;

	static int mInformationFont;	// 情報表示用フォント
public:
	cGameBaseScene(iSceneChanger<eGameScene> *Changer);
	virtual ~cGameBaseScene();

	void SetVirtualPad(cVirtualPad Pad[2]);	// パッドの情報を受け渡し

	virtual void Initialize() override;
	virtual void Finalize() override;
	virtual void Update() override;
	virtual void Draw() override;
};