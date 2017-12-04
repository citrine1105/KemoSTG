﻿#include "../../Header/Scene/Title.h"

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

	cImageResourceContainer::GetInstance()->GetElement(eImage_Title)->SetPath(_T("./Data/Image/Title/back.jpg"));
	cImageResourceContainer::GetInstance()->GetElement(eImage_TitleLogo)->SetPath(_T("./Data/Image/Title/logo.png"));

	cImageResourceContainer::GetInstance()->GetElement(eImage_Title)->Load();
	cImageResourceContainer::GetInstance()->GetElement(eImage_TitleLogo)->Load();
	//GraphFilter(cImageResourceContainer::GetInstance()->GetElement(eImage_TitleLogo)->GetHandle(), DX_GRAPH_FILTER_DOWN_SCALE, 4);
}

void cTitleScene::Finalize() {
	cImageResourceContainer::GetInstance()->GetElement(eImage_Title)->Delete();
	cImageResourceContainer::GetInstance()->GetElement(eImage_TitleLogo)->Delete();
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

		for (int i = 0; i < eButton_TotalNum; i++) {
			if (mVirtualPad[0].GetInputState(static_cast<eButtonAssign>(i)) == 1) {
				//pSceneChanger->ChangeScene(eScene_Game);
				fNext = true;
				mMessageFlash.Reset();
				mFade.MoveToPoint(255.0, 0.0, 60);
				break;
			}
		}
	}
}

void cTitleScene::Draw() {
	std::tstring tMes = _T("Press Any Button");
	std::tstring tVersion = _T("Version ");
	tVersion += VERSION_STRING;

	DrawGraph(0, 0, cImageResourceContainer::GetInstance()->GetElement(eImage_Title)->GetHandle(), FALSE);
	DrawRotaGraphF(DISPLAY_WIDTH / 2, DISPLAY_HEIGHT / 2,
		static_cast<float>(DISPLAY_SHORT) / static_cast<float>(cImageResourceContainer::GetInstance()->GetElement(eImage_TitleLogo)->GetSizeY()), TO_RADIAN(static_cast<double>(90 * cSystemConfig::GetInstance()->GetConfig().mRotation)),
		cImageResourceContainer::GetInstance()->GetElement(eImage_TitleLogo)->GetHandle(), TRUE);

	SetDrawScreen(mInterfaceScreen);
	ClearDrawScreen();

	if (fNext) {
		if (mMessageFlash.GetTime() % 12 < 6) {
			DrawStringToHandle(DISPLAY_SHORT / 2 - GetDrawStringWidthToHandle(tMes.c_str(), tMes.size(), cFontContainer::GetInstance()->GetElement(eFont_GlobalInterfaceFont)) / 2, DISPLAY_SHORT * 2 / 3 - GetFontSizeToHandle(cFontContainer::GetInstance()->GetElement(eFont_GlobalInterfaceFont) / 2),
				tMes.c_str(), GetColor(0xFF, 0xFF, 0xFF), cFontContainer::GetInstance()->GetElement(eFont_GlobalInterfaceFont));
		}
	}
	else {
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, mMessageFade.GetPositionX());
		DrawStringToHandle(DISPLAY_SHORT / 2 - GetDrawStringWidthToHandle(tMes.c_str(), tMes.size(), cFontContainer::GetInstance()->GetElement(eFont_GlobalInterfaceFont)) / 2, DISPLAY_SHORT * 2 / 3 - GetFontSizeToHandle(cFontContainer::GetInstance()->GetElement(eFont_GlobalInterfaceFont) / 2),
			tMes.c_str(), GetColor(0xFF, 0xFF, 0xFF), cFontContainer::GetInstance()->GetElement(eFont_GlobalInterfaceFont));
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
	}

	DrawStringToHandle(DISPLAY_SHORT - GetDrawStringWidthToHandle(tVersion.c_str(), tVersion.size(), cFontContainer::GetInstance()->GetElement(eFont_GlobalInterfaceFont)) - UPSCALE(12), DISPLAY_HEIGHT - GetFontSizeToHandle(cFontContainer::GetInstance()->GetElement(eFont_GlobalInterfaceFont)) - UPSCALE(8),
		tVersion.c_str(), GetColor(0xFF, 0xFF, 0xFF), cFontContainer::GetInstance()->GetElement(eFont_GlobalInterfaceFont));

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