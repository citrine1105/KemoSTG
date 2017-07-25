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

	if (mFade.GetPositionX() <= 0.0) {
		mGame.Update();
	}
}

void cGameScene::Draw() {
	//mVirtualPad[0].Draw();
	DrawRotaGraph(640 / 2, 480 / 2, 1.0, 0.0, cImageResourceContainer::GetInstance()->GetElement(eImage_Background)->GetHandle(), FALSE);
	if (CheckHandleASyncLoad(mGameScreen) == FALSE) {
		if (mFade.GetPositionX() <= 0.0) {
			SetDrawScreen(mGameScreen);
			ClearDrawScreen();
			mGame.Draw();
			SetDrawScreen(DX_SCREEN_BACK);
		}
		//DrawRotaGraph(320, 240, 1.0, TO_RADIAN(90.0), mGameScreen, FALSE);
		DrawRotaGraph(320, 240, 0.75, TO_RADIAN(0.0), mGameScreen, FALSE);
	}

	if (mFade.GetPositionX() > 0.0) {
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, static_cast<int>(mFade.GetPositionX()));
		DrawBox(0, 0, 640, 480, GetColor(0x00, 0x00, 0x00), TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
	}
}