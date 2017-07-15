#include "../../Header/Scene/Load.h"

cLoadScene::cLoadScene(iSceneChanger<eScene> *Changer) : cScene(Changer) {

}

void cLoadScene::Initialize() {
	//cImageResourceContainer::GetInstance()->GetElement(eImage_None)->SetPath(_T("./Data/Image/hoge.png"));
}

void cLoadScene::Finalize() {

}

void cLoadScene::Update() {
	cScene::Update();
	if (GetASyncLoadNum() == 0) {
		pSceneChanger->ChangeScene(eScene_Title);
	}
}

void cLoadScene::Draw() {
	DrawString(0, 0, _T("Loading"), GetColor(0xFF, 0xFF, 0xFF));
}