#include "../../Header/Scene/Load.h"
#include "../../Header/Collider.h"

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

	gSystemFont.GetElement(eSystemFont_UIFont)->SetSize(DISPLAY_SHORT / 28);
	gSystemFont.GetElement(eSystemFont_LocalizedUIFont)->SetSize(DISPLAY_SHORT / 28);

	// 衝突判定デバッグ用
	gColliderDebugImageContainer.Initialize(eCollision_TotalNum);
	gColliderDebugImageContainer.GetElement(eCollision_Rectangle)->SetPath(_T("./Data/Image/CollisionTest/rect.png"));
	gColliderDebugImageContainer.GetElement(eCollision_Ellipse)->SetPath(_T("./Data/Image/CollisionTest/ellipse.png"));

	gColliderDebugImageContainer.Load();
	SetFontCacheUsePremulAlphaFlag(TRUE);
	gSystemFont.Load();
	SetFontCacheUsePremulAlphaFlag(FALSE);
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
			SetDrawBlendMode(DX_BLENDMODE_PMA_ALPHA, 255);
			DrawStringToHandle(DISPLAY_SHORT - GetDrawStringWidthToHandle(_T("Loading"), _tcslen(_T("Loading")), gSystemFont.GetElement(eSystemFont_UIFont)->GetHandle()) - UPSCALE(12), DISPLAY_SHORT - gSystemFont.GetElement(eSystemFont_UIFont)->GetSize() - UPSCALE(8), _T("Loading"), GetColor(0xFF, 0xFF, 0xFF), gSystemFont.GetElement(eSystemFont_UIFont)->GetHandle());
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
		}
	}

	SetDrawScreen(DX_SCREEN_BACK);

	SetDrawBlendMode(DX_BLENDMODE_PMA_ALPHA, 255);
	DrawRotaGraphF(DISPLAY_WIDTH / 2, DISPLAY_HEIGHT / 2, 1.0, TO_RADIAN(static_cast<double>(90 * cSystemConfig::GetInstance()->GetConfig().mRotation)), mInterfaceScreen, TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
}