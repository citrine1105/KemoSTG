#include "../../Header/Scene/Load.h"

cLoadScene::cLoadScene(iSceneChanger<eScene> *Changer) : cScene(Changer) {

}

void cLoadScene::Initialize() {
	// UI描画用スクリーンの生成
	mInterfaceScreen = MakeScreen(DISPLAY_SHORT, DISPLAY_SHORT, TRUE);
	SetDrawScreen(mInterfaceScreen);
	SetDrawMode(DX_DRAWMODE_BILINEAR);
	SetDrawScreen(DX_SCREEN_BACK);

	// フォントハンドルの取得
	if (cSystemConfig::GetInstance()->GetConfig().mDisplayWidth >= cSystemConfig::GetInstance()->GetConfig().mDisplayHeight) {
		cFontContainer::GetInstance()->SetElement(eFont_MainInterfaceFont, CreateFontToHandle(_T("ＭＳ 明朝"), cSystemConfig::GetInstance()->GetConfig().mDisplayHeight / 24, 0, DX_FONTTYPE_ANTIALIASING_4X4));
		cFontContainer::GetInstance()->SetElement(eFont_GlobalInterfaceFont, CreateFontToHandle(_T("Palatino Linotype"), cSystemConfig::GetInstance()->GetConfig().mDisplayHeight / 24, 0, DX_FONTTYPE_ANTIALIASING_4X4));
	}
	else {
		cFontContainer::GetInstance()->SetElement(eFont_MainInterfaceFont, CreateFontToHandle(_T("ＭＳ 明朝"), cSystemConfig::GetInstance()->GetConfig().mDisplayWidth / 24, 0, DX_FONTTYPE_ANTIALIASING_4X4));
		cFontContainer::GetInstance()->SetElement(eFont_GlobalInterfaceFont, CreateFontToHandle(_T("Palatino Linotype"), cSystemConfig::GetInstance()->GetConfig().mDisplayWidth / 24, 0, DX_FONTTYPE_ANTIALIASING_4X4));
	}
	cFontContainer::GetInstance()->SetElement(eFont_GameFont, CreateFontToHandle(_T("Palatino Linotype"), 18, 0, DX_FONTTYPE_ANTIALIASING_EDGE_4X4));
	cFontContainer::GetInstance()->SetElement(eFont_GameCaption, CreateFontToHandle(_T("ＭＳ 明朝"), 20, 0, DX_FONTTYPE_ANTIALIASING_4X4));
	cFontContainer::GetInstance()->SetElement(eFont_TimerFont, CreateFontToHandle(_T("Palatino Linotype"), 26, 0, DX_FONTTYPE_ANTIALIASING_EDGE_4X4));
	cFontContainer::GetInstance()->SetElement(eFont_MiniTimerFont, CreateFontToHandle(_T("Palatino Linotype"), 18, 0, DX_FONTTYPE_ANTIALIASING_EDGE_4X4));

	cImageResourceContainer::GetInstance()->GetElement(eImage_RectCollisionRange)->SetPath(_T("./Data/Image/CollisionTest/rect.png"));
	cImageResourceContainer::GetInstance()->GetElement(eImage_EllipseCollisionRange)->SetPath(_T("./Data/Image/CollisionTest/ellipse.png"));
}

void cLoadScene::Finalize() {

}

void cLoadScene::Update() {
	cScene::Update();
	if (GetASyncLoadNum() == 0) {
		pSceneChanger->ChangeScene(eScene_Title);
	}
}

void cLoadScene::Draw() {
	DrawString(0, 0, _T("Loading"), GetColor(0xFF, 0xFF, 0xFF));
}