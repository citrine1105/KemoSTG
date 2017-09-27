#include "../../Header/Scene/Title.h"

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
	
	cImageResourceContainer::GetInstance()->GetElement(eImage_Title)->Load();
}

void cTitleScene::Finalize() {
	cImageResourceContainer::GetInstance()->GetElement(eImage_Title)->Delete();
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
			mMessageFade.MoveToPoint(0.0, 0.0, 40, eEasing_Sine);
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

	DrawStringToHandle(cSystemConfig::GetInstance()->GetConfig().mDisplayWidth - GetDrawStringWidthToHandle(tVersion.c_str(), tVersion.size(), cFontContainer::GetInstance()->GetElement(eFont_GlobalInterfaceFont)), cSystemConfig::GetInstance()->GetConfig().mDisplayHeight - GetFontSizeToHandle(cFontContainer::GetInstance()->GetElement(eFont_GlobalInterfaceFont)),
		tVersion.c_str(), GetColor(0xFF, 0xFF, 0xFF), cFontContainer::GetInstance()->GetElement(eFont_GlobalInterfaceFont));

	if (fNext) {
		if (mMessageFlash.GetTime() % 12 < 6) {
			DrawStringToHandle(cSystemConfig::GetInstance()->GetConfig().mDisplayWidth / 2 - GetDrawStringWidthToHandle(tMes.c_str(), tMes.size(), cFontContainer::GetInstance()->GetElement(eFont_GlobalInterfaceFont)) / 2, cSystemConfig::GetInstance()->GetConfig().mDisplayHeight * 2 / 3 - GetFontSizeToHandle(cFontContainer::GetInstance()->GetElement(eFont_GlobalInterfaceFont) / 2),
				tMes.c_str(), GetColor(0xFF, 0xFF, 0xFF), cFontContainer::GetInstance()->GetElement(eFont_GlobalInterfaceFont));
		}
	}
	else {
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, mMessageFade.GetPositionX());
		DrawStringToHandle(cSystemConfig::GetInstance()->GetConfig().mDisplayWidth / 2 - GetDrawStringWidthToHandle(tMes.c_str(), tMes.size(), cFontContainer::GetInstance()->GetElement(eFont_GlobalInterfaceFont)) / 2, cSystemConfig::GetInstance()->GetConfig().mDisplayHeight * 2 / 3 - GetFontSizeToHandle(cFontContainer::GetInstance()->GetElement(eFont_GlobalInterfaceFont) / 2),
			tMes.c_str(), GetColor(0xFF, 0xFF, 0xFF), cFontContainer::GetInstance()->GetElement(eFont_GlobalInterfaceFont));
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
	}

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, mFade.GetPositionX());
	DrawBox(0, 0, DISPLAY_WIDTH, DISPLAY_HEIGHT, GetColor(0x00, 0x00, 0x00), TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);

	//DrawFormatString(0, 0, GetColor(0xFF, 0xFF, 0xFF), _T("%f"), mMessageFade.GetPositionX());
	//DrawFormatString(0, 18, GetColor(0xFF, 0xFF, 0xFF), _T("%f"), mFade.GetPositionX());
}