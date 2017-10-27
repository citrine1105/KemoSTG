#include "../../Header/GameScene/GameMain.h"

cMainGameScene::cMainGameScene(iSceneChanger<eGameScene> *Changer) : cGameBaseScene(Changer) {

}

cMainGameScene::~cMainGameScene() {

}

std::list<cPlayerBullet>* cMainGameScene::GetPlayerBullet() {
	return &mPlayerBullet;
}

void cMainGameScene::Initialize() {
	cImageResourceContainer::GetInstance()->GetElement(eImage_GameBackGround)->SetPath(_T("./Data/Image/Game/Background/test.png"));

	cImageResourceContainer::GetInstance()->GetElement(eImage_GameBackGround)->Load();

	mPlayer.at(0).SetInputPad(ppVirtualPad[0]);
	mPlayer.at(1).SetInputPad(ppVirtualPad[1]);

	mBackground.MoveToPoint(0.0, 1200.0, 90 * 60);

	mTimer.Initialize(0, (cImageResourceContainer::GetInstance()->GetElement(eImage_Bomb)->GetHandleNum() * 2 - 2) * 5, eCountMode_CountUp, true);
	mBossTimer.Initialize(120.0, 1000.0, eCountMode_CountDown);

	mTimer.Start();
	mBossTimer.Start();
}

void cMainGameScene::Finalize() {

}

void cMainGameScene::Update() {
	mTimer.Update();
	mBossTimer.Update();
	mBackground.Update();

	//if (ppVirtualPad[0]->GetInputState(eButton_FullAuto) % 4 == 1) {
	//	cPoint2D tPoint;
	//	cVector2D tVector;
	//	cBullet tBullet;
	//	for (int i = 0; i < 5; i++) {
	//		tPoint.SetPoint(mPlayer.at(0).GetPositionX(), mPlayer.at(0).GetPositionY());
	//		tVector.SetPolarForm(TO_RADIAN(270.0 + 12.0 * (i - 2)), 18.0);
	//		tBullet.Initialize(tPoint, tVector);
	//		mBullet.push_back(tBullet);
	//	}
	//}

	for (auto &i : mPlayer) {
		i.Update();
	}
	for (auto &i : mEnemy) {
		i.Update();
	}
	for (auto &i : mBullet) {
		i.Update();
		if (mBulletOutCollider.GetCollisionFlag(i)) {

		}
	}
}

