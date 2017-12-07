#include "../../Header/GameScene/GameMain.h"

cSoundResource gGameBGM;
cImageResourceContainer gGameUIImageContainer;

cMainGameScene::cMainGameScene(iSceneChanger<eGameScene> *Changer) : cGameBaseScene(Changer) {

}

cMainGameScene::~cMainGameScene() {

}

void cMainGameScene::Initialize() {
	mBulletOutCollider.GetColliderPointer()->resize(1);
	mBulletOutCollider.GetColliderPointer()->at(0).SetRange(GAME_SCREEN_WIDTH, GAME_SCREEN_HEIGHT);
	mBulletOutCollider.SetPosition(GAME_SCREEN_WIDTH / 2.0, GAME_SCREEN_HEIGHT / 2.0);

	mPlayer.at(0).SetInputPad(ppVirtualPad[0]);
	mPlayer.at(1).SetInputPad(ppVirtualPad[1]);
	for (auto &i : mPlayer) {
		i.SetBulletGenerateTarget(&mPlayerBullet);
	}

	mBackground.GetMoveVectorPointer()->SetElement(0.0, 0.7);

	mFade.SetPosition(0.0, 0.0);

	mTimer.Initialize(0);
	mBossTimer.Initialize(120.0, 1000.0, eCountMode_CountDown);

	gGameBGM.SetPath(_T("./Data/Sound/Music/bgm_test.wav"));
	gGameBGM.SetBufferNum(1);
	gGameBGM.Load();

	mTimer.Start();
	mBombAnimeTimer.Start();
	mBossTimer.Start();

	mPlayer.at(0).Entry();
}

void cMainGameScene::Finalize() {
	mEnemy.clear();
	mPlayerBullet.clear();
	mEnemyBullet.clear();
	gGameBGM.Finalize();
}

