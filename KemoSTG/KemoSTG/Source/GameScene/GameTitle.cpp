#include "../../Header/GameScene/GameTitle.h"

cTitleGameScene::cTitleGameScene(iSceneChanger<eGameScene> *Changer) : cGameBaseScene(Changer) {

}

cTitleGameScene::~cTitleGameScene() {

}

void cTitleGameScene::Initialize() {
	mImage.SetPath(_T("./Data/Image/Game/Title/title.png"));
	mImage.Load();
	mFade.SetPosition(0.0, 0.0);
	mTimer.Start();
}

void cTitleGameScene::Finalize() {

}

void cTitleGameScene::Update() {
	if (GetASyncLoadNum() == 0) {
		if (mTimer.GetValue() == 0) {
			mFade.MoveToPoint(255.0, 0.0, 60);
		}
		else if (mTimer.GetValue() == 60 * 10 - 80) {
			mFade.MoveToPoint(0.0, 0.0, 60);
		}
		if (mTimer.GetSecond() >= 10.0) {
			pSceneChanger->ChangeScene(eGameScene_Logo);
		}
		mTimer.Update();
		mFade.Update();
	}
}

void cTitleGameScene::Draw() {
	std::tstring tCopyright[2];
	tCopyright[0] = _T("©2017 Amusement Makers");
	tCopyright[1] = _T("Developed by C-Lab");

	double tParam;	// フェードイン/アウト用
	mFade.GetPosition(&tParam, nullptr);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, static_cast<int>(tParam));
	DrawGraph(0, 0, mImage.GetHandle(), FALSE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);

	DrawStringToHandle(GAME_SCREEN_WIDTH / 2 - GetDrawStringWidthToHandle(tCopyright[0].c_str(), tCopyright[0].size(), cGameBaseScene::mInformationFont) / 2, 24 * 22 + 8,
		tCopyright[0].c_str(), GetColor(0xFF, 0xFF, 0xFF), cGameBaseScene::mInformationFont);
	DrawStringToHandle(GAME_SCREEN_WIDTH / 2 - GetDrawStringWidthToHandle(tCopyright[1].c_str(), tCopyright[1].size(), cGameBaseScene::mInformationFont) / 2, 24 * 23 + 8,
		tCopyright[1].c_str(), GetColor(0xFF, 0xFF, 0xFF), cGameBaseScene::mInformationFont);

	if (mTimer.GetValue() % 30 < 20) {
		DrawStringToHandle(GAME_SCREEN_WIDTH / 2 - GetDrawStringWidthToHandle(_T("PRESS START BUTTON"), _tcsclen(_T("PRESS START BUTTON")), cGameBaseScene::mInformationFont) / 2, 24 * 14 + 8,
			_T("PRESS START BUTTON"), GetColor(0xFF, 0xFF, 0xFF), cGameBaseScene::mInformationFont);
	}
}