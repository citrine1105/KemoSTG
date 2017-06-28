#include "../../Header/Scene/Game.h"

cGameScene::cGameScene(iSceneChanger<eScene> *Changer) : cScene(Changer) {

}

void cGameScene::Initialize() {

}

void cGameScene::Finalize() {

}

void cGameScene::Update() {
	cScene::Update();
}

void cGameScene::Draw() {
	DrawString(0, 0, _T("ゲーム画面ﾀﾞﾖｰ"), GetColor(0xFF, 0xFF, 0xFF));
	mVirtualPad[0].Draw();
}