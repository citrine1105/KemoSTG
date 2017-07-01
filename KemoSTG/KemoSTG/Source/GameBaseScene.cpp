#include "../Header/GameBaseScene.h"

cVirtualPad **cGameBaseScene::ppVirtualPad;
int cGameBaseScene::mInformationFont;

cGameBaseScene::cGameBaseScene(iSceneChanger<eGameScene> *Changer) {
	pSceneChanger = Changer;
}

cGameBaseScene::~cGameBaseScene() {

}

void cGameBaseScene::SetVirtualPad(cVirtualPad Pad[2]) {
	ppVirtualPad[0] = &Pad[0];
	ppVirtualPad[1] = &Pad[1];
}

void cGameBaseScene::Initialize() {
	if (ppVirtualPad == nullptr) {
		ppVirtualPad = new cVirtualPad*[2];	// パッドの生成
	}
	mInformationFont = CreateFontToHandle(_T("Palatino Linotype"), 18, 0, DX_FONTTYPE_ANTIALIASING_EDGE_4X4);	// フォントハンドルの取得
}

void cGameBaseScene::Finalize() {
	if (ppVirtualPad != nullptr) {
		delete[] ppVirtualPad;
	}
	DeleteFontToHandle(mInformationFont);
}

void cGameBaseScene::Update() {
	ppVirtualPad[0]->Update();
	ppVirtualPad[1]->Update();
}

void cGameBaseScene::Draw() {
	
}