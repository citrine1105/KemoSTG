﻿#include "../Header/VirtualPad.h"

cVirtualPad::cVirtualPad() {
	this->Initialize();
}

cVirtualPad::cVirtualPad(cPad *Pad) {
	this->Initialize();
	this->SetJoyPad(Pad);
}

cVirtualPad::~cVirtualPad() {
	this->Finalize();
}

void cVirtualPad::SetDefaultAssign(const int Type) {
	switch (Type) {
	case 1:
		mKeyAssign[eButton_Shot] = KEY_INPUT_COMMA;
		mKeyAssign[eButton_Possess] = KEY_INPUT_PERIOD;
		mKeyAssign[eButton_Bomb] = KEY_INPUT_SLASH;
		mKeyAssign[eButton_FullAuto] = KEY_INPUT_RSHIFT;
		mKeyAssign[eButton_Pause] = KEY_INPUT_2;
		mKeyAssign[eButton_Coin] = KEY_INPUT_6;
		mKeyAssign[eButton_Service] = KEY_INPUT_0;

		mDPadKeyAssign[eDPad_Up] = KEY_INPUT_W;
		mDPadKeyAssign[eDPad_Down] = KEY_INPUT_A;
		mDPadKeyAssign[eDPad_Left] = KEY_INPUT_S;
		mDPadKeyAssign[eDPad_Right] = KEY_INPUT_D;
		break;
	default:
		mKeyAssign[eButton_Shot] = KEY_INPUT_Z;
		mKeyAssign[eButton_Possess] = KEY_INPUT_X;
		mKeyAssign[eButton_Bomb] = KEY_INPUT_C;
		mKeyAssign[eButton_FullAuto] = KEY_INPUT_LSHIFT;
		mKeyAssign[eButton_Pause] = KEY_INPUT_1;
		mKeyAssign[eButton_Coin] = KEY_INPUT_5;
		mKeyAssign[eButton_Service] = KEY_INPUT_9;

		mDPadKeyAssign[eDPad_Up] = KEY_INPUT_UP;
		mDPadKeyAssign[eDPad_Down] = KEY_INPUT_DOWN;
		mDPadKeyAssign[eDPad_Left] = KEY_INPUT_LEFT;
		mDPadKeyAssign[eDPad_Right] = KEY_INPUT_RIGHT;
		break;
	}

	mDirectInputAssign[eButton_Shot] = eDirectInputAssign_Button1;
	mDirectInputAssign[eButton_Possess] = eDirectInputAssign_Button2;
	mDirectInputAssign[eButton_Bomb] = eDirectInputAssign_Button3;
	mDirectInputAssign[eButton_FullAuto] = eDirectInputAssign_Button4;
	mDirectInputAssign[eButton_Pause] = eDirectInputAssign_Button5;
	mDirectInputAssign[eButton_Coin] = eDirectInputAssign_Button6;
	mDirectInputAssign[eButton_Service] = eDirectInputAssign_Button7;

	mXInputAssign[eButton_Shot] = eXInputAssign_A;
	mXInputAssign[eButton_Possess] = eXInputAssign_B;
	mXInputAssign[eButton_Bomb] = eXInputAssign_Y;
	mXInputAssign[eButton_FullAuto] = eXInputAssign_RT;
	mXInputAssign[eButton_Pause] = eXInputAssign_Start;
	mXInputAssign[eButton_Coin] = eXInputAssign_LeftStickButton;
	mXInputAssign[eButton_Service] = eXInputAssign_RightStickButton;

	mStickDeadZone = 0;
}

void cVirtualPad::SetJoyPad(cPad *Pad) {
	pPad = Pad;
}

void cVirtualPad::SetButtonAssign(const eButtonAssign Assign, const unsigned char Key) {
	int i, j;
	for (i = 0; i < eButton_TotalNum; i++) {
		if (mKeyAssign[i] == Key) {	// 既に同じ割り当てのキーがあるか探索
			break;
		}
	}
	for (j = 0; j < eDPad_TotalNum; j++) {
		if (mDPadKeyAssign[j] == Key) {	// 既に同じ割り当てのキーがあるか探索
			break;
		}
	}
	if (i < eButton_TotalNum) {	// ある場合
		mKeyAssign[i] = mKeyAssign[Assign];	// 入れ替え
		mKeyAssign[Assign] = Key;
	}
	else if (j < eDPad_TotalNum) {
		mDPadKeyAssign[j] = mKeyAssign[Assign];	// 入れ替え
		mKeyAssign[Assign] = Key;
	}
	else {						// ない場合
		mKeyAssign[Assign] = Key;	// 設定
	}
}

void cVirtualPad::SetButtonAssign(const eButtonAssign Assign, const eDirectInputAssign Button) {
	int i;
	for (i = 0; i < eButton_TotalNum; i++) {
		if (mDirectInputAssign[i] == Button) {	// 既に同じ割り当てのボタンがあるか探索
			break;
		}
	}
	if (i < eButton_TotalNum) {	// ある場合
		mDirectInputAssign[i] = mDirectInputAssign[Assign];	// 入れ替え
		mDirectInputAssign[Assign] = Button;
	}
	else {						// ない場合
		mDirectInputAssign[Assign] = Button;	// 設定
	}
}

