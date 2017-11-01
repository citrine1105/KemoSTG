#include "../../Header/GameScene/GameMain.h"

cMainGameScene::cMainGameScene(iSceneChanger<eGameScene> *Changer) : cGameBaseScene(Changer) {

}

cMainGameScene::~cMainGameScene() {

}

void cMainGameScene::Initialize() {
	cImageResourceContainer::GetInstance()->GetElement(eImage_GameBackGround)->SetPath(_T("./Data/Image/Game/Background/test.png"));
	cImageResourceContainer::GetInstance()->GetElement(eImage_PlayerRin)->SetPath(_T("./Data/Image/Game/Player/test.png"));
	cImageResourceContainer::GetInstance()->GetElement(eImage_PlayerRin)->SetDivisionSize(12, 3, 4, 64, 64);
	cImageResourceContainer::GetInstance()->GetElement(eImage_PlayerBullet)->SetPath(_T("./Data/Image/Game/Bullet/Player/rin.png"));
	cImageResourceContainer::GetInstance()->GetElement(eImage_EnemyBullet)->SetPath(_T("./Data/Image/Game/Bullet/Enemy/normal.png"));

	cImageResourceContainer::GetInstance()->GetElement(eImage_GameBackGround)->Load();
	cImageResourceContainer::GetInstance()->GetElement(eImage_PlayerRin)->Load();
	cImageResourceContainer::GetInstance()->GetElement(eImage_PlayerBullet)->Load();
	cImageResourceContainer::GetInstance()->GetElement(eImage_EnemyBullet)->Load();

	mBulletOutCollider.GetColliderPointer()->resize(1);
	mBulletOutCollider.GetColliderPointer()->at(0).SetRange(GAME_SCREEN_WIDTH, GAME_SCREEN_HEIGHT);
	mBulletOutCollider.SetPosition(GAME_SCREEN_WIDTH / 2.0, GAME_SCREEN_HEIGHT / 2.0);

	mPlayer.at(0).SetInputPad(ppVirtualPad[0]);
	mPlayer.at(1).SetInputPad(ppVirtualPad[1]);
	for (auto &i : mPlayer) {
		i.SetBulletGenerateTarget(&mPlayerBullet);
	}

	mBackground.MoveToPoint(0.0, 1200.0, 90 * 60);

	mTimer.Initialize(0);
	mBombAnimeTimer.Initialize(0, (cImageResourceContainer::GetInstance()->GetElement(eImage_Bomb)->GetHandleNum() * 2 - 2) * 5, eCountMode_CountUp, true);
	mBossTimer.Initialize(120.0, 1000.0, eCountMode_CountDown);

	mTimer.Start();
	mBombAnimeTimer.Start();
	mBossTimer.Start();
}

void cMainGameScene::Finalize() {

}

