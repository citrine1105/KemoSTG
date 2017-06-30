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
	cGameBaseScene::Update();
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
	std::tstring tRank;
	std::tstring tExtend[3];
	std::tstring tVersion;

	tRank = _T("RANK: ");
	tRank += _T("NORMAL");
	tExtend[0] = _T("-EXTEND-");
	tExtend[1] = _T("40,000,000PTS");
	tExtend[2] = _T("100,000,000PTS");
	tVersion = _T("VER. ");
	tVersion += VERSION_STRING;

	double tParam;	// フェードイン/アウト用
	mFade.GetPosition(&tParam, nullptr);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, static_cast<int>(tParam));
	DrawGraph(0, 0, mImage.GetHandle(), FALSE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);

	DrawStringToHandle(GAME_SCREEN_WIDTH / 2 - GetDrawStringWidthToHandle(tRank.c_str(), tRank.size(), cGameBaseScene::mInformationFont) / 2, 24 * 18 + 8,
		tRank.c_str(), GetColor(0xFF, 0xFF, 0xFF), cGameBaseScene::mInformationFont);
	DrawStringToHandle(GAME_SCREEN_WIDTH / 2 - GetDrawStringWidthToHandle(tExtend[0].c_str(), tExtend[0].size(), cGameBaseScene::mInformationFont) / 2, 24 * 20 + 8,
		tExtend[0].c_str(), GetColor(0xFF, 0xFF, 0xFF), cGameBaseScene::mInformationFont);
	DrawFormatStringToHandle(133, 24 * 21 + 8, GetColor(0xFF, 0xFF, 0xFF), cGameBaseScene::mInformationFont, _T("1ST"));
	DrawFormatStringToHandle(133, 24 * 22 + 8, GetColor(0xFF, 0xFF, 0xFF), cGameBaseScene::mInformationFont, _T("2ND"));
	DrawStringToHandle(GAME_SCREEN_WIDTH - 133 - GetDrawStringWidthToHandle(tExtend[1].c_str(), tExtend[1].size(), cGameBaseScene::mInformationFont), 24 * 21 + 8,
		tExtend[1].c_str(), GetColor(0xFF, 0xFF, 0xFF), cGameBaseScene::mInformationFont);
	DrawStringToHandle(GAME_SCREEN_WIDTH - 133 - GetDrawStringWidthToHandle(tExtend[2].c_str(), tExtend[2].size(), cGameBaseScene::mInformationFont), 24 * 22 + 8,
		tExtend[2].c_str(), GetColor(0xFF, 0xFF, 0xFF), cGameBaseScene::mInformationFont);

	if (mTimer.GetValue() % 30 < 20) {
		DrawStringToHandle(GAME_SCREEN_WIDTH / 2 - GetDrawStringWidthToHandle(_T("INSERT 2 COINS"), _tcsclen(_T("INSERT 2 COINS")), cGameBaseScene::mInformationFont) / 2, 24 * 14 + 8,
			_T("INSERT 2 COINS"), GetColor(0xFF, 0xFF, 0xFF), cGameBaseScene::mInformationFont);
		//DrawStringToHandle(GAME_SCREEN_WIDTH / 2 - GetDrawStringWidthToHandle(_T("CONTINUE REQUIRES"), _tcsclen(_T("CONTINUE REQUIRES")), cGameBaseScene::mInformationFont) / 2, 24 * 15 + 8,
		//	_T("CONTINUE REQUIRES"), GetColor(0xFF, 0xFF, 0xFF), cGameBaseScene::mInformationFont);
		//DrawStringToHandle(GAME_SCREEN_WIDTH / 2 - GetDrawStringWidthToHandle(_T("ONLY 1 COIN"), _tcsclen(_T("ONLY 1 COIN")), cGameBaseScene::mInformationFont) / 2, 24 * 16 + 8,
		//	_T("ONLY 1 COIN"), GetColor(0xFF, 0xFF, 0xFF), cGameBaseScene::mInformationFont);
	}
	DrawStringToHandle(12, 24 * 0 + 8,
		tVersion.c_str(), GetColor(0xFF, 0xFF, 0xFF), cGameBaseScene::mInformationFont);
}