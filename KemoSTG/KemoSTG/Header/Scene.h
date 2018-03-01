#pragma once
#include "Include.h"
#include "SceneChanger.h"
#include "Config.h"
#include "VirtualPad.h"
#include "ImageResourceContainer.h"
#include "FontContainer.h"

#define GAMEPAD_NUM 2	// ゲーム全体で使用するパッドの数

enum eScene {
	eScene_Load,
	eScene_Logo,
	eScene_Title,
	eScene_Menu,
	eScene_Game,

	eScene_None
};

enum eSystemFontIndex {
	eSystemFont_UIFont,				// UI(共通言語)
	eSystemFont_LocalizedUIFont,	// UI(ローカライズ)

	eSystemFont_TotalNum	// 総要素数
};

extern cFontContainer gSystemFont;

class cScene : public iInitialization, iActivity {
protected:
	iSceneChanger<eScene> *pSceneChanger;	// シーン切り替えインターフェース

	static int mInterfaceScreen;	// UI描画用スクリーン

	static std::array<cPad, GAMEPAD_NUM> mPad;	// 物理パッド入力
	static std::array<cVirtualPad, GAMEPAD_NUM> mVirtualPad;	// 仮想パッド入力
public:
	cScene(iSceneChanger<eScene> *Changer);
	virtual ~cScene();
	virtual void Initialize() override;
	virtual void Finalize() override;
	virtual void Update() override;
	virtual void Draw() override;
};