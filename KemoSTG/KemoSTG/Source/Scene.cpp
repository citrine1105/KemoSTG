#include "../Header/Scene.h"

cPad cScene::mPad[2];
cVirtualPad cScene::mVirtualPad[2];

cScene::cScene(iSceneChanger<eScene> *Changer) {
	pSceneChanger = Changer;
	mPad[0].SetJoyPadNum(DX_INPUT_PAD1);
	mPad[1].SetJoyPadNum(DX_INPUT_PAD2);
	mVirtualPad[0].SetJoyPad(&mPad[0]);
	mVirtualPad[0].SetDefaultAssign(0);
	mVirtualPad[1].SetJoyPad(&mPad[1]);
	mVirtualPad[1].SetDefaultAssign(1);
}

cScene::~cScene() {

}

void cScene::Initialize() {

}

void cScene::Finalize() {

}

void cScene::Update() {
	mVirtualPad[0].Update();
	mVirtualPad[1].Update();
}

void cScene::Draw() {

}