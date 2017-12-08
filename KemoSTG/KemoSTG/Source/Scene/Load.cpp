﻿#include "../../Header/Scene/Load.h"

cLoadScene::cLoadScene(iSceneChanger<eScene> *Changer) : cScene(Changer) {

}

void cLoadScene::Initialize() {
	// UI描画用スクリーンの生成
	mInterfaceScreen = MakeScreen(DISPLAY_SHORT, DISPLAY_SHORT, TRUE);
	SetDrawScreen(mInterfaceScreen);
	SetDrawMode(DX_DRAWMODE_BILINEAR);
	SetDrawScreen(DX_SCREEN_BACK);

	// フォントハンドルの取得
	gSystemFont.Initialize(eSystemFont_TotalNum);
	gSystemFont.GetElement(eSystemFont_UIFont)->SetFontName(_T("Palatino Linotype"));
	gSystemFont.GetElement(eSystemFont_LocalizedUIFont)->SetFontName(_T("ＭＳ 明朝"));
	for (int i = 0; i < eSystemFont_TotalNum; i++) {
		gSystemFont.GetElement(i)->SetThickness(0);
		gSystemFont.GetElement(i)->SetFontType(DX_FONTTYPE_ANTIALIASING_4X4);
	}

	if (DISPLAY_WIDTH >= DISPLAY_HEIGHT) {
		gSystemFont.GetElement(eSystemFont_UIFont)->SetSize(DISPLAY_HEIGHT / 24);
		gSystemFont.GetElement(eSystemFont_LocalizedUIFont)->SetSize(DISPLAY_HEIGHT / 24);
	}
	else {
		gSystemFont.GetElement(eSystemFont_UIFont)->SetSize(DISPLAY_WIDTH / 24);
		gSystemFont.GetElement(eSystemFont_LocalizedUIFont)->SetSize(DISPLAY_WIDTH / 24);
	}
	//cFontContainer::GetInstance()->SetElement(eFont_GameFont, CreateFontToHandle(_T("Palatino Linotype"), 18, 0, DX_FONTTYPE_ANTIALIASING_EDGE_4X4));
	//cFontContainer::GetInstance()->SetElement(eFont_GameCaption, CreateFontToHandle(_T("ＭＳ 明朝"), 20, 0, DX_FONTTYPE_ANTIALIASING_4X4));
	//cFontContainer::GetInstance()->SetElement(eFont_TimerFont, CreateFontToHandle(_T("Palatino Linotype"), 26, 0, DX_FONTTYPE_ANTIALIASING_EDGE_4X4));
	//cFontContainer::GetInstance()->SetElement(eFont_MiniTimerFont, CreateFontToHandle(_T("Palatino Linotype"), 18, 0, DX_FONTTYPE_ANTIALIASING_EDGE_4X4));

	//cImageResourceContainer::GetInstance()->GetElement(eImage_RectCollisionRange)->SetPath(_T("./Data/Image/CollisionTest/rect.png"));
	//cImageResourceContainer::GetInstance()->GetElement(eImage_EllipseCollisionRange)->SetPath(_T("./Data/Image/CollisionTest/ellipse.png"));

	gSystemFont.Load();
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
	if (CheckHandleASyncLoad(mInterfaceScreen) == FALSE) {
		SetDrawScreen(mInterfaceScreen);
		ClearDrawScreen();
		if (CheckHandleASyncLoad(gSystemFont.GetElement(eSystemFont_UIFont)->GetHandle()) == FALSE) {
			DrawStringToHandle(0, DISPLAY_SHORT - GetFontSizeToHandle(gSystemFont.GetElement(eSystemFont_UIFont)->GetHandle()) - UPSCALE(8), _T("Loading"), GetColor(0xFF, 0xFF, 0xFF), gSystemFont.GetElement(eSystemFont_UIFont)->GetHandle());
		}
	}

	SetDrawScreen(DX_SCREEN_BACK);

	SetDrawBlendMode(DX_BLENDMODE_PMA_ALPHA, 255);
	DrawRotaGraphF(DISPLAY_WIDTH / 2, DISPLAY_HEIGHT / 2, 1.0, TO_RADIAN(static_cast<double>(90 * cSystemConfig::GetInstance()->GetConfig().mRotation)), mInterfaceScreen, TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
}