void cVirtualPad::SetButtonAssign(const eButtonAssign Assign, const eXInputAssign Button) {
	int i;
	for (i = 0; i < eButton_TotalNum; i++) {
		if (mXInputAssign[i] == Button) {	// 既に同じ割り当てのボタンがあるか探索
			break;
		}
	}
	if (i < eButton_TotalNum) {	// ある場合
		mXInputAssign[i] = mXInputAssign[Assign];	// 入れ替え
		mXInputAssign[Assign] = Button;
	}
	else {						// ない場合
		mXInputAssign[Assign] = Button;	// 設定
	}
}

void cVirtualPad::SetDPadAssign(const eDPadAssign Assign, const unsigned char Key) {
	int i, j;
	for (i = 0; i < eButton_TotalNum; i++) {
		if (mKeyAssign[i] == Key) {	// 既に同じ割り当てのキーがあるか探索
			break;
		}
	}
	for (j = 0; j < eDPad_TotalNum; j++) {
		if (mDPadKeyAssign[j] == Key) {	// 既に同じ割り当てのキーがあるか探索
			break;
		}
	}
	if (i < eButton_TotalNum) {	// ある場合
		mKeyAssign[i] = mDPadKeyAssign[Assign];	// 入れ替え
		mDPadKeyAssign[Assign] = Key;
	}
	else if (j < eDPad_TotalNum) {
		mDPadKeyAssign[j] = mDPadKeyAssign[Assign];	// 入れ替え
		mDPadKeyAssign[Assign] = Key;
	}
	else {						// ない場合
		mKeyAssign[Assign] = Key;	// 設定
	}
}

cPad* cVirtualPad::GetJoyPad() {
	return pPad;
}

unsigned AUTO_INT cVirtualPad::GetInputState(const eButtonAssign Button) {
	return mButtonInputState[Button];
}

unsigned AUTO_INT cVirtualPad::GetInputState(const eDPadAssign Button) {
	return mDPadInputState[Button];
}

void cVirtualPad::ResetInputState() {
	for (int i = 0; i < eButton_TotalNum; i++) {
		mButtonInputState[i] = 0;
	}
	for (int i = 0; i < eDPad_TotalNum; i++) {
		mDPadInputState[i] = 0;
	}
}

void cVirtualPad::Initialize() {
	pPad = nullptr;
	this->SetDefaultAssign();
	this->ResetInputState();
}

void cVirtualPad::Finalize() {
	pPad = nullptr;
	this->SetDefaultAssign();
	this->ResetInputState();
}

