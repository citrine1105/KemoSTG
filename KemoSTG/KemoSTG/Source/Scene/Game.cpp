#include "../../Header/Scene/Game.h"
#include "../../Header/GameScene/GameLogo.h"
#include "../../Header/GameScene/GameTitle.h"
#include "../../Header/GameScene/GameMain.h"
#include "../../Header/Player.h"

cFontContainer gGameFontContainer;

cGameScene::cGameScene(iSceneChanger<eScene> *Changer) : cScene(Changer) {
	
}

cGameScene::~cGameScene() {
	
}

void cGameScene::Initialize() {
	mGameScreen = MakeScreen(GAME_SCREEN_WIDTH, GAME_SCREEN_HEIGHT);
	mGame.Initialize();
	mGame.SetVirtualPad(mVirtualPad);

	mFade.SetPosition(255.0, 0.0);

	mBackgroundImage.SetPath(_T("./Data/Image/Game/Background/back.png"));

	gLogoImageContainer.Initialize(eLogo_TotalNum);
	gGameTitleImageContainer.Initialize(eGameTitle_TotalNum);
	gGameUIImageContainer.Initialize(eGameUI_TotalNum);
	gPlayerImageContainer.Initialize(ePlayer_TotalNum);
	gPlayerBulletImageContainer.Initialize(ePlayer_TotalNum);
	gEnemyImageContainer.Initialize(eEnemy_TotalNum);
	gEnemyBulletImageContainer.Initialize(eBullet_TotalNum);
	gEffectImageContainer.Initialize(eEffect_TotalNum);

	gPlayerShotSoundContainer.Initialize(ePlayer_TotalNum);
	gBombSoundContainer.Initialize(ePlayer_TotalNum);

	gGameFontContainer.Initialize(eGameFont_TotalNum);
	gTimerFontContainer.Initialize(eTimerFont_TotalNum);

	// アトラクトロゴ画像
	gLogoImageContainer.GetElement(eLogo_AM)->SetPath(_T("./Data/Image/Game/Logo/am.png"));
	gLogoImageContainer.GetElement(eLogo_CLab)->SetPath(_T("./Data/Image/Game/Logo/clab.png"));

	// タイトルロゴ画像
	gGameTitleImageContainer.GetElement(eGameTitle_Logo)->SetPath(_T("./Data/Image/Game/Title/title.png"));

	// UI画像
	gGameUIImageContainer.GetElement(eGameUI_Life)->SetPath(_T("./Data/Image/Game/life.png"));
	gGameUIImageContainer.GetElement(eGameUI_Bomb)->SetPath(_T("./Data/Image/Game/bomb.png"));
	gGameUIImageContainer.GetElement(eGameUI_Bomb)->SetDivisionSize(4, 4, 1, 20, 20);
	gGameUIImageContainer.GetElement(eGameUI_ScoreBoard)->SetPath(_T("./Data/Image/Game/score_board.png"));
	gGameUIImageContainer.GetElement(eGameUI_ScoreBoard)->SetDivisionSize(2, 2, 1, 160, 56);
	gGameUIImageContainer.GetElement(eGameUI_RateNumber)->SetPath(_T("./Data/Image/Game/rate_num.png"));
	gGameUIImageContainer.GetElement(eGameUI_RateNumber)->SetDivisionSize(11, 11, 1, 24, 36);
	gGameUIImageContainer.GetElement(eGameUI_LifeGauge)->SetPath(_T("./Data/Image/Game/gauge.png"));
	gGameUIImageContainer.GetElement(eGameUI_LifeGauge)->SetDivisionSize(4, 4, 1, 16, 16);
	gGameUIImageContainer.GetElement(eGameUI_WordBackground)->SetPath(_T("./Data/Image/Game/wordback.png"));
	gGameUIImageContainer.GetElement(eGameUI_CaptionBomb)->SetPath(_T("./Data/Image/Game/Caption/bomb.png"));
	gGameUIImageContainer.GetElement(eGameUI_CaptionTime)->SetPath(_T("./Data/Image/Game/Caption/time.png"));
	gGameUIImageContainer.GetElement(eGameUI_GameOver)->SetPath(_T("./Data/Image/Game/gameover.png"));

	// 自機画像
	gPlayerImageContainer.GetElement(ePlayer_Rin)->SetPath(_T("./Data/Image/Game/Player/rin.png"));
	gPlayerImageContainer.GetElement(ePlayer_Kakeru)->SetPath(_T("./Data/Image/Game/Player/kakeru.png"));
	gPlayerImageContainer.GetElement(ePlayer_3rd)->SetPath(_T("./Data/Image/Game/Player/3.png"));

	// 自機弾画像
	gPlayerBulletImageContainer.GetElement(ePlayer_Rin)->SetPath(_T("./Data/Image/Game/Bullet/Player/rin.png"));
	gPlayerBulletImageContainer.GetElement(ePlayer_Kakeru)->SetPath(_T("./Data/Image/Game/Bullet/Player/kakeru.png"));
	gPlayerBulletImageContainer.GetElement(ePlayer_3rd)->SetPath(_T("./Data/Image/Game/Bullet/Player/3rd.png"));

	// 敵画像
	gEnemyImageContainer.GetElement(eEnemy_Zako)->SetPath(_T("./Data/Image/Game/Enemy/zako1.png"));

	// 敵弾画像
	gEnemyBulletImageContainer.GetElement(eBullet_Normal)->SetPath(_T("./Data/Image/Game/Bullet/Enemy/normal.png"));
	gEnemyBulletImageContainer.GetElement(eBullet_Arrow)->SetPath(_T("./Data/Image/Game/Bullet/Enemy/arrow.png"));

	gEffectImageContainer.GetElement(eEffect_Bomb)->SetPath(_T("./Data/Image/Game/Effect/bomb.png"));
	gEffectImageContainer.GetElement(eEffect_Bomb)->SetDivisionSize(4, 4, 1, 64, 64);

	// プレイヤーショット音
	gPlayerShotSoundContainer.GetElement(ePlayer_Rin)->SetPath(_T("./Data/Sound/Effect/Game/shot.wav"));
	gPlayerShotSoundContainer.GetElement(ePlayer_Kakeru)->SetPath(_T("./Data/Sound/Effect/Game/shot.wav"));
	gPlayerShotSoundContainer.GetElement(ePlayer_3rd)->SetPath(_T("./Data/Sound/Effect/Game/shot.wav"));
	for (int i = ePlayer_Rin; i < ePlayer_TotalNum; i++) {
		gPlayerShotSoundContainer.GetElement(i)->SetBufferNum(1);
	}

	// 憑依音
	gPossessSound.SetPath(_T("./Data/Sound/Effect/Game/possess.wav"));
	gPossessSound.SetBufferNum(1);

	// ボム発射音
	gBombSoundContainer.GetElement(ePlayer_Rin)->SetPath(_T("./Data/Sound/Effect/Game/bomb.wav"));
	for (int i = 0; i < ePlayer_TotalNum; i++) {
		gBombSoundContainer.GetElement(i)->SetBufferNum(1);
	}

	gGameFontContainer.GetElement(eGameFont_Interface)->SetProperty(_T("Palatino Linotype"), 18, 0, DX_FONTTYPE_ANTIALIASING_EDGE_4X4);
	std::tstring tPath;
	tPath = _T("./Data/Font/");
	tPath += _T("ja");	// TODO: ロケールIDを取得するクラスを作成
	tPath += _T("/word.dft");
	gGameFontContainer.GetElement(eGameFont_Word)->SetPath(tPath.c_str());
	//gGameFontContainer.GetElement(eGameFont_Word)->SetProperty(_T("Palatino Linotype"), 20, 0, DX_FONTTYPE_ANTIALIASING_EDGE_4X4);
	gGameFontContainer.GetElement(eGameFont_Word)->SetEdgeThickness(0);

	gTimerFontContainer.GetElement(eTimerFont_Big)->SetProperty(_T("Palatino Linotype"), 26, 0, DX_FONTTYPE_ANTIALIASING_EDGE_4X4);
	gTimerFontContainer.GetElement(eTimerFont_Small)->SetProperty(_T("Palatino Linotype"), 18, 0, DX_FONTTYPE_ANTIALIASING_EDGE_4X4);

	mBackgroundImage.Load();
	gLogoImageContainer.Load();
	gGameTitleImageContainer.Load();
	gGameUIImageContainer.Load();
	gPlayerImageContainer.Load();
	gPlayerBulletImageContainer.Load();
	gEnemyImageContainer.Load();
	gEnemyBulletImageContainer.Load();
	gEffectImageContainer.Load();

	gPlayerShotSoundContainer.Load();
	gPossessSound.Load();
	gBombSoundContainer.Load();

	gGameFontContainer.Load();
	gTimerFontContainer.Load();
}