void cMainGameScene::Draw() {
	std::array<std::tstring, 2> tScore;
	std::array<unsigned int, 2> tDispScoreRate;	// 表示用スコアレート
	std::array<int, 2> tScoreRateDigit;	// スコアレート桁数

	tScore.at(0) = std::to_tstring(mPlayer.at(0).GetScore().mScore);
	tScore.at(1) = std::to_tstring(mPlayer.at(1).GetScore().mScore);

	tDispScoreRate.at(0) = mPlayer.at(0).GetScoreRate();
	tDispScoreRate.at(1) = mPlayer.at(1).GetScoreRate();

	for (auto &i : tDispScoreRate) {
		if (i > 999999) {
			i = 999999;
		}
	}

	tScoreRateDigit.at(0) = static_cast<int>(floor(log10(tDispScoreRate.at(0)))) + 1;
	tScoreRateDigit.at(1) = static_cast<int>(floor(log10(tDispScoreRate.at(1)))) + 1;

	DrawGraphF(0.0f, static_cast<float>(mBackground.GetPositionY()) - 640.0f, cImageResourceContainer::GetInstance()->GetElement(eImage_GameBackGround)->GetHandle(), FALSE);

	for (auto &i : mEnemy) {
		i.Draw();
	}

	for (auto &i : mPlayer) {
		i.Draw();
	}

	for (auto &i : mPlayerBullet) {
		i.Draw();
	}

	// ボス体力ゲージ
	DrawBox(12 + 5, 56 + 2, 480 - 12 - 5, 56 + 16 - 2, GetColor(0x52, 0xCC, 0x14), TRUE);
	DrawGraph(12, 56, cImageResourceContainer::GetInstance()->GetElement(eImage_LifeGauge)->GetHandle(0), TRUE);
	DrawGraph(480 - 12 - 16, 56, cImageResourceContainer::GetInstance()->GetElement(eImage_LifeGauge)->GetHandle(2), TRUE);
	for (int i = 12 + 16; i < 480 - 12 - 16; i += 16) {
		DrawGraph(i, 56, cImageResourceContainer::GetInstance()->GetElement(eImage_LifeGauge)->GetHandle(1), TRUE);
	}
	mBossTimer.Draw(240, 110);

	// スコア
	DrawGraph(0, 0, cImageResourceContainer::GetInstance()->GetElement(eImage_ScoreBoard)->GetHandle(0), TRUE);
	DrawGraph(480 - 160, 0, cImageResourceContainer::GetInstance()->GetElement(eImage_ScoreBoard)->GetHandle(1), TRUE);
	DrawStringToHandle(16 + GetDrawStringWidthToHandle(_T("3999999999"), _tcsclen(_T("3999999999")), cFontContainer::GetInstance()->GetElement(eFont_GameFont)) - GetDrawStringWidthToHandle(tScore.at(0).c_str(), tScore.at(0).size(), cFontContainer::GetInstance()->GetElement(eFont_GameFont)), 24,
		tScore.at(0).c_str(), GetColor(0xFF, 0xFF, 0xFF), cFontContainer::GetInstance()->GetElement(eFont_GameFont));
	DrawStringToHandle(480 - 16 - GetDrawStringWidthToHandle(tScore.at(1).c_str(), tScore.at(1).size(), cFontContainer::GetInstance()->GetElement(eFont_GameFont)), 24,
		tScore.at(1).c_str(), GetColor(0xFF, 0xFF, 0xFF), cFontContainer::GetInstance()->GetElement(eFont_GameFont));

	// スコアレート
	// 1P
	DrawGraph(12 + cImageResourceContainer::GetInstance()->GetElement(eImage_RateNumber)->GetSizeX() * 0, 108, cImageResourceContainer::GetInstance()->GetElement(eImage_RateNumber)->GetHandle(10), TRUE);
	for (int i = 0; i < tScoreRateDigit.at(0); i++) {
		DrawGraph(12 + cImageResourceContainer::GetInstance()->GetElement(eImage_RateNumber)->GetSizeX() * (tScoreRateDigit.at(0) - i), 108, cImageResourceContainer::GetInstance()->GetElement(eImage_RateNumber)->GetHandle(tDispScoreRate.at(0) / static_cast<int>(pow(10, i)) % 10), TRUE);
	}
	// 2P
	for (int i = 0; i <= tScoreRateDigit.at(1); i++) {
		if (i == tScoreRateDigit.at(1)) {
			DrawGraph(GAME_SCREEN_WIDTH - 12 + -cImageResourceContainer::GetInstance()->GetElement(eImage_RateNumber)->GetSizeX() * (i + 1), 108, cImageResourceContainer::GetInstance()->GetElement(eImage_RateNumber)->GetHandle(10), TRUE);
		}
		else {
			DrawGraph(GAME_SCREEN_WIDTH - 12 + -cImageResourceContainer::GetInstance()->GetElement(eImage_RateNumber)->GetSizeX() * (i + 1), 108, cImageResourceContainer::GetInstance()->GetElement(eImage_RateNumber)->GetHandle(tDispScoreRate.at(1) / static_cast<int>(pow(10, i)) % 10), TRUE);
		}
	}

	// ライフ
	for (int i = 0; i < mPlayer.at(0).GetLife(); i++) {
		DrawGraph(12 + 24 * i, 80, cImageResourceContainer::GetInstance()->GetElement(eImage_Life)->GetHandle(), TRUE);
	}
	for (int i = 0; i < mPlayer.at(1).GetLife(); i++) {
		DrawGraph(480 - 12 - 20 + -24 * i, 80, cImageResourceContainer::GetInstance()->GetElement(eImage_Life)->GetHandle(), TRUE);
	}

	// ボム
	DrawGraph(12, 640 - 8 - 20 - 8 - 14, cImageResourceContainer::GetInstance()->GetElement(eImage_CaptionBomb)->GetHandle(), TRUE);
	for (int i = 0; i < mPlayer.at(0).GetBomb(); i++) {
		if (mTimer.GetTime() / 5 % 6 < 4) {
			DrawGraph(12 + 24 * i, 640 - 8 - 20, cImageResourceContainer::GetInstance()->GetElement(eImage_Bomb)->GetHandle(mTimer.GetTime() / 5 % 6), TRUE);
		}
		else {
			DrawGraph(12 + 24 * i, 640 - 8 - 20, cImageResourceContainer::GetInstance()->GetElement(eImage_Bomb)->GetHandle(6 - mTimer.GetTime() / 5 % 6), TRUE);
		}
	}
	DrawGraph(480 - 12 - cImageResourceContainer::GetInstance()->GetElement(eImage_CaptionBomb)->GetSizeX(), 640 - 8 - 20 - 8 - 14, cImageResourceContainer::GetInstance()->GetElement(eImage_CaptionBomb)->GetHandle(), TRUE);
	for (int i = 0; i < mPlayer.at(1).GetBomb(); i++) {
		if (mTimer.GetTime() / 5 % 6 < 4) {
			DrawGraph(480 - 12 - 20 + -24 * i, 640 - 8 - 20, cImageResourceContainer::GetInstance()->GetElement(eImage_Bomb)->GetHandle(mTimer.GetTime() / 5 % 6), TRUE);
		}
		else {
			DrawGraph(480 - 12 - 20 + -24 * i, 640 - 8 - 20, cImageResourceContainer::GetInstance()->GetElement(eImage_Bomb)->GetHandle(6 - mTimer.GetTime() / 5 % 6), TRUE);
		}
	}

	//ppVirtualPad[0]->Draw();
}