void cVirtualPad::Update() {
	pPad->Update();

	for (int i = 0; i < eButton_TotalNum; i++) {
		if (CheckHitKey(mKeyAssign[i]) != 0) {	// キーボード入力
			++mButtonInputState[i];
		}
		else if (pPad->GetXInputFlag() &&
			(mXInputAssign[i] == eXInputAssign_LT || mXInputAssign[i] == eXInputAssign_RT) &&
			pPad->GetJoyPadInputState(mXInputAssign[i]) >= static_cast<int>(254.0 * (static_cast<double>(mStickDeadZone) / 100.0)) + 1) {	// LTかRTに割り当てられている場合
					++mButtonInputState[i];
		}
		else if (pPad->GetXInputFlag() &&
			pPad->GetJoyPadInputState(mXInputAssign[i]) != 0) {		// XInput入力
				++mButtonInputState[i];
		}
		else if (!pPad->GetXInputFlag() &&
			pPad->GetJoyPadInputState(mDirectInputAssign[i]) != 0) {		// DirectInput入力
			++mButtonInputState[i];
		}
		else {	// いずれの入力もない場合
			mButtonInputState[i] = 0;
		}
	}

	for (int i = 0; i < eDPad_TotalNum; i++) {
		switch (i) {
		case eDPad_Up:
			if (CheckHitKey(mDPadKeyAssign[i]) != 0) {
				++mDPadInputState[i];
			}
			else if (pPad->GetXInputFlag() &&
				(pPad->GetJoyPadInputState(eXInputAssign_LeftY) >= static_cast<int>(32766.0 * (static_cast<double>(mStickDeadZone) / 100.0)) + 1 || 
				pPad->GetJoyPadInputState(eXInputAssign_DPadUp) != 0)) {
				++mDPadInputState[i];
			}
			else if (!pPad->GetXInputFlag() &&
				(pPad->GetJoyPadInputState(eDirectInputAssign_Y) <= static_cast<int>(-999.0 * (static_cast<double>(mStickDeadZone) / 100.0)) - 1 ||
				pPad->GetJoyPadInputState(eDirectInputAssign_POV1) == 31500 ||
				pPad->GetJoyPadInputState(eDirectInputAssign_POV1) == 0 || 
				pPad->GetJoyPadInputState(eDirectInputAssign_POV1) == 4500)) {
				++mDPadInputState[i];
			}
			else {
				mDPadInputState[i] = 0;
			}
			break;
		case eDPad_Down:
			if (CheckHitKey(mDPadKeyAssign[i]) != 0) {
				++mDPadInputState[i];
			}
			else if (pPad->GetXInputFlag() &&
				(pPad->GetJoyPadInputState(eXInputAssign_LeftY) <= static_cast<int>(-32767.0 * (static_cast<double>(mStickDeadZone) / 100.0)) - 1 ||
					pPad->GetJoyPadInputState(eXInputAssign_DPadDown) != 0)) {
				++mDPadInputState[i];
			}
			else if (!pPad->GetXInputFlag() &&
				(pPad->GetJoyPadInputState(eDirectInputAssign_Y) >= static_cast<int>(999.0 * (static_cast<double>(mStickDeadZone) / 100.0)) + 1 ||
					pPad->GetJoyPadInputState(eDirectInputAssign_POV1) == 13500 ||
					pPad->GetJoyPadInputState(eDirectInputAssign_POV1) == 18000 ||
					pPad->GetJoyPadInputState(eDirectInputAssign_POV1) == 22500)) {
				++mDPadInputState[i];
			}
			else {
				mDPadInputState[i] = 0;
			}
			break;
		case eDPad_Left:
			if (CheckHitKey(mDPadKeyAssign[i]) != 0) {
				++mDPadInputState[i];
			}
			else if (pPad->GetXInputFlag() &&
				(pPad->GetJoyPadInputState(eXInputAssign_LeftX) <= static_cast<int>(-32767.0 * (static_cast<double>(mStickDeadZone) / 100.0)) - 1 ||
					pPad->GetJoyPadInputState(eXInputAssign_DPadLeft) != 0)) {
				++mDPadInputState[i];
			}
			else if (!pPad->GetXInputFlag() &&
				(pPad->GetJoyPadInputState(eDirectInputAssign_X) <= static_cast<int>(-999.0 * (static_cast<double>(mStickDeadZone) / 100.0)) - 1 ||
					pPad->GetJoyPadInputState(eDirectInputAssign_POV1) == 22500 ||
					pPad->GetJoyPadInputState(eDirectInputAssign_POV1) == 27000 ||
					pPad->GetJoyPadInputState(eDirectInputAssign_POV1) == 31500)) {
				++mDPadInputState[i];
			}
			else {
				mDPadInputState[i] = 0;
			}
			break;
		case eDPad_Right:
			if (CheckHitKey(mDPadKeyAssign[i]) != 0) {
				++mDPadInputState[i];
			}
			else if (pPad->GetXInputFlag() &&
				(pPad->GetJoyPadInputState(eXInputAssign_LeftX) >= static_cast<int>(32766.0 * (static_cast<double>(mStickDeadZone) / 100.0)) + 1 ||
					pPad->GetJoyPadInputState(eXInputAssign_DPadRight) != 0)) {
				++mDPadInputState[i];
			}
			else if (!pPad->GetXInputFlag() &&
				(pPad->GetJoyPadInputState(eDirectInputAssign_X) >= static_cast<int>(999.0 * (static_cast<double>(mStickDeadZone) / 100.0)) + 1 ||
					pPad->GetJoyPadInputState(eDirectInputAssign_POV1) == 4500 ||
					pPad->GetJoyPadInputState(eDirectInputAssign_POV1) == 9000 ||
					pPad->GetJoyPadInputState(eDirectInputAssign_POV1) == 13500)) {
				++mDPadInputState[i];
			}
			else {
				mDPadInputState[i] = 0;
			}
			break;
		}
	}
}

void cVirtualPad::Draw() {
	std::tstring tButtonAssign[eButton_TotalNum];
	std::tstring tDPadAssign[eDPad_TotalNum];

	tButtonAssign[eButton_Shot] = _T("Shot");
	tButtonAssign[eButton_Possess] = _T("Possess");
	tButtonAssign[eButton_Bomb] = _T("Bomb");
	tButtonAssign[eButton_FullAuto] = _T("FullAuto");
	tButtonAssign[eButton_Pause] = _T("Pause");
	tButtonAssign[eButton_Coin] = _T("Coin");
	tButtonAssign[eButton_Service] = _T("Service");

	tDPadAssign[eDPad_Up] = _T("Up");
	tDPadAssign[eDPad_Down] = _T("Down");
	tDPadAssign[eDPad_Left] = _T("Left");
	tDPadAssign[eDPad_Right] = _T("Right");

	for (int i = 0; i < eButton_TotalNum; i++) {
		DrawFormatString(0, 18 * i, GetColor(0xFF, 0xFF, 0xFF), _T("%s: %u"), tButtonAssign[i].c_str(), this->GetInputState(static_cast<eButtonAssign>(i)));
	}
	for (int i = 0; i < eDPad_TotalNum; i++) {
		DrawFormatString(0, 18 * (i + eButton_TotalNum + 1), GetColor(0xFF, 0xFF, 0xFF), _T("%s: %u"), tDPadAssign[i].c_str(), this->GetInputState(static_cast<eDPadAssign>(i)));
	}
}