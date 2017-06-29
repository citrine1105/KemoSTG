#include "../../Header/GameScene/Logo.h"

cLogoGameScene::cLogoGameScene(iSceneChanger<eGameScene> *Changer) : cGameBaseScene(Changer) {

}

cLogoGameScene::~cLogoGameScene() {

}

void cLogoGameScene::Initialize() {
	mLogoImage[0].SetPath(_T("./Data/Image/Game/Logo/am.png"));
	mLogoImage[1].SetPath(_T("./Data/Image/Game/Logo/clab.png"));
	mLogoImage[0].Load();
	mLogoImage[1].Load();
	mFade.SetPosition(0.0, 0.0);
	mTimer.Start();
}

void cLogoGameScene::Finalize() {

}

void cLogoGameScene::Update() {
	cGameBaseScene::Update();
	if (GetASyncLoadNum() == 0) {
		if (mTimer.GetValue() == 0) {
			mFade.MoveToPoint(255.0, 0.0, 30);
		}
		else if (mTimer.GetValue() == 60 * 4 + 20) {
			mFade.MoveToPoint(0.0, 0.0, 30);
		}
		else if (mTimer.GetValue() == 60 * 5) {
			mFade.MoveToPoint(255.0, 0.0, 30);
		}
		else if (mTimer.GetValue() == 60 * 9 + 20) {
			mFade.MoveToPoint(0.0, 0.0, 30);
		}
		mTimer.Update();
		mFade.Update();
	}
}

void cLogoGameScene::Draw() {
	double tParam;	// フェードイン/アウト用
	mFade.GetPosition(&tParam, nullptr);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, static_cast<int>(tParam));
	if (mTimer.GetSecond() < 5.0) {
		DrawGraph(0, 0, mLogoImage[0].GetHandle(), FALSE);
	}
	else {
		DrawGraph(0, 0, mLogoImage[1].GetHandle(), FALSE);
	}
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
	if (mTimer.GetValue() % 30 < 20) {
		DrawStringToHandle(GAME_SCREEN_WIDTH / 2 - GetDrawStringWidthToHandle(_T("PRESS START BUTTON"), _tcsclen(_T("PRESS START BUTTON")), cGameBaseScene::mInformationFont) / 2, 24 * 15,
			_T("PRESS START BUTTON"), GetColor(0xFF, 0xFF, 0xFF), cGameBaseScene::mInformationFont);
	}
}