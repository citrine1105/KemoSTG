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

	cImageResourceContainer::GetInstance()->GetElement(eImage_GameBackground)->SetPath(_T("./Data/Image/Game/Background/1.jpg"));

	cImageResourceContainer::GetInstance()->GetElement(eImage_GameBackground)->Load();
}

void cGameScene::Finalize() {
	DeleteGraph(mGameScreen);
	mGame.Finalize();

	cImageResourceContainer::GetInstance()->GetElement(eImage_GameBackground)->Finalize();
}

void cGameScene::Update() {
	double tPos;

	mFade.Update();
	mFade.GetPosition(&tPos, nullptr);

	cScene::Update();
	if (GetASyncLoadNum() == 0 && tPos >= 255.0) {
		mFade.MoveToPoint(0.0, 0.0, 30);
	}

	if (tPos <= 0.0) {
		mGame.Update();
	}
}

void cGameScene::Draw() {
	double tPos;

	mFade.GetPosition(&tPos, nullptr);

	//mVirtualPad[0].Draw();
	DrawRotaGraph(640 / 2, 480 / 2, 1.0, 0.0, cImageResourceContainer::GetInstance()->GetElement(eImage_GameBackground)->GetHandle(), FALSE);
	if (CheckHandleASyncLoad(mGameScreen) == FALSE) {
		if (tPos <= 0.0) {
			SetDrawScreen(mGameScreen);
			ClearDrawScreen();
			mGame.Draw();
			SetDrawScreen(DX_SCREEN_BACK);
		}
		//DrawRotaGraph(320, 240, 1.0, TO_RADIAN(90.0), mGameScreen, FALSE);
		DrawRotaGraph(320, 240, 0.75, TO_RADIAN(0.0), mGameScreen, FALSE);
	}

	if (tPos > 0.0) {
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, static_cast<int>(tPos));
		DrawBox(0, 0, 640, 480, GetColor(0x00, 0x00, 0x00), TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
	}
}