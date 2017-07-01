#include "../../Header/GameScene/GameLogo.h"

cLogoGameScene::cLogoGameScene(iSceneChanger<eGameScene> *Changer) : cGameBaseScene(Changer) {

}

cLogoGameScene::~cLogoGameScene() {

}

void cLogoGameScene::Initialize() {
	cImageResourceContainer::GetInstance()->GetElement(eImage_GameLogo)->SetPath(_T("./Data/Image/Game/Logo/logo.png"));
	cImageResourceContainer::GetInstance()->GetElement(eImage_GameLogo)->SetDivisionSize(2, 2, 1, GAME_SCREEN_WIDTH, GAME_SCREEN_HEIGHT);
	cImageResourceContainer::GetInstance()->GetElement(eImage_GameLogo)->Load();
	mFade.SetPosition(0.0, 0.0);
	mTimer.Start();
}

void cLogoGameScene::Finalize() {
	cImageResourceContainer::GetInstance()->GetElement(eImage_GameLogo)->Delete();
}

void cLogoGameScene::Update() {
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
	if (mTimer.GetSecond() >= 10.0) {
		pSceneChanger->ChangeScene(eGameScene_Title);
	}
}

void cLogoGameScene::Draw() {
	double tParam;	// フェードイン/アウト用
	mFade.GetPosition(&tParam, nullptr);

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, static_cast<int>(tParam));
	if (mTimer.GetSecond() < 5.0) {
		DrawGraph(0, 0, cImageResourceContainer::GetInstance()->GetElement(eImage_GameLogo)->GetHandle(0), FALSE);
	}
	else {
		DrawGraph(0, 0, cImageResourceContainer::GetInstance()->GetElement(eImage_GameLogo)->GetHandle(1), FALSE);
	}
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);

	if (mTimer.GetValue() % 30 < 20) {
		DrawStringToHandle(GAME_SCREEN_WIDTH / 2 - GetDrawStringWidthToHandle(_T("PRESS START BUTTON"), _tcsclen(_T("PRESS START BUTTON")), cGameBaseScene::mInformationFont) / 2, 24 * 14 + 8,
			_T("PRESS START BUTTON"), GetColor(0xFF, 0xFF, 0xFF), cGameBaseScene::mInformationFont);
	}
}