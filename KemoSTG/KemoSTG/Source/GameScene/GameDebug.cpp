#include "../../Header/GameScene/GameDebug.h"

cDebugGameScene::cDebugGameScene(iSceneChanger<eGameScene> *Changer) : cGameBaseScene(Changer) {

}

cDebugGameScene::~cDebugGameScene() {

}

void cDebugGameScene::Initialize() {

}

void cDebugGameScene::Finalize() {

}

void cDebugGameScene::Update() {
	for (int i = 0; i < 2; i++) {
		if (ppVirtualPad[i]->GetInputState(eButton_Possess) == 1) {
			pSceneChanger->ChangeScene(eGameScene_Logo);
		}
	}
}

void cDebugGameScene::Draw() {
	DrawStringToHandle(12, 8, _T("Debug Room"), GetColor(0xFF, 0xFF, 0xFF), gGameFontContainer.GetElement(eGameFont_Interface)->GetHandle());
}