void cMainGameScene::Update() {
	mTimer.Update();
	mBombAnimeTimer.Update();
	mBossTimer.Update();
	mBackground.Update();
	mBulletOutCollider.Update();

	if (mTimer.GetTime() == 60) {
		cEnemy tEnemy;
		tEnemy.SetPosition(240.0, 160.0);

		mEnemy.push_back(tEnemy);
	}

	for (auto &i : mPlayerBullet) {
		i.Update();
		if (!mBulletOutCollider.GetCollisionFlag(i)) {
			i.Erase();
		}
		else {
			for (auto &j : mEnemy) {
				if (j.GetCollisionFlag(i)) {
					i.Erase();
					mPlayer.at(0).AddScore(10 * mPlayer.at(0).GetScoreRate());
				}
			}
		}
	}
	for (auto i = mPlayerBullet.begin(); i != mPlayerBullet.end();) {
		if (!i->GetActiveFlag()) {
			i = mPlayerBullet.erase(i);
			continue;
		}
		i++;
	}

	for (auto &i : mEnemyBullet) {
		i.Update();
		if (!mBulletOutCollider.GetCollisionFlag(i)) {
			i.Erase();
		}
		
	}
	for (auto i = mEnemyBullet.begin(); i != mEnemyBullet.end();) {
		if (!i->GetActiveFlag()) {
			i = mEnemyBullet.erase(i);
			continue;
		}
		i++;
	}

	//for (auto &i : mPlayer) {
	//	i.Update();
	//}
	mPlayer.at(0).Update();

	for (auto &i : mEnemy) {
		i.SetBulletGenerateTarget(&mEnemyBullet);
		i.Update();
	}

	for (auto &i : mPlayer) {
		for (auto &j : mEnemyBullet) {
			if (i.GetCollisionFlag(j) && !i.GetInvincibleFlag()) {
				i.Damage();
			}
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
	for (auto &i : mPlayer) {
		if (i.GetPossessFlag()) {
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, static_cast<int>(255.0 * 40.0 / 100.0));
			DrawBox(0, 0, GAME_SCREEN_WIDTH, GAME_SCREEN_HEIGHT, GetColor(0x6F, 0xCC, 0xCE), TRUE);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
			break;
		}
	}

	// 敵
	for (auto &i : mEnemy) {
		i.Draw();
	}

	// 自機弾
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, static_cast<int>(255.0 * 60.0 / 100.0));
	for (auto &i : mPlayerBullet) {
		i.Draw();
	}
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);

	// 自機
	//for (auto &i : mPlayer) {
	//	i.Draw();
	//}
	mPlayer.at(0).Draw();

	// 敵弾
	for (auto &i : mEnemyBullet) {
		i.Draw();
	}

	// ボス体力ゲージ
	//DrawBox(12 + 5, 56 + 2, 480 - 12 - 5, 56 + 16 - 2, GetColor(0x52, 0xCC, 0x14), TRUE);
	//DrawGraph(12, 56, cImageResourceContainer::GetInstance()->GetElement(eImage_LifeGauge)->GetHandle(0), TRUE);
	//DrawGraph(480 - 12 - 16, 56, cImageResourceContainer::GetInstance()->GetElement(eImage_LifeGauge)->GetHandle(2), TRUE);
	//for (int i = 12 + 16; i < 480 - 12 - 16; i += 16) {
	//	DrawGraph(i, 56, cImageResourceContainer::GetInstance()->GetElement(eImage_LifeGauge)->GetHandle(1), TRUE);
	//}
	//mBossTimer.Draw(240, 110);

	// スコア
	// 1P
	DrawGraph(0, 0, cImageResourceContainer::GetInstance()->GetElement(eImage_ScoreBoard)->GetHandle(0), TRUE);
	DrawStringToHandle(16 + GetDrawStringWidthToHandle(_T("3999999999"), _tcsclen(_T("3999999999")), cFontContainer::GetInstance()->GetElement(eFont_GameFont)) - GetDrawStringWidthToHandle(tScore.at(0).c_str(), tScore.at(0).size(), cFontContainer::GetInstance()->GetElement(eFont_GameFont)), 24,
		tScore.at(0).c_str(), GetColor(0xFF, 0xFF, 0xFF), cFontContainer::GetInstance()->GetElement(eFont_GameFont));
	// 2P
	//if (mTimer.GetTime() % 60 < 30) {
		DrawStringToHandle(GAME_SCREEN_WIDTH * 7 / 9 - GetDrawStringWidthToHandle(_T("TRIAL VERSION"), _tcsclen(_T("TRIAL VERSION")), cFontContainer::GetInstance()->GetElement(eFont_GameFont)) / 2, 24,
			_T("TRIAL VERSION"), GetColor(0xFF, 0xFF, 0xFF), cFontContainer::GetInstance()->GetElement(eFont_GameFont));
	//}
	//DrawGraph(480 - 160, 0, cImageResourceContainer::GetInstance()->GetElement(eImage_ScoreBoard)->GetHandle(1), TRUE);
	//DrawStringToHandle(480 - 16 - GetDrawStringWidthToHandle(tScore.at(1).c_str(), tScore.at(1).size(), cFontContainer::GetInstance()->GetElement(eFont_GameFont)), 24,
	//	tScore.at(1).c_str(), GetColor(0xFF, 0xFF, 0xFF), cFontContainer::GetInstance()->GetElement(eFont_GameFont));

	// スコアレート
	// 1P
	DrawGraph(12 + cImageResourceContainer::GetInstance()->GetElement(eImage_RateNumber)->GetSizeX() * 0, 108, cImageResourceContainer::GetInstance()->GetElement(eImage_RateNumber)->GetHandle(10), TRUE);
	for (int i = 0; i < tScoreRateDigit.at(0); i++) {
		DrawGraph(12 + cImageResourceContainer::GetInstance()->GetElement(eImage_RateNumber)->GetSizeX() * (tScoreRateDigit.at(0) - i), 108, cImageResourceContainer::GetInstance()->GetElement(eImage_RateNumber)->GetHandle(tDispScoreRate.at(0) / static_cast<int>(pow(10, i)) % 10), TRUE);
	}
	// 2P
	//for (int i = 0; i <= tScoreRateDigit.at(1); i++) {
	//	if (i == tScoreRateDigit.at(1)) {
	//		DrawGraph(GAME_SCREEN_WIDTH - 12 + -cImageResourceContainer::GetInstance()->GetElement(eImage_RateNumber)->GetSizeX() * (i + 1), 108, cImageResourceContainer::GetInstance()->GetElement(eImage_RateNumber)->GetHandle(10), TRUE);
	//	}
	//	else {
	//		DrawGraph(GAME_SCREEN_WIDTH - 12 + -cImageResourceContainer::GetInstance()->GetElement(eImage_RateNumber)->GetSizeX() * (i + 1), 108, cImageResourceContainer::GetInstance()->GetElement(eImage_RateNumber)->GetHandle(tDispScoreRate.at(1) / static_cast<int>(pow(10, i)) % 10), TRUE);
	//	}
	//}

	// 憑依ゲージ
	// 1P
	DrawFormatStringToHandle(12, 108 + cImageResourceContainer::GetInstance()->GetElement(eImage_RateNumber)->GetSizeY() + 8, GetColor(0x5E, 0xED, 0xC7), cFontContainer::GetInstance()->GetElement(eFont_TimerFont), _T("%.1f%%"), floor(mPlayer.at(0).GetPossessGauge() * 10.0) / 10.0);

	// ライフ
	// 1P
	for (int i = 0; i < mPlayer.at(0).GetLife(); i++) {
		DrawGraph(12 + 24 * i, 80, cImageResourceContainer::GetInstance()->GetElement(eImage_Life)->GetHandle(), TRUE);
	}
	// 2P
	//for (int i = 0; i < mPlayer.at(1).GetLife(); i++) {
	//	DrawGraph(480 - 12 - 20 + -24 * i, 80, cImageResourceContainer::GetInstance()->GetElement(eImage_Life)->GetHandle(), TRUE);
	//}

	// ボム
	// 1P
	DrawGraph(12, 640 - 8 - 20 - 8 - 14, cImageResourceContainer::GetInstance()->GetElement(eImage_CaptionBomb)->GetHandle(), TRUE);
	for (int i = 0; i < mPlayer.at(0).GetBomb(); i++) {
		if (mTimer.GetTime() / 5 % 6 < 4) {
			DrawGraph(12 + 24 * i, 640 - 8 - 20, cImageResourceContainer::GetInstance()->GetElement(eImage_Bomb)->GetHandle(mTimer.GetTime() / 5 % 6), TRUE);
		}
		else {
			DrawGraph(12 + 24 * i, 640 - 8 - 20, cImageResourceContainer::GetInstance()->GetElement(eImage_Bomb)->GetHandle(6 - mTimer.GetTime() / 5 % 6), TRUE);
		}
	}
	// 2P
	//DrawGraph(480 - 12 - cImageResourceContainer::GetInstance()->GetElement(eImage_CaptionBomb)->GetSizeX(), 640 - 8 - 20 - 8 - 14, cImageResourceContainer::GetInstance()->GetElement(eImage_CaptionBomb)->GetHandle(), TRUE);
	//for (int i = 0; i < mPlayer.at(1).GetBomb(); i++) {
	//	if (mTimer.GetTime() / 5 % 6 < 4) {
	//		DrawGraph(480 - 12 - 20 + -24 * i, 640 - 8 - 20, cImageResourceContainer::GetInstance()->GetElement(eImage_Bomb)->GetHandle(mTimer.GetTime() / 5 % 6), TRUE);
	//	}
	//	else {
	//		DrawGraph(480 - 12 - 20 + -24 * i, 640 - 8 - 20, cImageResourceContainer::GetInstance()->GetElement(eImage_Bomb)->GetHandle(6 - mTimer.GetTime() / 5 % 6), TRUE);
	//	}
	//}

	//ppVirtualPad[0]->Draw();
#ifdef _DEBUG
	clsDx();
	printfDx(_T("Player Bullets: %d\n"), mPlayerBullet.size());
	printfDx(_T("Enemy Bullets: %d\n"), mEnemyBullet.size());
#endif
}