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
	for (int i = 0; i < 2; i++) {
		if (ppVirtualPad[i]->GetInputState(eButton_Pause) == 1) {
			pSceneChanger->ChangeScene(eGameScene_Game);
		}
	}

	if (GetASyncLoadNum() == 0) {
		if (mTimer.GetTime() == 0) {
			mFade.MoveToPoint(255.0, 0.0, 30);
		}
		else if (mTimer.GetTime() == 60 * 4 + 20) {
			mFade.MoveToPoint(0.0, 0.0, 30);
		}
		else if (mTimer.GetTime() == 60 * 5) {
			mFade.MoveToPoint(255.0, 0.0, 30);
		}
		else if (mTimer.GetTime() == 60 * 9 + 20) {
			mFade.MoveToPoint(0.0, 0.0, 30);
		}
		mTimer.Update();
		mFade.Update();
	}

	for (int i = 0; i < 2; i++) {
		if (ppVirtualPad[i]->GetInputState(eButton_Shot) == 1) {
			pSceneChanger->ChangeScene(eGameScene_Title);
		}
	}
	if (mTimer.GetSecond() >= 10.0) {
		pSceneChanger->ChangeScene(eGameScene_Title);
	}
}

void cLogoGameScene::Draw() {
	std::tstring tMessage;
	tMessage = _T("PRESS [1] KEY");

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, static_cast<int>(mFade.GetPositionX()));
	if (mTimer.GetSecond() < 5.0) {
		DrawGraph(0, 0, cImageResourceContainer::GetInstance()->GetElement(eImage_GameLogo)->GetHandle(0), FALSE);
	}
	else {
		DrawGraph(0, 0, cImageResourceContainer::GetInstance()->GetElement(eImage_GameLogo)->GetHandle(1), FALSE);
	}
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);

	if (mTimer.GetTime() % 30 < 20) {
		DrawStringToHandle(GAME_SCREEN_WIDTH / 2 - GetDrawStringWidthToHandle(tMessage.c_str(), _tcsclen(_T("PRESS START BUTTON")), cFontContainer::GetInstance()->GetElement(eFont_GameFont)) / 2, 24 * 14 + 8,
			tMessage.c_str(), GetColor(0xFF, 0xFF, 0xFF), cFontContainer::GetInstance()->GetElement(eFont_GameFont));
	}
}