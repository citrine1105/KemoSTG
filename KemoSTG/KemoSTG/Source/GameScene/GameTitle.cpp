#include "../../Header/GameScene/GameTitle.h"

cImageResourceContainer gGameTitleImageContainer;

cTitleGameScene::cTitleGameScene(iSceneChanger<eGameScene> *Changer) : cGameBaseScene(Changer) {

}

cTitleGameScene::~cTitleGameScene() {

}

void cTitleGameScene::Initialize() {
	mFade.SetPosition(0.0, 0.0);
	mTimer.Start();
}

void cTitleGameScene::Finalize() {

}

void cTitleGameScene::Update() {
	for (int i = 0; i < 2; i++) {
		if (ppVirtualPad[i]->GetInputState(eButton_Pause) == 1) {
			pSceneChanger->ChangeScene(eGameScene_Game);
		}
	}

	if (GetASyncLoadNum() == 0) {
		if (mTimer.GetTime() == 0) {
			mFade.MoveToPointX(255.0, 80);
		}
		else if (mTimer.GetTime() == 60 * 10 - 100) {
			mFade.MoveToPointX(0.0, 80);
		}
		if (mTimer.GetSecond() >= 10.0) {
			pSceneChanger->ChangeScene(eGameScene_Logo);
		}
		mTimer.Update();
		mFade.Update();
	}

	for (int i = 0; i < 2; i++) {
		if (ppVirtualPad[i]->GetInputState(eButton_Shot) == 1) {
			pSceneChanger->ChangeScene(eGameScene_Ranking);
		}
	}
}

void cTitleGameScene::Draw() {
	std::tstring tMessage;
	std::tstring tRank;
	std::array<std::tstring, 3> tExtend;
	std::array<std::tstring, 2> tCopyright;
	std::tstring tVersion;

	tMessage = _T("PRESS START BUTTON");
	tRank = _T("RANK: ");
	tRank += _T("NORMAL");
	tExtend.at(0) = _T("-EXTEND-");
	tExtend.at(1) = _T("1ST   10,000,000PTS");
	tExtend.at(2) = _T("2ND  100,000,000PTS");
	tCopyright.at(0) = _T("©2017 Amusement Makers");
	tCopyright.at(1) = _T("Developed by C-Lab");
	tVersion = _T("Ver ");
	tVersion += VERSION_STRING;

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, static_cast<int>(mFade.GetPositionX()));
	DrawGraph(0, 0, gGameTitleImageContainer.GetElement(eGameTitle_Logo)->GetHandle(), FALSE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);

	DrawStringToHandle(GAME_SCREEN_WIDTH / 2 - GetDrawStringWidthToHandle(tRank.c_str(), tRank.size(), cFontContainer::GetInstance()->GetElement(eFont_GameFont)) / 2, 24 * 16 + 8,
		tRank.c_str(), GetColor(0xFF, 0xFF, 0xFF), cFontContainer::GetInstance()->GetElement(eFont_GameFont));

	for (int i = 0; i < tExtend.size(); i++) {
		DrawStringToHandle(GAME_SCREEN_WIDTH / 2 - GetDrawStringWidthToHandle(tExtend.at(i).c_str(), tExtend.at(i).size(), cFontContainer::GetInstance()->GetElement(eFont_GameFont)) / 2, 24 * (18 + i) + 8,
			tExtend.at(i).c_str(), GetColor(0xFF, 0xFF, 0xFF), cFontContainer::GetInstance()->GetElement(eFont_GameFont));
	}

	for (int i = 0; i < tCopyright.size(); i++) {
		DrawStringToHandle(GAME_SCREEN_WIDTH / 2 - GetDrawStringWidthToHandle(tCopyright.at(i).c_str(), tCopyright.at(i).size(), cFontContainer::GetInstance()->GetElement(eFont_GameFont)) / 2, 24 * (22 + i) + 8,
			tCopyright.at(i).c_str(), GetColor(0xFF, 0xFF, 0xFF), cFontContainer::GetInstance()->GetElement(eFont_GameFont));
	}

	//if (cSystemConfig::GetInstance()->GetConfig().fArcade) {
		DrawStringToHandle(8, 8, tVersion.c_str(), GetColor(0xFF, 0xFF, 0xFF), cFontContainer::GetInstance()->GetElement(eFont_GameFont));
	//}

	if (mTimer.GetTime() % 30 < 20) {
		DrawStringToHandle(GAME_SCREEN_WIDTH / 2 - GetDrawStringWidthToHandle(tMessage.c_str(), tMessage.size(), cFontContainer::GetInstance()->GetElement(eFont_GameFont)) / 2, 24 * 14 + 8,
			tMessage.c_str(), GetColor(0xFF, 0xFF, 0xFF), cFontContainer::GetInstance()->GetElement(eFont_GameFont));
	}
}