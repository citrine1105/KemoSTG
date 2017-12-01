#include "../../Header/Scene/Game.h"

cGameScene::cGameScene(iSceneChanger<eScene> *Changer) : cScene(Changer) {
	
}

cGameScene::~cGameScene() {
	
}

void cGameScene::Initialize() {
	mGameScreen = MakeScreen(GAME_SCREEN_WIDTH, GAME_SCREEN_HEIGHT);
	mGame.Initialize();
	mGame.SetVirtualPad(mVirtualPad);

	mFade.SetPosition(255.0, 0.0);

	cImageResourceContainer::GetInstance()->GetElement(eImage_Life)->SetPath(_T("./Data/Image/Game/life.png"));
	cImageResourceContainer::GetInstance()->GetElement(eImage_Bomb)->SetPath(_T("./Data/Image/Game/bomb.png"));
	cImageResourceContainer::GetInstance()->GetElement(eImage_Bomb)->SetDivisionSize(4, 4, 1, 20, 20);
	cImageResourceContainer::GetInstance()->GetElement(eImage_Background)->SetPath(_T("./Data/Image/Game/Background/1.jpg"));
	cImageResourceContainer::GetInstance()->GetElement(eImage_ScoreBoard)->SetPath(_T("./Data/Image/Game/score_board.png"));
	cImageResourceContainer::GetInstance()->GetElement(eImage_ScoreBoard)->SetDivisionSize(2, 2, 1, 160, 56);
	cImageResourceContainer::GetInstance()->GetElement(eImage_RateNumber)->SetPath(_T("./Data/Image/Game/rate_num.png"));
	cImageResourceContainer::GetInstance()->GetElement(eImage_RateNumber)->SetDivisionSize(11, 11, 1, 24, 36);
	cImageResourceContainer::GetInstance()->GetElement(eImage_LifeGauge)->SetPath(_T("./Data/Image/Game/gauge.png"));
	cImageResourceContainer::GetInstance()->GetElement(eImage_LifeGauge)->SetDivisionSize(4, 4, 1, 16, 16);
	cImageResourceContainer::GetInstance()->GetElement(eImage_CaptionBomb)->SetPath(_T("./Data/Image/Game/Caption/bomb.png"));
	cImageResourceContainer::GetInstance()->GetElement(eImage_CaptionTime)->SetPath(_T("./Data/Image/Game/Caption/time.png"));

	cImageResourceContainer::GetInstance()->GetElement(eImage_Life)->Load();
	cImageResourceContainer::GetInstance()->GetElement(eImage_Bomb)->Load();
	cImageResourceContainer::GetInstance()->GetElement(eImage_Background)->Load();
	cImageResourceContainer::GetInstance()->GetElement(eImage_ScoreBoard)->Load();
	cImageResourceContainer::GetInstance()->GetElement(eImage_RateNumber)->Load();
	cImageResourceContainer::GetInstance()->GetElement(eImage_LifeGauge)->Load();
	cImageResourceContainer::GetInstance()->GetElement(eImage_CaptionBomb)->Load();
	cImageResourceContainer::GetInstance()->GetElement(eImage_CaptionTime)->Load();
}

void cGameScene::Finalize() {
	DeleteGraph(mGameScreen);
	mGame.Finalize();

	cImageResourceContainer::GetInstance()->GetElement(eImage_Background)->Finalize();
}

void cGameScene::Update() {
	mFade.Update();

	cScene::Update();
	if (GetASyncLoadNum() == 0 && mFade.GetPositionX() >= 255.0) {
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
	DrawRotaGraph(DISPLAY_WIDTH / 2, DISPLAY_HEIGHT / 2, 1.0, 0.0, cImageResourceContainer::GetInstance()->GetElement(eImage_Background)->GetHandle(), FALSE);
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
		DrawStringToHandle(DISPLAY_WIDTH / 2 - GetDrawStringWidthToHandle(tPauseMes.c_str(), tPauseMes.size(), cFontContainer::GetInstance()->GetElement(eFont_GlobalInterfaceFont)) / 2, DISPLAY_HEIGHT / 2 - GetFontSizeToHandle(cFontContainer::GetInstance()->GetElement(eFont_GlobalInterfaceFont)) / 2, tPauseMes.c_str(), GetColor(0xFF, 0xFF, 0xFF), cFontContainer::GetInstance()->GetElement(eFont_GlobalInterfaceFont));
	}

	if (mFade.GetPositionX() > 0.0) {
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, static_cast<int>(mFade.GetPositionX()));
		DrawBox(0, 0, DISPLAY_WIDTH, DISPLAY_HEIGHT, GetColor(0x00, 0x00, 0x00), TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
	}
}