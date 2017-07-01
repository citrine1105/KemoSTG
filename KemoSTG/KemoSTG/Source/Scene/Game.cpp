#include "../../Header/Scene/Game.h"

cGameScene::cGameScene(iSceneChanger<eScene> *Changer) : cScene(Changer) {
	
}

cGameScene::~cGameScene() {
	
}

void cGameScene::Initialize() {
	mGameScreen = MakeScreen(GAME_SCREEN_WIDTH, GAME_SCREEN_HEIGHT);
	mGame.Initialize();
	mGame.SetVirtualPad(mVirtualPad);
}

void cGameScene::Finalize() {
	DeleteGraph(mGameScreen);
	mGame.Finalize();
}

void cGameScene::Update() {
	cScene::Update();
	mGame.Update();
}

void cGameScene::Draw() {
	mVirtualPad[0].Draw();
	SetDrawScreen(mGameScreen);
	ClearDrawScreen();
	mGame.Draw();
	//DrawBox(0, 0, GAME_SCREEN_WIDTH, GAME_SCREEN_HEIGHT, GetColor(0xFF, 0x00, 0x00), FALSE);	// テスト
	SetDrawScreen(DX_SCREEN_BACK);
	//DrawRotaGraph(320, 240, 1.0, DEGREE_TO_RADIAN(90.0), mGameScreen, FALSE);
	DrawRotaGraph(320, 240, 0.75, DEGREE_TO_RADIAN(0.0), mGameScreen, FALSE);
}