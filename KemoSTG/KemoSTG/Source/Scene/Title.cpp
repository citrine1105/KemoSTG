﻿#include "../../Header/Scene/Title.h"

cImageResourceContainer gTitleImageContainer;
int cScene::mInterfaceScreen;

cTitleScene::cTitleScene(iSceneChanger<eScene> *Changer) : cScene(Changer) {

}

void cTitleScene::Initialize() {
	fNext = false;

	mMessageFlash.Start();
	mMessageFade.SetPosition(0.0, 0.0);
	mMessageFade.MoveToPoint(255.0, 0.0, 40, eEasing_Sine);
	mFade.SetPosition(255.0, 0.0);
	mFade.MoveToPoint(0.0, 0.0, 60);

	gTitleImageContainer.Initialize(eTitle_TotalNum);

	gTitleImageContainer.GetElement(eTitle_Logo)->SetPath(_T("./Data/Image/Title/logo.png"));
	gTitleImageContainer.GetElement(eTitle_Back)->SetPath(_T("./Data/Image/Title/back.png"));
	gTitleImageContainer.GetElement(eTitle_Guide)->SetPath(_T("./Data/Image/Title/guide.png"));

	for (int i = 0; i < eTitle_TotalNum; i++) {
		gTitleImageContainer.GetElement(i)->SetPremulAlphaFlag(true);
	}

	gTitleImageContainer.Load();
}

void cTitleScene::Finalize() {
	gTitleImageContainer.Finalize();
}

void cTitleScene::Update() {
	cScene::Update();
	mMessageFlash.Update();
	if (GetASyncLoadNum() == 0) {
		mMessageFade.Update();
		mFade.Update();
	}

	if (fNext) {
		if (mFade.GetPositionX() >= 255.0) {
			pSceneChanger->ChangeScene(eScene_Game);
		}
	}
	else {
		if (mMessageFade.GetPositionX() >= 255.0) {
			mMessageFade.MoveToPoint(0.0, 0.0, 40, eEasing_Linear);
		}
		else if (mMessageFade.GetPositionX() <= 0.0) {
			mMessageFade.MoveToPoint(255.0, 0.0, 40, eEasing_Sine);
		}

		for (auto &i : mVirtualPad) {
			for (int j = 0; j < eButton_TotalNum; j++) {
				if (i.GetInputState(static_cast<eButtonAssign>(j)) == 1) {	// いずれかのボタンが押されたら
					//pSceneChanger->ChangeScene(eScene_Game);
					fNext = true;
					mMessageFlash.Reset();
					mFade.MoveToPoint(255.0, 0.0, 60);
					break;
				}
			}
		}
	}
}

void cTitleScene::Draw() {
	std::tstring tCopyright = _T("©2018 C-Lab");
	std::tstring tVersion = _T("Version ");
	tVersion += VERSION_STRING;

	DrawRotaGraph(DISPLAY_WIDTH / 2, DISPLAY_HEIGHT / 2, DISPLAY_LONG / 3840.0, 0.0, gTitleImageContainer.GetElement(eTitle_Back)->GetHandle(), FALSE);
	DrawRotaGraphF(DISPLAY_WIDTH / 2, DISPLAY_HEIGHT / 2,
		static_cast<float>(DISPLAY_SHORT) / static_cast<float>(gTitleImageContainer.GetElement(eTitle_Logo)->GetSizeY()), TO_RADIAN(static_cast<double>(90 * cSystemConfig::GetInstance()->GetConfig().mRotation)),
		gTitleImageContainer.GetElement(eTitle_Logo)->GetHandle(), TRUE);

	SetDrawScreen(mInterfaceScreen);
	ClearDrawScreen();

	// 著作権表記
	SetDrawBlendMode(DX_BLENDMODE_PMA_ALPHA, 255);
	DrawStringToHandle(DISPLAY_SHORT / 2 - GetDrawStringWidthToHandle(tCopyright.c_str(), tCopyright.size(), gSystemFont.GetElement(eSystemFont_UIFont)->GetHandle()) / 2, DISPLAY_SHORT * 29 / 32 - gSystemFont.GetElement(eSystemFont_UIFont)->GetSize() / 2,
		tCopyright.c_str(), GetColor(0xFF, 0xFF, 0xFF), gSystemFont.GetElement(eSystemFont_UIFont)->GetHandle());
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);

	// Press Any Button
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
	if (fNext) {
		if (mMessageFlash.GetTime() % 12 < 6) {
			DrawRotaGraphF(DISPLAY_SHORT / 2.0, DISPLAY_SHORT * 2.0 / 3.0, static_cast<double>(DISPLAY_SHORT) / static_cast<double>(2160), 0.0, gTitleImageContainer.GetElement(eTitle_Guide)->GetHandle(), TRUE);
		}
	}
	else {
		SetDrawBlendMode(DX_BLENDMODE_PMA_ALPHA, mMessageFade.GetPositionX());
		DrawRotaGraphF(DISPLAY_SHORT / 2.0, DISPLAY_SHORT * 2.0 / 3.0, static_cast<double>(DISPLAY_SHORT) / static_cast<double>(2160), 0.0, gTitleImageContainer.GetElement(eTitle_Guide)->GetHandle(), TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
	}

	// バージョン表記
	SetDrawBlendMode(DX_BLENDMODE_PMA_ALPHA, 255);
	DrawStringToHandle(DISPLAY_SHORT - GetDrawStringWidthToHandle(tVersion.c_str(), tVersion.size(), gSystemFont.GetElement(eSystemFont_UIFont)->GetHandle()) - UPSCALE(12), DISPLAY_SHORT - gSystemFont.GetElement(eSystemFont_UIFont)->GetSize() - UPSCALE(8),
		tVersion.c_str(), GetColor(0xFF, 0xFF, 0xFF), gSystemFont.GetElement(eSystemFont_UIFont)->GetHandle());
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);

	// コントローラー情報(メニュー画面に実装して)
	DrawStringToHandle(UPSCALE(12), UPSCALE(8),
		_T("P1: Controller 1(X)"), GetColor(0xFF, 0xFF, 0xFF), gSystemFont.GetElement(eSystemFont_UIFont)->GetHandle());
	DrawStringToHandle(DISPLAY_SHORT - GetDrawStringWidthToHandle(_T("P2: Keyboard"), _tcslen(_T("P2: Keyboard")), gSystemFont.GetElement(eSystemFont_UIFont)->GetHandle()) - UPSCALE(12), UPSCALE(8),
		_T("P2: Keyboard"), GetColor(0xFF, 0xFF, 0xFF), gSystemFont.GetElement(eSystemFont_UIFont)->GetHandle());

	SetDrawScreen(DX_SCREEN_BACK);

	SetDrawBlendMode(DX_BLENDMODE_PMA_ALPHA, 255);
	DrawRotaGraphF(DISPLAY_WIDTH / 2, DISPLAY_HEIGHT / 2, 1.0, TO_RADIAN(static_cast<double>(90 * cSystemConfig::GetInstance()->GetConfig().mRotation)), mInterfaceScreen, TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, mFade.GetPositionX());
	DrawBox(0, 0, DISPLAY_WIDTH, DISPLAY_HEIGHT, GetColor(0x00, 0x00, 0x00), TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);

	//DrawFormatString(0, 0, GetColor(0xFF, 0xFF, 0xFF), _T("%f"), mMessageFade.GetPositionX());
	//DrawFormatString(0, 18, GetColor(0xFF, 0xFF, 0xFF), _T("%f"), mFade.GetPositionX());
}