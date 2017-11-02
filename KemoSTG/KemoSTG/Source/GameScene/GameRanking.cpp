#include "../../Header/GameScene/GameRanking.h"

cRankingGameScene::cRankingGameScene(iSceneChanger<eGameScene> *Changer) : cGameBaseScene(Changer) {
	
}

cRankingGameScene::~cRankingGameScene() {

}

void cRankingGameScene::Initialize() {
	for (int i = 0; i < mSprite.size(); i++) {
		mSprite.at(i).SetPosition(GAME_SCREEN_WIDTH, 24 * ((i + 2) * 2) + 8);
	}

	// テストデータ
	for (int i = 0; i < mScore.size(); i++) {
		mScore.at(i).mScore = 1000000U - 100000 * i;
		mScore.at(i).mContinue = i / 2;
		mScore.at(i).mMaxRate = 1000 - 50 * i;
		mScore.at(i).mCharacter = static_cast<enum ePlayerCharacter>(i / 2 % 2);
		mScore.at(i).mType = static_cast<enum ePossessType>(i % 2);
	}
	mScore.at(0).mName = _T("OBO");
	mScore.at(1).mName = _T("RO.");
	mScore.at(2).mName = _T("NO.");
	mScore.at(3).mName = _T("MAY");
	mScore.at(4).mName = _T("OIG");
	mScore.at(5).mName = _T("O.T");
	mScore.at(6).mName = _T("ACH");
	mScore.at(7).mName = _T("I");
	mScore.at(8).mName = _T("C.L");
	mScore.at(9).mName = _T("AB");

	mTimer.Start();
}

void cRankingGameScene::Finalize() {

}

void cRankingGameScene::Update() {
	mTimer.Update();

	if (ppVirtualPad[0]->GetInputState(eButton_Shot) == 1) {
		pSceneChanger->ChangeScene(eGameScene_Logo);
	}

	for (int i = 0; i < mSprite.size(); i++) {
		if (mTimer.GetTime() == 10 * (9 - i) + 30) {
			mSprite.at(i).MoveToPoint(0, 24 * ((i + 2) * 2) + 8, 40, eEasing_Quint);
		}
		mSprite.at(i).Update();
	}
}

void cRankingGameScene::Draw() {
	std::tstring tBuffer;
	for (int i = 0; i < mScore.size(); i++) {
		tBuffer = std::to_tstring(i + 1);
		switch (i + 1) {
		case 1:
			tBuffer += _T("ST");
			break;
		case 2:
			tBuffer += _T("ND");
			break;
		case 3:
			tBuffer += _T("RD");
			break;
		default:
			tBuffer += _T("TH");
			break;
		}
		DrawStringToHandle(mSprite.at(i).GetPositionX() + 12 * 2, 24 * ((i + 2) * 2) + 8, tBuffer.c_str(), GetColor(0xFF, 0xFF, 0xFF), cFontContainer::GetInstance()->GetElement(eFont_GameFont));

		tBuffer = mScore.at(i).mName;
		DrawStringToHandle(mSprite.at(i).GetPositionX() + 12 * 8, 24 * ((i + 2) * 2) + 8, tBuffer.c_str(), GetColor(0xFF, 0xFF, 0xFF), cFontContainer::GetInstance()->GetElement(eFont_GameFont));

		tBuffer = std::to_tstring(mScore.at(i).mScore);
		DrawStringToHandle(mSprite.at(i).GetPositionX() + 12 * 24 - GetDrawStringWidthToHandle(tBuffer.c_str(), tBuffer.size(), cFontContainer::GetInstance()->GetElement(eFont_GameFont)),
			24 * ((i + 2) * 2) + 8, tBuffer.c_str(), GetColor(0xFF, 0xFF, 0xFF), cFontContainer::GetInstance()->GetElement(eFont_GameFont));

		tBuffer = _T("MAX ");
		DrawStringToHandle(mSprite.at(i).GetPositionX() + 12 * 28, 24 * ((i + 2) * 2) + 8, tBuffer.c_str(), GetColor(0xFF, 0xFF, 0xFF), cFontContainer::GetInstance()->GetElement(eFont_GameFont));

		tBuffer = std::to_tstring(mScore.at(i).mMaxRate);
		DrawStringToHandle(mSprite.at(i).GetPositionX() + 12 * 38 - GetDrawStringWidthToHandle(tBuffer.c_str(), tBuffer.size(), cFontContainer::GetInstance()->GetElement(eFont_GameFont)),
			24 * ((i + 2) * 2) + 8, tBuffer.c_str(), GetColor(0xFF, 0xFF, 0xFF), cFontContainer::GetInstance()->GetElement(eFont_GameFont));
	}
}