void cMainGameScene::Update() {
	mTimer.Update();
	mBombAnimeTimer.Update();
	mBossTimer.Update();
	mBackground.Move();
	mBulletOutCollider.Update();
	mFade.Update();

	if (CheckHandleASyncLoad(gGameBGM.GetHandle()) == FALSE && CheckSoundMem(gGameBGM.GetHandle()) == 0) {
		gGameBGM.SetVolume(static_cast<int>(cSystemConfig::GetInstance()->GetConfig().mBGMVolume * 255.0 / 100.0));
		PlaySoundMem(gGameBGM.GetHandle(), DX_PLAYTYPE_LOOP, FALSE);
	}

	if (mTimer.GetTime() == 120) {
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
					//j.Damage(i.GetPower());
					i.Erase();
					if (mPlayer.at(0).GetPossessFlag()) {
						mPlayer.at(0).AddScoreRate(1);
					}
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

	for (auto &i : mPlayer) {
		if (i.GetAliveFlag()) {
			i.Update();
		}
	}

	if (mTimer.GetTime() >= 60 * 10 && mTimer.GetTime() % (60 * 3) == 0) {
		for (auto &i : mEnemy) {
			i.MoveToPoint(GetRand(GAME_SCREEN_WIDTH), GetRand(GAME_SCREEN_HEIGHT), 120, eEasing_Quad, eEasingFunction_InOut);
		}
	}

	for (auto &i : mEnemy) {
		i.SetBulletGenerateTarget(&mEnemyBullet);
		i.Update();
	}
	for (auto i = mEnemy.begin(); i != mEnemy.end();) {
		if (!i->GetAliveFlag()) {
			i = mEnemy.erase(i);
			continue;
		}
		i++;
	}

	for (auto &i : mPlayer) {
		for (auto &j : mEnemyBullet) {
			if (i.GetCollisionFlag(j) && !i.GetInvincibleFlag()) {
				i.Damage();
			}
		}
	}

	if (mPlayer.at(0).GetLife() <= 0 && mFade.GetPositionX() == 0.0) {
		mFade.MoveToPoint(255.0, 0.0, 90);
	}

	if (mFade.GetPositionX() >= 255.0) {
		pSceneChanger->ChangeScene(eGameScene_Logo);
	}
}

void cMainGameScene::Draw() {
	std::array<std::tstring, 2> tInformation;
	std::array<std::tstring, 2> tScore;
	std::array<unsigned int, 2> tDispScoreRate;	// 表示用スコアレート
	std::array<int, 2> tScoreRateDigit;	// スコアレート桁数
	std::array<std::tstring, 2> tDispGauge; // 表示用残りゲージ

	tInformation.at(0) = _T("GAME OVER");
	tInformation.at(1) = _T("TRIAL VERSION");

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

	for (int i = -1; i < 256; i++) {
		//DrawGraphF(0.0f, static_cast<float>(mBackground.GetPositionY() - gGameUIImageContainer.GetElement(eGameUI_GameBackGround)->GetSizeY() * i), gGameUIImageContainer.GetElement(eGameUI_GameBackGround)->GetHandle(), FALSE);
	}
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
	for (auto &i : mPlayer) {
		if (i.GetAliveFlag()) {
			i.Draw();
		}
	}

	// 敵弾
	for (auto &i : mEnemyBullet) {
		i.Draw();
	}

	// ボス体力ゲージ
	DrawBox(12 + 5, 56 + 2, 480 - 12 - 5, 56 + 16 - 2, GetColor(0x52, 0xCC, 0x14), TRUE);
	DrawGraph(12, 56, gGameUIImageContainer.GetElement(eGameUI_LifeGauge)->GetHandle(0), TRUE);
	DrawGraph(480 - 12 - 16, 56, gGameUIImageContainer.GetElement(eGameUI_LifeGauge)->GetHandle(2), TRUE);
	for (int i = 12 + 16; i < 480 - 12 - 16; i += 16) {
		DrawGraph(i, 56, gGameUIImageContainer.GetElement(eGameUI_LifeGauge)->GetHandle(1), TRUE);
	}
	mBossTimer.Draw(240, 110);

	// スコアレート
	// 1P
	if (mPlayer.at(0).GetAliveFlag()) {
		DrawGraph(12 + gGameUIImageContainer.GetElement(eGameUI_RateNumber)->GetSizeX() * 0, 108, gGameUIImageContainer.GetElement(eGameUI_RateNumber)->GetHandle(10), TRUE);
		for (int i = 0; i < tScoreRateDigit.at(0); i++) {
			DrawGraph(12 + gGameUIImageContainer.GetElement(eGameUI_RateNumber)->GetSizeX() * (tScoreRateDigit.at(0) - i), 108, gGameUIImageContainer.GetElement(eGameUI_RateNumber)->GetHandle(tDispScoreRate.at(0) / static_cast<int>(pow(10, i)) % 10), TRUE);
		}
	}
	// 2P
	if (mPlayer.at(1).GetAliveFlag()) {
		for (int i = 0; i <= tScoreRateDigit.at(1); i++) {
			if (i == tScoreRateDigit.at(1)) {
				//DrawGraph(GAME_SCREEN_WIDTH - 12 + -gGameUIImageContainer.GetElement(eGameUI_RateNumber)->GetSizeX() * (i + 1), 108, gGameUIImageContainer.GetElement(eGameUI_RateNumber)->GetHandle(10), TRUE);
			}
			else {
				//DrawGraph(GAME_SCREEN_WIDTH - 12 + -gGameUIImageContainer.GetElement(eGameUI_RateNumber)->GetSizeX() * (i + 1), 108, gGameUIImageContainer.GetElement(eGameUI_RateNumber)->GetHandle(tDispScoreRate.at(1) / static_cast<int>(pow(10, i)) % 10), TRUE);
			}
		}
	}

	// 憑依ゲージ
	// 1P
	if (mPlayer.at(0).GetAliveFlag()) {
		DrawFormatStringToHandle(12, 108 + gGameUIImageContainer.GetElement(eGameUI_RateNumber)->GetSizeY() + 8, GetColor(0x5E, 0xED, 0xC7), cFontContainer::GetInstance()->GetElement(eFont_TimerFont), _T("%.1f%%"), floor(mPlayer.at(0).GetPossessGauge() * 10.0) / 10.0);
	}

	// ライフ
	// 1P
	if (mPlayer.at(0).GetAliveFlag()) {
		for (int i = 0; i < mPlayer.at(0).GetLife(); i++) {
			DrawGraph(12 + 24 * i, 80, gGameUIImageContainer.GetElement(eGameUI_Life)->GetHandle(), TRUE);
		}
	}
	// 2P
	if (mPlayer.at(1).GetAliveFlag()) {
		for (int i = 0; i < mPlayer.at(1).GetLife(); i++) {
			//DrawGraph(480 - 12 - 20 + -24 * i, 80, gGameUIImageContainer.GetElement(eGameUI_Life)->GetHandle(), TRUE);
		}
	}

	// ボム
	// 1P
	if (mPlayer.at(0).GetAliveFlag()) {
		DrawGraph(12, 640 - 8 - 20 - 8 - 14, gGameUIImageContainer.GetElement(eGameUI_CaptionBomb)->GetHandle(), TRUE);
		for (int i = 0; i < mPlayer.at(0).GetBomb(); i++) {
			if (mTimer.GetTime() / 5 % 6 < 4) {
				DrawGraph(12 + 24 * i, 640 - 8 - 20, gGameUIImageContainer.GetElement(eGameUI_Bomb)->GetHandle(mTimer.GetTime() / 5 % 6), TRUE);
			}
			else {
				DrawGraph(12 + 24 * i, 640 - 8 - 20, gGameUIImageContainer.GetElement(eGameUI_Bomb)->GetHandle(6 - mTimer.GetTime() / 5 % 6), TRUE);
			}
		}
	}
	// 2P
	if (mPlayer.at(1).GetAliveFlag()) {
		//DrawGraph(480 - 12 - gGameUIImageContainer.GetElement(eGameUI_CaptionBomb)->GetSizeX(), 640 - 8 - 20 - 8 - 14, gGameUIImageContainer.GetElement(eGameUI_CaptionBomb)->GetHandle(), TRUE);
		//for (int i = 0; i < mPlayer.at(1).GetBomb(); i++) {
		//	if (mTimer.GetTime() / 5 % 6 < 4) {
		//		DrawGraph(480 - 12 - 20 + -24 * i, 640 - 8 - 20, gGameUIImageContainer.GetElement(eGameUI_Bomb)->GetHandle(mTimer.GetTime() / 5 % 6), TRUE);
		//	}
		//	else {
		//		DrawGraph(480 - 12 - 20 + -24 * i, 640 - 8 - 20, gGameUIImageContainer.GetElement(eGameUI_Bomb)->GetHandle(6 - mTimer.GetTime() / 5 % 6), TRUE);
		//	}
		//}
	}

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, mFade.GetPositionX());
	DrawBox(0, 0, GAME_SCREEN_WIDTH, GAME_SCREEN_HEIGHT, GetColor(0x00, 0x00, 0x00), TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);

	if (mPlayer.at(0).GetLife() <= 0) {
		DrawGraph(GAME_SCREEN_WIDTH / 2 - gGameUIImageContainer.GetElement(eGameUI_GameOver)->GetSizeX() / 2, GAME_SCREEN_HEIGHT * 2 / 5, gGameUIImageContainer.GetElement(eGameUI_GameOver)->GetHandle(), TRUE);
	}

	// スコア
	// 1P
	if (mPlayer.at(0).GetAliveFlag()) {
		DrawGraph(0, 0, gGameUIImageContainer.GetElement(eGameUI_ScoreBoard)->GetHandle(0), TRUE);
		DrawStringToHandle(16 + GetDrawStringWidthToHandle(_T("3999999999"), _tcsclen(_T("3999999999")), cFontContainer::GetInstance()->GetElement(eFont_GameFont)) - GetDrawStringWidthToHandle(tScore.at(0).c_str(), tScore.at(0).size(), cFontContainer::GetInstance()->GetElement(eFont_GameFont)), 24,
			tScore.at(0).c_str(), GetColor(0xFF, 0xFF, 0xFF), cFontContainer::GetInstance()->GetElement(eFont_GameFont));
	}
	else {
		DrawStringToHandle(GAME_SCREEN_WIDTH * 2 / 9 - GetDrawStringWidthToHandle(tInformation.at(0).c_str(), tInformation.at(0).size(), cFontContainer::GetInstance()->GetElement(eFont_GameFont)) / 2, 24,
			tInformation.at(0).c_str(), GetColor(0xFF, 0xFF, 0xFF), cFontContainer::GetInstance()->GetElement(eFont_GameFont));
	}
	// 2P
	if (mPlayer.at(1).GetAliveFlag()) {
		//DrawGraph(480 - 160, 0, gGameUIImageContainer.GetElement(eGameUI_ScoreBoard)->GetHandle(1), TRUE);
		DrawStringToHandle(480 - 16 - GetDrawStringWidthToHandle(tScore.at(1).c_str(), tScore.at(1).size(), cFontContainer::GetInstance()->GetElement(eFont_GameFont)), 24,
			tScore.at(1).c_str(), GetColor(0xFF, 0xFF, 0xFF), cFontContainer::GetInstance()->GetElement(eFont_GameFont));
	}
	else {
		//if (mTimer.GetTime() % 60 < 30) {
		DrawStringToHandle(GAME_SCREEN_WIDTH * 7 / 9 - GetDrawStringWidthToHandle(tInformation.at(1).c_str(), tInformation.at(1).size(), cFontContainer::GetInstance()->GetElement(eFont_GameFont)) / 2, 24,
			tInformation.at(1).c_str(), GetColor(0xFF, 0xFF, 0xFF), cFontContainer::GetInstance()->GetElement(eFont_GameFont));
		//}
	}

	//ppVirtualPad[0]->Draw();
#ifdef _DEBUG
	clsDx();
	printfDx(_T("Player Bullets: %d\n"), mPlayerBullet.size());
	printfDx(_T("Enemy Bullets: %d\n"), mEnemyBullet.size());
#endif
}