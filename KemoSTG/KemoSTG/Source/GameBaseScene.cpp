#include "../Header/GameBaseScene.h"

//cVirtualPad **cGameBaseScene::ppVirtualPad;
cVirtualPad* cGameBaseScene::pInputPad;
std::array<cVirtualPad, 2> cGameBaseScene::mVirtualPad;

cGameBaseScene::cGameBaseScene(iSceneChanger<eGameScene> *Changer) {
	pSceneChanger = Changer;
}

cGameBaseScene::~cGameBaseScene() {

}

void cGameBaseScene::SetVirtualPad(cVirtualPad *Pad) {
	//ppVirtualPad[0] = &Pad[0];
	//ppVirtualPad[1] = &Pad[1];
	pInputPad = Pad;
}

cVirtualPad* cGameBaseScene::GetVirtualPadPointer(const unsigned int Index) {
	return &mVirtualPad.at(Index);
}

void cGameBaseScene::Initialize() {
	//if (ppVirtualPad == nullptr) {
	//	ppVirtualPad = new cVirtualPad*[2];	// パッドの生成
	//}
	for (auto &i : mVirtualPad) {
		i.Initialize();
	}
}

void cGameBaseScene::Finalize() {
	//if (ppVirtualPad != nullptr) {
	//	delete[] ppVirtualPad;
	//}
	for (auto &i : mVirtualPad) {
		i.Finalize();
	}
}

void cGameBaseScene::Update() {
	//ppVirtualPad[0]->Update();
	//ppVirtualPad[1]->Update();
	for (int i = 0; i < PLAYER_NUM; i++) {
		mVirtualPad.at(i).SetButtonState((pInputPad + i)->GetButtonState());	// 現実時間におけるパッド入力情報を受け渡す
	}
	for (auto &i : mVirtualPad) {
		i.Update();
	}
}

void cGameBaseScene::Draw() {
	
}