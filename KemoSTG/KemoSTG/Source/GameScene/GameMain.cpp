#include "../../Header/GameScene/GameMain.h"

cImageResource gGameBackground;	// ゲーム背景
cImageResourceContainer gGameUIImageContainer;	// ゲームUI
cSoundResource gGameBGM;	// ゲームBGM

cMainGameScene::cMainGameScene(iSceneChanger<eGameScene> *Changer) : cGameBaseScene(Changer) {
	
}

cMainGameScene::~cMainGameScene() {

}

void cMainGameScene::Initialize() {
	cGameManager::GetInstance()->GetPlayerPointer()->at(0).SetInputPad(ppVirtualPad[0]);
	cGameManager::GetInstance()->GetPlayerPointer()->at(1).SetInputPad(ppVirtualPad[1]);
	mBackground.GetMoveVectorPointer()->SetElement(0.0, 0.7);

	mFade.SetPosition(0.0, 0.0);

	mTimer.Initialize(0);
	mDelayTimer.Initialize(0, 1, eCountMode_CountUp, true);
	mBossTimer.Initialize(100.0, 1000.0, eCountMode_CountDown);

	mCharacterImage.at(0).SetPath(_T("./Data/Image/Game/Character/rin.png"));
	mCharacterImage.at(1).SetPath(_T("./Data/Image/Game/Character/kasumi.png"));
	for (auto &i : mCharacterImage) {
		i.Load();
	}

	gGameBackground.SetPath(_T("./Data/Image/Game/Background/1.png"));
	gGameBackground.Load();

	gGameBGM.SetPath(_T("./Data/Sound/Music/Game/1.wav"));
	gGameBGM.SetBufferNum(1);
	gGameBGM.Load();

	mTimer.Start();
	mDelayTimer.Start();
	mBombAnimeTimer.Start();
	mBossTimer.Start();

	// 会話データ
	mWordCount = 0;
	mSerif.push_back({ _T("―…はぁ…"), 0 });
	mSerif.push_back({ _T("もう10分はやってるのに…全然減らないや"), 0 });
	mSerif.push_back({ _T("助けてあげよっか？"), 1 });
	mSerif.push_back({ _T("！？　誰…？"), 0 });
	mSerif.push_back({ _T("とりあえず逃げよっか、手伝ってあげるよ"), 1 });
	mSerif.push_back({ _T("これを倒せばいいんだよね？\nえっと…おおかみさん、かな？"), 1 });
	mWordTimer.Initialize(6.0, 6.0, eCountMode_CountDown);
	mWordTimer.Start();

	cGameManager::GetInstance()->Initialize();
	cGameManager::GetInstance()->GetPlayerPointer()->at(0).Entry();
}

void cMainGameScene::Finalize() {
	gGameBGM.Finalize();
}

