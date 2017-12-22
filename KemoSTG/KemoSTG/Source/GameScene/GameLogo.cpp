#include "../../Header/GameScene/GameLogo.h"
#include "../../Header/Scene/Game.h"

cImageResourceContainer gLogoImageContainer;	// ロゴ画面で使う画像データコンテナ

cLogoGameScene::cLogoGameScene(iSceneChanger<eGameScene> *Changer) : cGameBaseScene(Changer) {

}

cLogoGameScene::~cLogoGameScene() {

}

void cLogoGameScene::Initialize() {
	//cImageResourceContainer::GetInstance()->GetElement(eImage_GameLogo)->SetPath(_T("./Data/Image/Game/Logo/logo.png"));
	//cImageResourceContainer::GetInstance()->GetElement(eImage_GameLogo)->SetDivisionSize(2, 2, 1, GAME_SCREEN_WIDTH, GAME_SCREEN_HEIGHT);
	//cImageResourceContainer::GetInstance()->GetElement(eImage_GameLogo)->Load();
	mFade.SetPosition(0.0, 0.0);
	mTimer.Start();
}

void cLogoGameScene::Finalize() {
	//cImageResourceContainer::GetInstance()->GetElement(eImage_GameLogo)->Delete();
}

void cLogoGameScene::Update() {
	for (int i = 0; i < 2; i++) {
		if (ppVirtualPad[i]->GetInputState(eButton_Pause) == 1) {
			pSceneChanger->ChangeScene(eGameScene_Game);
		}
	}

	if (GetASyncLoadNum() == 0) {
		//if (mTimer.GetTime() == 0) {
		//	mFade.MoveToPoint(255.0, 0.0, 30);
		//}
		//else if (mTimer.GetTime() == 60 * 4 + 20) {
		//	mFade.MoveToPoint(0.0, 0.0, 30);
		//}
		//else if (mTimer.GetTime() == 60 * 5) {
		//	mFade.MoveToPoint(255.0, 0.0, 30);
		//}
		//else if (mTimer.GetTime() == 60 * 9 + 20) {
		//	mFade.MoveToPoint(0.0, 0.0, 30);
		//}
		for (int i = 0; i < gLogoImageContainer.GetResourceCount(); i++) {
			if (mTimer.GetTime() == 60 * 5 * i) {
				mFade.MoveToPointX(255.0, 30);
			}
			else if (mTimer.GetTime() == 60 * 5 * (i + 1) - 40) {
				mFade.MoveToPointX(0.0, 30);
			}
		}
		mTimer.Update();
		mFade.Update();
	}

	//for (int i = 0; i < 2; i++) {
	//	if (ppVirtualPad[i]->GetInputState(eButton_Shot) == 1) {
	//		pSceneChanger->ChangeScene(eGameScene_Title);
	//	}
	//}
	if (mTimer.GetTime() >= 60 * 5 * gLogoImageContainer.GetResourceCount() - 1) {
		pSceneChanger->ChangeScene(eGameScene_Title);
	}
}

void cLogoGameScene::Draw() {
	std::tstring tMessage;
	tMessage = _T("PRESS START BUTTON");

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, static_cast<int>(mFade.GetPositionX()));
	DrawGraph(0, 0, gLogoImageContainer.GetElement(mTimer.GetTime() / (60 * 5))->GetHandle(), FALSE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);

	if (mTimer.GetTime() % 30 < 20) {
		DrawStringToHandle(GAME_SCREEN_WIDTH / 2 - GetDrawStringWidthToHandle(tMessage.c_str(), _tcsclen(_T("PRESS START BUTTON")), gGameFontContainer.GetElement(eGameFont_Interface)->GetHandle()) / 2, 24 * 14 + 8,
			tMessage.c_str(), GetColor(0xFF, 0xFF, 0xFF), gGameFontContainer.GetElement(eGameFont_Interface)->GetHandle());
	}
}