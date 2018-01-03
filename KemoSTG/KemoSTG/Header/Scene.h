#pragma once
#include "Include.h"
#include "SceneChanger.h"
#include "Config.h"
#include "VirtualPad.h"
#include "ImageResourceContainer.h"
#include "FontContainer.h"

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

	static std::array<cPad, 2> mPad;
	static std::array<cVirtualPad, 2> mVirtualPad;
public:
	cScene(iSceneChanger<eScene> *Changer);
	virtual ~cScene();
	virtual void Initialize() override;
	virtual void Finalize() override;
	virtual void Update() override;
	virtual void Draw() override;
};