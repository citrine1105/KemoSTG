﻿#pragma once
#include "Include.h"
#include "SceneChanger.h"
#include "VirtualPad.h"
#include "Config.h"
#include "ImageResourceContainer.h"
#include "SoundResourceContainer.h"
#include "FontContainer.h"

#define GAME_SCREEN_WIDTH 480	// ゲーム画面幅
#define GAME_SCREEN_HEIGHT 640	// ゲーム画面高さ

#define PLAYER_NUM 2	// 最大プレイヤー数

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
	eGameScene_Debug,

	eGameScene_None
};

class cGameBaseScene : public iInitialization, iActivity {
protected:
	iSceneChanger<eGameScene> *pSceneChanger;	// シーン切り替えインターフェース

	static cVirtualPad *pInputPad;	// パッド入力に使用する仮想パッドのポインタ
	static std::array<cVirtualPad, PLAYER_NUM> mVirtualPad;	// ゲーム内で使うパッドの実体
public:
	cGameBaseScene(iSceneChanger<eGameScene> *Changer);
	virtual ~cGameBaseScene();

	void SetVirtualPad(cVirtualPad *Pad);	// パッドの情報を受け渡し
	cVirtualPad* GetVirtualPadPointer(const unsigned int Index);

	virtual void Initialize() override;
	virtual void Finalize() override;
	virtual void Update() override;
	virtual void Draw() override;
};