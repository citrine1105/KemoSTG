#include "../../Header/Scene/Title.h"

cTitleScene::cTitleScene(iSceneChanger<eScene> *Changer) : cScene(Changer) {

}

void cTitleScene::Initialize() {

}

void cTitleScene::Finalize() {

}

void cTitleScene::Update() {
	cScene::Update();
	if (mVirtualPad[0].GetInputState(eButton_Pause) == 1) {
		pSceneChanger->ChangeScene(eScene_Game);
	}
}

void cTitleScene::Draw() {
	DrawString(0, 0, _T("ƒ^ƒCƒgƒ‹‰æ–ÊÀÞÖ°"), GetColor(0xFF, 0xFF, 0xFF));
	mVirtualPad[0].Draw();
}