void cMainGameScene::Update() {
	mDelayTimer.Update();
			mBombAnimeTimer.Update();
			mBackground.Move();
			mFade.Update();

	if (CheckHandleASyncLoad(gGameBGM.GetHandle()) == FALSE && CheckSoundMem(gGameBGM.GetHandle()) == 0) {
		gGameBGM.SetVolume(static_cast<int>(cSystemConfig::GetInstance()->GetConfig().mBGMVolume * 255.0 / 100.0));
		PlaySoundMem(gGameBGM.GetHandle(), DX_PLAYTYPE_LOOP, FALSE);
	}

	if (mDelayTimer.GetTime() == 0) {
		if (mWordCount < mSerif.size()) {
			if (mWordTimer.GetTime() == 0) {
				mWordTimer.SetSecond(6.0);
				mWordCount++;
			}
			mWordTimer.Update();
			if (ppVirtualPad[0]->GetInputState(eButton_Shot) == 1) {
				mWordTimer.SetTime(0);
			}
		}
		else {
			mTimer.Update();
			mBossTimer.Update();
			//mBulletOutCollider.Update();

			// 敵登録テスト
			if (mTimer.GetTime() == 180) {
				sEnemyRegisterData tRegisterData;
				tRegisterData.mAppearanceX = GAME_SCREEN_WIDTH / 2 - 180;
				tRegisterData.mAppearanceY = GAME_SCREEN_HEIGHT / 5;
				tRegisterData.mType = eEnemy_Zako;
				tRegisterData.mMovePattern = 0;
				tRegisterData.mGeneratorPattern = 0;
				tRegisterData.mBulletPattern = 0;
				for (int i = 0; i < 5; i++) {
					cGameManager::GetInstance()->GetEnemyPointer()->push_back(cEnemy(tRegisterData));
					tRegisterData.mAppearanceX += 90;
				}
			}

			if (mTimer.GetTime() >= 180) {
				while (cGameManager::GetInstance()->GetEnemyPointer()->size() < 5) {
					sEnemyRegisterData tRegisterData;
					tRegisterData.mAppearanceX = GetRand(GAME_SCREEN_WIDTH);
					tRegisterData.mAppearanceY = GetRand(GAME_SCREEN_HEIGHT);
					tRegisterData.mType = eEnemy_Zako;
					tRegisterData.mMovePattern = 0;
					tRegisterData.mGeneratorPattern = 0;
					tRegisterData.mBulletPattern = 0;
					cGameManager::GetInstance()->GetEnemyPointer()->push_back(cEnemy(tRegisterData));
				}
			}

			cGameManager::GetInstance()->Update();

			if (cGameManager::GetInstance()->GetPlayerPointer()->at(0).GetLife() <= 0 && mFade.GetPositionX() == 0.0) {
				mFade.MoveToPoint(255.0, 0.0, 90);
			}

			if (mFade.GetPositionX() >= 255.0 || mBossTimer.GetTime() <= 0) {
				pSceneChanger->ChangeScene(eGameScene_NameEntry);
			}
		}
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

	tScore.at(0) = std::to_tstring(cGameManager::GetInstance()->GetPlayerPointer()->at(0).GetScore().mScore);
	tScore.at(1) = std::to_tstring(cGameManager::GetInstance()->GetPlayerPointer()->at(1).GetScore().mScore);

	tDispScoreRate.at(0) = cGameManager::GetInstance()->GetPlayerPointer()->at(0).GetScoreRate();
	tDispScoreRate.at(1) = cGameManager::GetInstance()->GetPlayerPointer()->at(1).GetScoreRate();

	for (auto &i : tDispScoreRate) {
		if (i > 999999) {
			i = 999999;
		}
	}

	tScoreRateDigit.at(0) = static_cast<int>(floor(log10(tDispScoreRate.at(0)))) + 1;
	tScoreRateDigit.at(1) = static_cast<int>(floor(log10(tDispScoreRate.at(1)))) + 1;

	for (int i = -1; i < 256; i++) {
		DrawGraphF(0.0f, static_cast<float>(mBackground.GetPositionY() - gGameBackground.GetSizeY() * i), gGameBackground.GetHandle(), FALSE);
	}

	cGameManager::GetInstance()->Draw();

	// ボス体力ゲージ
	//DrawBox(12 + 5, 56 + 2, 480 - 12 - 5, 56 + 16 - 2, GetColor(0x52, 0xCC, 0x14), TRUE);
	//DrawGraph(12, 56, gGameUIImageContainer.GetElement(eGameUI_LifeGauge)->GetHandle(0), TRUE);
	//DrawGraph(480 - 12 - 16, 56, gGameUIImageContainer.GetElement(eGameUI_LifeGauge)->GetHandle(2), TRUE);
	//for (int i = 12 + 16; i < 480 - 12 - 16; i += 16) {
	//	DrawGraph(i, 56, gGameUIImageContainer.GetElement(eGameUI_LifeGauge)->GetHandle(1), TRUE);
	//}
	mBossTimer.Draw(240, 110);

	// スコアレート
	// 1P
	if (cGameManager::GetInstance()->GetPlayerPointer()->at(0).GetAliveFlag()) {
		DrawGraph(12 + gGameUIImageContainer.GetElement(eGameUI_RateNumber)->GetSizeX() * 0, 108, gGameUIImageContainer.GetElement(eGameUI_RateNumber)->GetHandle(10), TRUE);
		for (int i = 0; i < tScoreRateDigit.at(0); i++) {
			DrawGraph(12 + gGameUIImageContainer.GetElement(eGameUI_RateNumber)->GetSizeX() * (tScoreRateDigit.at(0) - i), 108, gGameUIImageContainer.GetElement(eGameUI_RateNumber)->GetHandle(tDispScoreRate.at(0) / static_cast<int>(pow(10, i)) % 10), TRUE);
		}
	}
	// 2P
	if (cGameManager::GetInstance()->GetPlayerPointer()->at(1).GetAliveFlag()) {
		for (int i = 0; i <= tScoreRateDigit.at(1); i++) {
			if (i == tScoreRateDigit.at(1)) {
				DrawGraph(GAME_SCREEN_WIDTH - 12 + -gGameUIImageContainer.GetElement(eGameUI_RateNumber)->GetSizeX() * (i + 1), 108, gGameUIImageContainer.GetElement(eGameUI_RateNumber)->GetHandle(10), TRUE);
			}
			else {
				DrawGraph(GAME_SCREEN_WIDTH - 12 + -gGameUIImageContainer.GetElement(eGameUI_RateNumber)->GetSizeX() * (i + 1), 108, gGameUIImageContainer.GetElement(eGameUI_RateNumber)->GetHandle(tDispScoreRate.at(1) / static_cast<int>(pow(10, i)) % 10), TRUE);
			}
		}
	}

	// 憑依ゲージ
	// 1P
	if (cGameManager::GetInstance()->GetPlayerPointer()->at(0).GetAliveFlag()) {
		DrawFormatStringToHandle(12, 108 + gGameUIImageContainer.GetElement(eGameUI_RateNumber)->GetSizeY() + 8, GetColor(0x5E, 0xED, 0xC7), gTimerFontContainer.GetElement(eTimerFont_Big)->GetHandle(), _T("%d"), static_cast<int>(floor(cGameManager::GetInstance()->GetPlayerPointer()->at(0).GetPossessGauge())));
		DrawFormatStringToHandle(12 + GetDrawFormatStringWidthToHandle(gTimerFontContainer.GetElement(eTimerFont_Big)->GetHandle(), _T("%d"), static_cast<int>(floor(cGameManager::GetInstance()->GetPlayerPointer()->at(0).GetPossessGauge()))), 108 + gGameUIImageContainer.GetElement(eGameUI_RateNumber)->GetSizeY() + 8 + (gTimerFontContainer.GetElement(eTimerFont_Big)->GetSize() - gTimerFontContainer.GetElement(eTimerFont_Small)->GetSize()),
			GetColor(0x5E, 0xED, 0xC7), gTimerFontContainer.GetElement(eTimerFont_Small)->GetHandle(), _T(".%d%%"), static_cast<int>(cGameManager::GetInstance()->GetPlayerPointer()->at(0).GetPossessGauge() * 10.0) % 10);
	}
	// 2P
	if (cGameManager::GetInstance()->GetPlayerPointer()->at(1).GetAliveFlag()) {
		DrawFormatStringToHandle(GAME_SCREEN_WIDTH - 12 - GetDrawFormatStringWidthToHandle(gTimerFontContainer.GetElement(eTimerFont_Small)->GetHandle(), _T(".%d%%"), static_cast<int>(cGameManager::GetInstance()->GetPlayerPointer()->at(1).GetPossessGauge() * 10.0) % 10) - GetDrawFormatStringWidthToHandle(gTimerFontContainer.GetElement(eTimerFont_Big)->GetHandle(), _T("%d"), static_cast<int>(floor(cGameManager::GetInstance()->GetPlayerPointer()->at(1).GetPossessGauge()))), 108 + gGameUIImageContainer.GetElement(eGameUI_RateNumber)->GetSizeY() + 8, GetColor(0x5E, 0xED, 0xC7), gTimerFontContainer.GetElement(eTimerFont_Big)->GetHandle(), _T("%d"), static_cast<int>(floor(cGameManager::GetInstance()->GetPlayerPointer()->at(1).GetPossessGauge())));
		DrawFormatStringToHandle(GAME_SCREEN_WIDTH - 12 - GetDrawFormatStringWidthToHandle(gTimerFontContainer.GetElement(eTimerFont_Small)->GetHandle(), _T(".%d%%"), static_cast<int>(cGameManager::GetInstance()->GetPlayerPointer()->at(1).GetPossessGauge() * 10.0) % 10), 108 + gGameUIImageContainer.GetElement(eGameUI_RateNumber)->GetSizeY() + 8 + (gTimerFontContainer.GetElement(eTimerFont_Big)->GetSize() - gTimerFontContainer.GetElement(eTimerFont_Small)->GetSize()),
			GetColor(0x5E, 0xED, 0xC7), gTimerFontContainer.GetElement(eTimerFont_Small)->GetHandle(), _T(".%d%%"), static_cast<int>(cGameManager::GetInstance()->GetPlayerPointer()->at(1).GetPossessGauge() * 10.0) % 10);
	}

	// ライフ
	// 1P
	if (cGameManager::GetInstance()->GetPlayerPointer()->at(0).GetAliveFlag()) {
		for (int i = 0; i < cGameManager::GetInstance()->GetPlayerPointer()->at(0).GetLife(); i++) {
			DrawGraph(12 + 24 * i, 80, gGameUIImageContainer.GetElement(eGameUI_Life)->GetHandle(), TRUE);
		}
	}
	// 2P
	if (cGameManager::GetInstance()->GetPlayerPointer()->at(1).GetAliveFlag()) {
		for (int i = 0; i < cGameManager::GetInstance()->GetPlayerPointer()->at(1).GetLife(); i++) {
			DrawGraph(480 - 12 - 20 + -24 * i, 80, gGameUIImageContainer.GetElement(eGameUI_Life)->GetHandle(), TRUE);
		}
	}

	// キャラ表示領域
	if (mWordCount < mSerif.size()) {
		//DrawBox(0, GAME_SCREEN_HEIGHT - 540, 280, GAME_SCREEN_HEIGHT, GetColor(0xFF, 0xFF, 0xFF), FALSE);
		DrawGraph(0, GAME_SCREEN_HEIGHT - 540, mCharacterImage.at(mSerif.at(mWordCount).mChara).GetHandle(), TRUE);
	}

	// ボム
	// 1P
	if (cGameManager::GetInstance()->GetPlayerPointer()->at(0).GetAliveFlag()) {
		DrawGraph(12, 640 - 8 - 20 - 8 - 14, gGameUIImageContainer.GetElement(eGameUI_CaptionBomb)->GetHandle(), TRUE);
		for (int i = 0; i < cGameManager::GetInstance()->GetPlayerPointer()->at(0).GetBomb(); i++) {
			if (mTimer.GetTime() / 5 % 6 < 4) {
				DrawGraph(12 + 24 * i, 640 - 8 - 20, gGameUIImageContainer.GetElement(eGameUI_Bomb)->GetHandle(mTimer.GetTime() / 5 % 6), TRUE);
			}
			else {
				DrawGraph(12 + 24 * i, 640 - 8 - 20, gGameUIImageContainer.GetElement(eGameUI_Bomb)->GetHandle(6 - mTimer.GetTime() / 5 % 6), TRUE);
			}
		}
	}
	// 2P
	if (cGameManager::GetInstance()->GetPlayerPointer()->at(1).GetAliveFlag()) {
		DrawGraph(480 - 12 - gGameUIImageContainer.GetElement(eGameUI_CaptionBomb)->GetSizeX(), 640 - 8 - 20 - 8 - 14, gGameUIImageContainer.GetElement(eGameUI_CaptionBomb)->GetHandle(), TRUE);
		for (int i = 0; i < cGameManager::GetInstance()->GetPlayerPointer()->at(1).GetBomb(); i++) {
			if (mTimer.GetTime() / 5 % 6 < 4) {
				DrawGraph(480 - 12 - 20 + -24 * i, 640 - 8 - 20, gGameUIImageContainer.GetElement(eGameUI_Bomb)->GetHandle(mTimer.GetTime() / 5 % 6), TRUE);
			}
			else {
				DrawGraph(480 - 12 - 20 + -24 * i, 640 - 8 - 20, gGameUIImageContainer.GetElement(eGameUI_Bomb)->GetHandle(6 - mTimer.GetTime() / 5 % 6), TRUE);
			}
		}
	}

	// 台詞
	if (mWordCount < mSerif.size()) {
		DrawGraph(16, GAME_SCREEN_HEIGHT - 200, gGameUIImageContainer.GetElement(eGameUI_WordBackground)->GetHandle(), TRUE);
		switch (mSerif.at(mWordCount).mChara) {
		case 0:
			DrawStringToHandle(94 + 17 - GetDrawStringWidthToHandle(_T("神谷　倫"), _tcslen(_T("神谷　倫")), gGameFontContainer.GetElement(eGameFont_Word)->GetHandle()) / 2, GAME_SCREEN_HEIGHT - 191, _T("神谷　倫"), GetColor(0x3F, 0x3F, 0x3F), gGameFontContainer.GetElement(eGameFont_Word)->GetHandle());
			DrawStringToHandle(94 + 16 - GetDrawStringWidthToHandle(_T("神谷　倫"), _tcslen(_T("神谷　倫")), gGameFontContainer.GetElement(eGameFont_Word)->GetHandle()) / 2, GAME_SCREEN_HEIGHT - 192, _T("神谷　倫"), GetColor(0xFF, 0xFF, 0xFF), gGameFontContainer.GetElement(eGameFont_Word)->GetHandle());
			break;
		case 1:
			DrawStringToHandle(94 + 17 - GetDrawStringWidthToHandle(_T("霞"), _tcslen(_T("霞")), gGameFontContainer.GetElement(eGameFont_Word)->GetHandle()) / 2, GAME_SCREEN_HEIGHT - 191, _T("霞"), GetColor(0x3F, 0x3F, 0x3F), gGameFontContainer.GetElement(eGameFont_Word)->GetHandle());
			DrawStringToHandle(94 + 16 - GetDrawStringWidthToHandle(_T("霞"), _tcslen(_T("霞")), gGameFontContainer.GetElement(eGameFont_Word)->GetHandle()) / 2, GAME_SCREEN_HEIGHT - 192, _T("霞"), GetColor(0xFF, 0xFF, 0xFF), gGameFontContainer.GetElement(eGameFont_Word)->GetHandle());
			break;
		}
		DrawStringToHandle(31, GAME_SCREEN_HEIGHT - 151, mSerif.at(mWordCount).mString.c_str(), GetColor(0x3F, 0x3F, 0x3F), gGameFontContainer.GetElement(eGameFont_Word)->GetHandle());
		DrawStringToHandle(30, GAME_SCREEN_HEIGHT - 152, mSerif.at(mWordCount).mString.c_str(), GetColor(0xFF, 0xFF, 0xFF), gGameFontContainer.GetElement(eGameFont_Word)->GetHandle());
	}

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, mFade.GetPositionX());
	DrawBox(0, 0, GAME_SCREEN_WIDTH, GAME_SCREEN_HEIGHT, GetColor(0x00, 0x00, 0x00), TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);

	if (cGameManager::GetInstance()->GetPlayerPointer()->at(0).GetLife() <= 0) {
		DrawGraph(GAME_SCREEN_WIDTH / 2 - gGameUIImageContainer.GetElement(eGameUI_GameOver)->GetSizeX() / 2, GAME_SCREEN_HEIGHT * 2 / 5, gGameUIImageContainer.GetElement(eGameUI_GameOver)->GetHandle(), TRUE);
	}

	// スコア
	// 1P
	if (cGameManager::GetInstance()->GetPlayerPointer()->at(0).GetAliveFlag()) {
		DrawGraph(0, 0, gGameUIImageContainer.GetElement(eGameUI_ScoreBoard)->GetHandle(0), TRUE);
		DrawStringToHandle(16 + GetDrawStringWidthToHandle(_T("3999999999"), _tcsclen(_T("3999999999")), gGameFontContainer.GetElement(eGameFont_Interface)->GetHandle()) - GetDrawStringWidthToHandle(tScore.at(0).c_str(), tScore.at(0).size(), gGameFontContainer.GetElement(eGameFont_Interface)->GetHandle()), 24,
			tScore.at(0).c_str(), GetColor(0xFF, 0xFF, 0xFF), gGameFontContainer.GetElement(eGameFont_Interface)->GetHandle());
	}
	else {
		DrawStringToHandle(GAME_SCREEN_WIDTH * 2 / 9 - GetDrawStringWidthToHandle(tInformation.at(0).c_str(), tInformation.at(0).size(), gGameFontContainer.GetElement(eGameFont_Interface)->GetHandle()) / 2, 24,
			tInformation.at(0).c_str(), GetColor(0xFF, 0xFF, 0xFF), gGameFontContainer.GetElement(eGameFont_Interface)->GetHandle());
	}
	// 2P
	if (cGameManager::GetInstance()->GetPlayerPointer()->at(1).GetAliveFlag()) {
		//DrawGraph(480 - 160, 0, gGameUIImageContainer.GetElement(eGameUI_ScoreBoard)->GetHandle(1), TRUE);
		DrawStringToHandle(480 - 16 - GetDrawStringWidthToHandle(tScore.at(1).c_str(), tScore.at(1).size(), gGameFontContainer.GetElement(eGameFont_Interface)->GetHandle()), 24,
			tScore.at(1).c_str(), GetColor(0xFF, 0xFF, 0xFF), gGameFontContainer.GetElement(eGameFont_Interface)->GetHandle());
	}
	else {
		//if (mTimer.GetTime() % 60 < 30) {
		DrawStringToHandle(GAME_SCREEN_WIDTH * 7 / 9 - GetDrawStringWidthToHandle(tInformation.at(1).c_str(), tInformation.at(1).size(), gGameFontContainer.GetElement(eGameFont_Interface)->GetHandle()) / 2, 24,
			tInformation.at(1).c_str(), GetColor(0xFF, 0xFF, 0xFF), gGameFontContainer.GetElement(eGameFont_Interface)->GetHandle());
		//}
	}

	//ppVirtualPad[0]->Draw();
#ifdef _DEBUG
	clsDx();
	printfDx(_T("Player Bullets: %d\n"), cGameManager::GetInstance()->GetPlayerBulletPointer()->size());
	printfDx(_T("Enemy Bullets: %d\n"), cGameManager::GetInstance()->GetEnemyBulletPointer()->size());
	printfDx(_T("Effects: %d\n"), cGameManager::GetInstance()->GetEffectPointer()->size());
#endif
}