void cGameScene::Finalize() {
	DeleteGraph(mGameScreen);
	mGame.Finalize();

	mBackgroundImage.Finalize();
	gLogoImageContainer.Finalize();
	gGameTitleImageContainer.Finalize();
	gGameUIImageContainer.Finalize();
	gPlayerImageContainer.Finalize();
	gPlayerBulletImageContainer.Finalize();
	gEnemyImageContainer.Finalize();
	gEnemyBulletImageContainer.Finalize();

	gPlayerShotSoundContainer.Finalize();
}

void cGameScene::Update() {
	mFade.Update();

	cScene::Update();
	// ロード完了直後のみ呼ばれる処理
	if (GetASyncLoadNum() == 0 && mFade.GetPositionX() >= 255.0) {
		gPlayerShotSoundContainer.SetVolume(static_cast<int>(cSystemConfig::GetInstance()->GetConfig().mSEVolume * 255.0 / 100.0));
		gPossessSound.SetVolume(static_cast<int>(cSystemConfig::GetInstance()->GetConfig().mSEVolume * 255.0 / 100.0));
		gBombSoundContainer.SetVolume(static_cast<int>(cSystemConfig::GetInstance()->GetConfig().mSEVolume * 255.0 / 100.0));
		mFade.MoveToPoint(0.0, 0.0, 30);
	}

	if (mGame.GetNowScene() == eGameScene_Game && !mGame.GetPauseFlag() && GetWindowActiveFlag() == FALSE) {
		mGame.Pause();
	}
	if (mGame.GetNowScene() == eGameScene_Game && mVirtualPad[0].GetInputState(eButton_Pause) == 1) {
		mGame.Pause();
	}

	if (mFade.GetPositionX() <= 0.0) {
		mGame.Update();
	}
}

