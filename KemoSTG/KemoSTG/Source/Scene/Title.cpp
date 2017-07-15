#include "../../Header/Scene/Title.h"

cTitleScene::cTitleScene(iSceneChanger<eScene> *Changer) : cScene(Changer) {

}

void cTitleScene::Initialize() {
	fNext = false;

	mMessageAnimation.Start();
	mFade.SetPosition(255.0, 0.0);
	mFade.MoveToPoint(0.0, 0.0, 60);

	cImageResourceContainer::GetInstance()->GetElement(eImage_Title)->SetPath(_T("./Data/Image/Title/back.jpg"));
	
	cImageResourceContainer::GetInstance()->GetElement(eImage_Title)->Load();
}

void cTitleScene::Finalize() {
	cImageResourceContainer::GetInstance()->GetElement(eImage_Title)->Delete();
}

void cTitleScene::Update() {
	double tPos;
	mFade.GetPosition(&tPos, nullptr);

	cScene::Update();
	mMessageAnimation.Update();
	if (GetASyncLoadNum() == 0) {
		mFade.Update();
	}

	if (fNext) {
		if (tPos >= 255.0) {
			pSceneChanger->ChangeScene(eScene_Game);
		}
	}
	else {
		for (int i = 0; i < eButton_TotalNum; i++) {
			if (mVirtualPad[0].GetInputState(static_cast<eButtonAssign>(i)) == 1) {
				//pSceneChanger->ChangeScene(eScene_Game);
				fNext = true;
				mFade.MoveToPoint(255.0, 0.0, 60);
				break;
			}
		}
	}
}

void cTitleScene::Draw() {
	double tFade;

	mFade.GetPosition(&tFade, nullptr);
	DrawGraph(0, 0, cImageResourceContainer::GetInstance()->GetElement(eImage_Title)->GetHandle(), FALSE);
	if (fNext) {
		if (mMessageAnimation.GetValue() % 12 < 6) {
			DrawString(0, 0, _T("Press any button"), GetColor(0xFF, 0xFF, 0xFF));
		}
	}
	else {
		if (mMessageAnimation.GetValue() % 60 < 30) {
			DrawString(0, 0, _T("Press any button"), GetColor(0xFF, 0xFF, 0xFF));
		}
	}
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, tFade);
	DrawBox(0, 0, 640, 480, GetColor(0x00, 0x00, 0x00), TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
}