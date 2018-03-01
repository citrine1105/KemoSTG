#include "../../Header/GameScene/GameRanking.h"

cRankingGameScene::cRankingGameScene(iSceneChanger<eGameScene> *Changer) : cGameBaseScene(Changer) {
	
}

cRankingGameScene::~cRankingGameScene() {

}

void cRankingGameScene::Initialize() {
	for (int i = 0; i < mSprite.size(); i++) {
		mSprite.at(i).SetPosition(i % 2 == 0 ? -GAME_SCREEN_WIDTH : GAME_SCREEN_WIDTH, 0);
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

	if (mVirtualPad.at(0).GetInputState(eButton_Shot) == 1) {
		pSceneChanger->ChangeScene(eGameScene_Logo);
	}

	for (int i = 0; i < mSprite.size(); i++) {
		if (mTimer.GetTime() == 10 * (9 - i) + 30) {
			mSprite.at(i).MoveToPointX(0, 40, eEasing_Quint);
			mSprite.at(i).MoveToPointY(24 * ((i + 2) * 2) + 8, 40, eEasing_Cubic);
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
			tBuffer += _T("st");
			break;
		case 2:
			tBuffer += _T("nd");
			break;
		case 3:
			tBuffer += _T("rd");
			break;
		default:
			tBuffer += _T("th");
			break;
		}
		DrawStringFToHandle(mSprite.at(i).GetPositionX() + 12 * 2, mSprite.at(i).GetPositionY(), tBuffer.c_str(), GetColor(0xFF, 0xFF, 0xFF), gGameFontContainer.GetElement(eGameFont_Interface)->GetHandle());

		tBuffer = mScore.at(i).mName;
		DrawStringFToHandle(mSprite.at(i).GetPositionX() + 12 * 8, mSprite.at(i).GetPositionY(), tBuffer.c_str(), GetColor(0xFF, 0xFF, 0xFF), gGameFontContainer.GetElement(eGameFont_Interface)->GetHandle());

		tBuffer = std::to_tstring(mScore.at(i).mScore);
		DrawStringFToHandle(mSprite.at(i).GetPositionX() + 12 * 24 - GetDrawStringWidthToHandle(tBuffer.c_str(), tBuffer.size(), gGameFontContainer.GetElement(eGameFont_Interface)->GetHandle()),
			mSprite.at(i).GetPositionY(), tBuffer.c_str(), GetColor(0xFF, 0xFF, 0xFF), gGameFontContainer.GetElement(eGameFont_Interface)->GetHandle());

		tBuffer = _T("MAX ");
		DrawStringFToHandle(mSprite.at(i).GetPositionX() + 12 * 28, mSprite.at(i).GetPositionY(), tBuffer.c_str(), GetColor(0xFF, 0xFF, 0xFF), gGameFontContainer.GetElement(eGameFont_Interface)->GetHandle());

		tBuffer = std::to_tstring(mScore.at(i).mMaxRate);
		DrawStringFToHandle(mSprite.at(i).GetPositionX() + 12 * 38 - GetDrawStringWidthToHandle(tBuffer.c_str(), tBuffer.size(), gGameFontContainer.GetElement(eGameFont_Interface)->GetHandle()),
			mSprite.at(i).GetPositionY(), tBuffer.c_str(), GetColor(0xFF, 0xFF, 0xFF), gGameFontContainer.GetElement(eGameFont_Interface)->GetHandle());
	}
}