void cGameScene::Draw() {
	SetDrawScreen(mInterfaceScreen);
	ClearDrawScreen();
	SetDrawScreen(DX_SCREEN_BACK);

	DrawRotaGraph(DISPLAY_WIDTH / 2, DISPLAY_HEIGHT / 2, DISPLAY_LONG / 3840.0, 0.0, mBackgroundImage.GetHandle(), FALSE);

	if (GetASyncLoadNum() != 0) {
		SetDrawScreen(mInterfaceScreen);
		DrawStringToHandle(DISPLAY_SHORT - GetDrawStringWidthToHandle(_T("Loading"), _tcslen(_T("Loading")), gSystemFont.GetElement(eSystemFont_UIFont)->GetHandle()) - UPSCALE(12), DISPLAY_SHORT - gSystemFont.GetElement(eSystemFont_UIFont)->GetSize() - UPSCALE(8), _T("Loading"), GetColor(0xFF, 0xFF, 0xFF), gSystemFont.GetElement(eSystemFont_UIFont)->GetHandle());
		SetDrawScreen(DX_SCREEN_BACK);
	}

	if (CheckHandleASyncLoad(mGameScreen) == FALSE) {
		if (mFade.GetPositionX() <= 0.0) {
			SetDrawScreen(mGameScreen);
			ClearDrawScreen();
			mGame.Draw();
			SetDrawScreen(DX_SCREEN_BACK);
		}
		switch (cSystemConfig::GetInstance()->GetConfig().mRotation) {
		case eRotation_Horizontal:
		case eRotation_Reverse:
			if (DISPLAY_HEIGHT > DISPLAY_WIDTH * 4 / 3) {
				DrawRotaGraph3(DISPLAY_WIDTH / 2 + cGameConfig::GetInstance()->GetConfig().mPositionX, DISPLAY_HEIGHT / 2 + cGameConfig::GetInstance()->GetConfig().mPositionY, GAME_SCREEN_WIDTH / 2, GAME_SCREEN_HEIGHT / 2,
					static_cast<double>(DISPLAY_WIDTH) / static_cast<double>(GAME_SCREEN_WIDTH) * (cGameConfig::GetInstance()->GetConfig().mZoomX / 100.0), static_cast<double>(DISPLAY_WIDTH) / static_cast<double>(GAME_SCREEN_WIDTH) * (cGameConfig::GetInstance()->GetConfig().mZoomY / 100.0),
					TO_RADIAN(static_cast<double>(90 * cSystemConfig::GetInstance()->GetConfig().mRotation)), mGameScreen, FALSE);
			}
			else {
				DrawRotaGraph3(DISPLAY_WIDTH / 2 + cGameConfig::GetInstance()->GetConfig().mPositionX, DISPLAY_HEIGHT / 2 + cGameConfig::GetInstance()->GetConfig().mPositionY, GAME_SCREEN_WIDTH / 2, GAME_SCREEN_HEIGHT / 2,
					static_cast<double>(DISPLAY_HEIGHT) / static_cast<double>(GAME_SCREEN_HEIGHT) * (cGameConfig::GetInstance()->GetConfig().mZoomX / 100.0), static_cast<double>(DISPLAY_HEIGHT) / static_cast<double>(GAME_SCREEN_HEIGHT) * (cGameConfig::GetInstance()->GetConfig().mZoomY / 100.0),
					TO_RADIAN(static_cast<double>(90 * cSystemConfig::GetInstance()->GetConfig().mRotation)), mGameScreen, FALSE);
			}
			break;
		case eRotation_LeftRoll:
		case eRotation_RightRoll:
			if (DISPLAY_WIDTH > DISPLAY_HEIGHT * 4 / 3) {
				DrawRotaGraph3(DISPLAY_WIDTH / 2 + cGameConfig::GetInstance()->GetConfig().mPositionX, DISPLAY_HEIGHT / 2 + cGameConfig::GetInstance()->GetConfig().mPositionY, GAME_SCREEN_WIDTH / 2, GAME_SCREEN_HEIGHT / 2,
					static_cast<double>(DISPLAY_HEIGHT) / static_cast<double>(GAME_SCREEN_WIDTH) * (cGameConfig::GetInstance()->GetConfig().mZoomX / 100.0), static_cast<double>(DISPLAY_HEIGHT) / static_cast<double>(GAME_SCREEN_WIDTH) * (cGameConfig::GetInstance()->GetConfig().mZoomY / 100.0),
					TO_RADIAN(static_cast<double>(90 * cSystemConfig::GetInstance()->GetConfig().mRotation)), mGameScreen, FALSE);
			}
			else {
				DrawRotaGraph3(DISPLAY_WIDTH / 2 + cGameConfig::GetInstance()->GetConfig().mPositionX, DISPLAY_HEIGHT / 2 + cGameConfig::GetInstance()->GetConfig().mPositionY, GAME_SCREEN_WIDTH / 2, GAME_SCREEN_HEIGHT / 2,
					static_cast<double>(DISPLAY_WIDTH) / static_cast<double>(GAME_SCREEN_HEIGHT) * (cGameConfig::GetInstance()->GetConfig().mZoomX / 100.0), static_cast<double>(DISPLAY_WIDTH) / static_cast<double>(GAME_SCREEN_HEIGHT) * (cGameConfig::GetInstance()->GetConfig().mZoomY / 100.0),
					TO_RADIAN(static_cast<double>(90 * cSystemConfig::GetInstance()->GetConfig().mRotation)), mGameScreen, FALSE);
			}
			break;
		}
	}

	if (mGame.GetPauseFlag()) {
		std::tstring tPauseMes = _T("Pause");
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, static_cast<int>(255.0 * 50.0 / 100.0));
		DrawBox(0, 0, DISPLAY_WIDTH, DISPLAY_HEIGHT, GetColor(0x00, 0x00, 0x00), TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
		//DrawLine(DISPLAY_WIDTH / 2, 0, DISPLAY_WIDTH / 2, DISPLAY_HEIGHT, GetColor(0xFF, 0x00, 0x00));
		//DrawLine(0, DISPLAY_HEIGHT / 2, DISPLAY_WIDTH, DISPLAY_HEIGHT / 2, GetColor(0xFF, 0x00, 0x00));
		DrawStringToHandle(DISPLAY_WIDTH / 2 - GetDrawStringWidthToHandle(tPauseMes.c_str(), tPauseMes.size(), gSystemFont.GetElement(eSystemFont_UIFont)->GetHandle()) / 2, DISPLAY_HEIGHT / 2 - gSystemFont.GetElement(eSystemFont_UIFont)->GetSize() / 2, tPauseMes.c_str(), GetColor(0xFF, 0xFF, 0xFF), gSystemFont.GetElement(eSystemFont_UIFont)->GetHandle());
	}

	// フェードイン/アウト
	if (mFade.GetPositionX() > 0.0) {
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, static_cast<int>(mFade.GetPositionX()));
		DrawBox(0, 0, DISPLAY_WIDTH, DISPLAY_HEIGHT, GetColor(0x00, 0x00, 0x00), TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
	}

	// UIスクリーン
	SetDrawBlendMode(DX_BLENDMODE_PMA_ALPHA, 255);
	DrawRotaGraphF(DISPLAY_WIDTH / 2, DISPLAY_HEIGHT / 2, 1.0, TO_RADIAN(static_cast<double>(90 * cSystemConfig::GetInstance()->GetConfig().mRotation)), mInterfaceScreen, TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
}