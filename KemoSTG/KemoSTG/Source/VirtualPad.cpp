#include "../Header/VirtualPad.h"

sVirtualPadInputState::sVirtualPadInputState() {
	mButton.fill(false);
	mDPad.fill(false);
}

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
		mKeyAssign.at(eButton_Shot) = KEY_INPUT_COMMA;
		mKeyAssign.at(eButton_Possess) = KEY_INPUT_PERIOD;
		mKeyAssign.at(eButton_Bomb) = KEY_INPUT_SLASH;
		mKeyAssign.at(eButton_FullAuto) = KEY_INPUT_RSHIFT;
		mKeyAssign.at(eButton_Pause) = KEY_INPUT_2;
		mKeyAssign.at(eButton_Coin) = KEY_INPUT_6;
		mKeyAssign.at(eButton_Service) = KEY_INPUT_0;

		mDPadKeyAssign.at(eDPad_Up) = KEY_INPUT_W;
		mDPadKeyAssign.at(eDPad_Down) = KEY_INPUT_S;
		mDPadKeyAssign.at(eDPad_Left) = KEY_INPUT_A;
		mDPadKeyAssign.at(eDPad_Right) = KEY_INPUT_D;
		break;
	default:
		mKeyAssign.at(eButton_Shot) = KEY_INPUT_Z;
		mKeyAssign.at(eButton_Possess) = KEY_INPUT_X;
		mKeyAssign.at(eButton_Bomb) = KEY_INPUT_C;
		mKeyAssign.at(eButton_FullAuto) = KEY_INPUT_LSHIFT;
		mKeyAssign.at(eButton_Pause) = KEY_INPUT_1;
		mKeyAssign.at(eButton_Coin) = KEY_INPUT_5;
		mKeyAssign.at(eButton_Service) = KEY_INPUT_9;
		mKeyAssign.at(eButton_Decide) = KEY_INPUT_Z;
		mKeyAssign.at(eButton_Cancel) = KEY_INPUT_X;

		mDPadKeyAssign.at(eDPad_Up) = KEY_INPUT_UP;
		mDPadKeyAssign.at(eDPad_Down) = KEY_INPUT_DOWN;
		mDPadKeyAssign.at(eDPad_Left) = KEY_INPUT_LEFT;
		mDPadKeyAssign.at(eDPad_Right) = KEY_INPUT_RIGHT;
		break;
	}

	mDirectInputAssign.at(eButton_Shot) = eDirectInputAssign_Button1;
	mDirectInputAssign.at(eButton_Possess) = eDirectInputAssign_Button2;
	mDirectInputAssign.at(eButton_Bomb) = eDirectInputAssign_Button3;
	mDirectInputAssign.at(eButton_FullAuto) = eDirectInputAssign_Button4;
	mDirectInputAssign.at(eButton_Pause) = eDirectInputAssign_Button5;
	mDirectInputAssign.at(eButton_Coin) = eDirectInputAssign_Button6;
	mDirectInputAssign.at(eButton_Service) = eDirectInputAssign_Button7;
	mDirectInputAssign.at(eButton_Decide) = eDirectInputAssign_Button1;
	mDirectInputAssign.at(eButton_Cancel) = eDirectInputAssign_Button2;

	mXInputAssign.at(eButton_Shot) = eXInputAssign_A;
	mXInputAssign.at(eButton_Possess) = eXInputAssign_B;
	mXInputAssign.at(eButton_Bomb) = eXInputAssign_Y;
	mXInputAssign.at(eButton_FullAuto) = eXInputAssign_RT;
	mXInputAssign.at(eButton_Pause) = eXInputAssign_Start;
	mXInputAssign.at(eButton_Coin) = eXInputAssign_LeftStickButton;
	mXInputAssign.at(eButton_Service) = eXInputAssign_RightStickButton;
	mXInputAssign.at(eButton_Decide) = eXInputAssign_A;
	mXInputAssign.at(eButton_Cancel) = eXInputAssign_B;

	mStickDeadZone = 50;
	fVibration = true;
}

void cVirtualPad::SetJoyPad(cPad *Pad) {
	pPad = Pad;
}

void cVirtualPad::SetKeyAssign(const eButtonAssign Assign, const unsigned char Key) {
	int i, j;
	for (i = 0; i < eButton_TotalNum; i++) {
		if (mKeyAssign.at(i) == Key) {	// 既に同じ割り当てのキーがあるか探索
			break;
		}
	}
	for (j = 0; j < eDPad_TotalNum; j++) {
		if (mDPadKeyAssign.at(j) == Key) {	// 既に同じ割り当てのキーがあるか探索
			break;
		}
	}
	if (i < eButton_TotalNum) {	// ある場合
		mKeyAssign.at(i) = mKeyAssign.at(Assign);	// 入れ替え
		mKeyAssign.at(Assign) = Key;
	}
	else if (j < eDPad_TotalNum) {
		mDPadKeyAssign.at(j) = mKeyAssign.at(Assign);	// 入れ替え
		mKeyAssign.at(Assign) = Key;
	}
	else {						// ない場合
		mKeyAssign.at(Assign) = Key;	// 設定
	}
}

void cVirtualPad::SetKeyAssign(const eDPadAssign Assign, const unsigned char Key) {
	int i, j;
	for (i = 0; i < eButton_TotalNum; i++) {
		if (mKeyAssign.at(i) == Key) {	// 既に同じ割り当てのキーがあるか探索
			break;
		}
	}
	for (j = 0; j < eDPad_TotalNum; j++) {
		if (mDPadKeyAssign.at(j) == Key) {	// 既に同じ割り当てのキーがあるか探索
			break;
		}
	}
	if (i < eButton_TotalNum) {	// ある場合
		mKeyAssign.at(i) = mDPadKeyAssign.at(Assign);	// 入れ替え
		mDPadKeyAssign.at(Assign) = Key;
	}
	else if (j < eDPad_TotalNum) {
		mDPadKeyAssign.at(j) = mDPadKeyAssign.at(Assign);	// 入れ替え
		mDPadKeyAssign.at(Assign) = Key;
	}
	else {						// ない場合
		mKeyAssign.at(Assign) = Key;	// 設定
	}
}

void cVirtualPad::SetButtonAssign(const eButtonAssign Assign, const eDirectInputAssign Button) {
	int i;
	for (i = 0; i < eButton_TotalNum; i++) {
		if (mDirectInputAssign.at(i) == Button) {	// 既に同じ割り当てのボタンがあるか探索
			break;
		}
	}
	if (i < eButton_TotalNum) {	// ある場合
		mDirectInputAssign.at(i) = mDirectInputAssign.at(Assign);	// 入れ替え
		mDirectInputAssign.at(Assign) = Button;
	}
	else {						// ない場合
		mDirectInputAssign.at(Assign) = Button;	// 設定
	}
}

void cVirtualPad::SetButtonAssign(const eButtonAssign Assign, const eXInputAssign Button) {
	int i;
	for (i = 0; i < eButton_TotalNum; i++) {
		if (mXInputAssign.at(i) == Button) {	// 既に同じ割り当てのボタンがあるか探索
			break;
		}
	}
	if (i < eButton_TotalNum) {	// ある場合
		mXInputAssign.at(i) = mXInputAssign.at(Assign);	// 入れ替え
		mXInputAssign.at(Assign) = Button;
	}
	else {						// ない場合
		mXInputAssign.at(Assign) = Button;	// 設定
	}
}

void cVirtualPad::SetVibrationFlag(const bool Flag) {
	fVibration = Flag;
}

void cVirtualPad::SetButtonState(const sVirtualPadInputState &State) {
	mButtonState = State;
}

cPad* cVirtualPad::GetJoyPad() {
	return pPad;
}

unsigned AUTO_INT cVirtualPad::GetInputState(const eButtonAssign Button) {
	return mButtonInputState.at(Button);
}

unsigned AUTO_INT cVirtualPad::GetInputState(const eDPadAssign Button) {
	return mDPadInputState.at(Button);
}

unsigned char cVirtualPad::GetKeyAssign(const eButtonAssign Assign) {
	return mKeyAssign.at(Assign);
}

unsigned char cVirtualPad::GetKeyAssign(const eDPadAssign Assign) {
	return mDPadKeyAssign.at(Assign);
}

eDirectInputAssign cVirtualPad::GetDirectInputAssign(const eButtonAssign Assign) {
	return mDirectInputAssign.at(Assign);
}

eXInputAssign cVirtualPad::GetXInputAssign(const eButtonAssign Assign) {
	return mXInputAssign.at(Assign);
}

bool cVirtualPad::GetVibrationFlag() {
	if (pPad->GetActiveFlag() && pPad->GetXInputFlag()) {
		return fVibration;
	}
	else {
		return false;
	}
}

const sVirtualPadInputState cVirtualPad::GetButtonState() {
	return mButtonState;
}

void cVirtualPad::StartVibration(const int Power, const int Time) {
	if (this->GetVibrationFlag()) {
		StartJoypadVibration(this->GetJoyPad()->GetJoyPadNum(), Power, Time);
	}
}

void cVirtualPad::StopVibration() {
	if (pPad != nullptr) {
		StopJoypadVibration(this->GetJoyPad()->GetJoyPadNum());
	}
}

void cVirtualPad::ResetInputState() {
	for (int i = 0; i < eButton_TotalNum; i++) {
		mButtonInputState.at(i) = 0;
	}
	for (int i = 0; i < eDPad_TotalNum; i++) {
		mDPadInputState.at(i) = 0;
	}
}

void cVirtualPad::Initialize() {
	pPad = nullptr;
	this->StopVibration();
	this->SetDefaultAssign();
	this->ResetInputState();
}

void cVirtualPad::Finalize() {
	this->StopVibration();
	pPad = nullptr;
	this->SetDefaultAssign();
	this->ResetInputState();
}

void cVirtualPad::Update() {
	if (pPad != nullptr) {
		pPad->Update();

		for (int i = 0; i < eButton_TotalNum; i++) {
			if (cKeyboard::GetInstance()->GetKeyPushState(mKeyAssign.at(i)) != 0) {	// キーボード入力
				mButtonState.mButton.at(i) = true;
			}
			else if (pPad->GetXInputFlag() &&
				(mXInputAssign.at(i) == eXInputAssign_LT || mXInputAssign.at(i) == eXInputAssign_RT) &&
				pPad->GetJoyPadInputState(mXInputAssign.at(i)) >= static_cast<int>(254.0 * (static_cast<double>(mStickDeadZone) / 100.0)) + 1) {	// LTかRTに割り当てられている場合
				mButtonState.mButton.at(i) = true;
			}
			else if (pPad->GetXInputFlag() &&
				mXInputAssign.at(i) != eXInputAssign_LT && mXInputAssign.at(i) != eXInputAssign_RT &&
				pPad->GetJoyPadInputState(mXInputAssign.at(i)) != 0) {		// XInput入力
				mButtonState.mButton.at(i) = true;
			}
			else if (!pPad->GetXInputFlag() &&
				pPad->GetJoyPadInputState(mDirectInputAssign.at(i)) != 0) {		// DirectInput入力
				mButtonState.mButton.at(i) = true;
			}
			else {	// いずれの入力もない場合
				mButtonState.mButton.at(i) = false;
			}
		}

		for (int i = 0; i < eDPad_TotalNum; i++) {
			switch (i) {
			case eDPad_Up:
				if (cKeyboard::GetInstance()->GetKeyPushState(mDPadKeyAssign.at(i)) != 0) {
					mButtonState.mDPad.at(i) = true;
				}
				else if (pPad->GetXInputFlag() &&
					(pPad->GetJoyPadInputState(eXInputAssign_LeftY) >= static_cast<int>(32766.0 * (static_cast<double>(mStickDeadZone) / 100.0)) + 1 ||
						pPad->GetJoyPadInputState(eXInputAssign_DPadUp) != 0)) {
					mButtonState.mDPad.at(i) = true;
				}
				else if (!pPad->GetXInputFlag() &&
					(pPad->GetJoyPadInputState(eDirectInputAssign_Y) <= static_cast<int>(-999.0 * (static_cast<double>(mStickDeadZone) / 100.0)) - 1 ||
						pPad->GetJoyPadInputState(eDirectInputAssign_POV1) == 31500 ||
						pPad->GetJoyPadInputState(eDirectInputAssign_POV1) == 0 ||
						pPad->GetJoyPadInputState(eDirectInputAssign_POV1) == 4500)) {
					mButtonState.mDPad.at(i) = true;
				}
				else {
					mButtonState.mDPad.at(i) = false;
				}
				break;
			case eDPad_Down:
				if (cKeyboard::GetInstance()->GetKeyPushState(mDPadKeyAssign.at(i)) != 0) {
					mButtonState.mDPad.at(i) = true;
				}
				else if (pPad->GetXInputFlag() &&
					(pPad->GetJoyPadInputState(eXInputAssign_LeftY) <= static_cast<int>(-32767.0 * (static_cast<double>(mStickDeadZone) / 100.0)) - 1 ||
						pPad->GetJoyPadInputState(eXInputAssign_DPadDown) != 0)) {
					mButtonState.mDPad.at(i) = true;
				}
				else if (!pPad->GetXInputFlag() &&
					(pPad->GetJoyPadInputState(eDirectInputAssign_Y) >= static_cast<int>(999.0 * (static_cast<double>(mStickDeadZone) / 100.0)) + 1 ||
						pPad->GetJoyPadInputState(eDirectInputAssign_POV1) == 13500 ||
						pPad->GetJoyPadInputState(eDirectInputAssign_POV1) == 18000 ||
						pPad->GetJoyPadInputState(eDirectInputAssign_POV1) == 22500)) {
					mButtonState.mDPad.at(i) = true;
				}
				else {
					mButtonState.mDPad.at(i) = false;
				}
				break;
			case eDPad_Left:
				if (cKeyboard::GetInstance()->GetKeyPushState(mDPadKeyAssign.at(i)) != 0) {
					mButtonState.mDPad.at(i) = true;
				}
				else if (pPad->GetXInputFlag() &&
					(pPad->GetJoyPadInputState(eXInputAssign_LeftX) <= static_cast<int>(-32767.0 * (static_cast<double>(mStickDeadZone) / 100.0)) - 1 ||
						pPad->GetJoyPadInputState(eXInputAssign_DPadLeft) != 0)) {
					mButtonState.mDPad.at(i) = true;
				}
				else if (!pPad->GetXInputFlag() &&
					(pPad->GetJoyPadInputState(eDirectInputAssign_X) <= static_cast<int>(-999.0 * (static_cast<double>(mStickDeadZone) / 100.0)) - 1 ||
						pPad->GetJoyPadInputState(eDirectInputAssign_POV1) == 22500 ||
						pPad->GetJoyPadInputState(eDirectInputAssign_POV1) == 27000 ||
						pPad->GetJoyPadInputState(eDirectInputAssign_POV1) == 31500)) {
					mButtonState.mDPad.at(i) = true;
				}
				else {
					mButtonState.mDPad.at(i) = false;
				}
				break;
			case eDPad_Right:
				if (cKeyboard::GetInstance()->GetKeyPushState(mDPadKeyAssign.at(i)) != 0) {
					mButtonState.mDPad.at(i) = true;
				}
				else if (pPad->GetXInputFlag() &&
					(pPad->GetJoyPadInputState(eXInputAssign_LeftX) >= static_cast<int>(32766.0 * (static_cast<double>(mStickDeadZone) / 100.0)) + 1 ||
						pPad->GetJoyPadInputState(eXInputAssign_DPadRight) != 0)) {
					mButtonState.mDPad.at(i) = true;
				}
				else if (!pPad->GetXInputFlag() &&
					(pPad->GetJoyPadInputState(eDirectInputAssign_X) >= static_cast<int>(999.0 * (static_cast<double>(mStickDeadZone) / 100.0)) + 1 ||
						pPad->GetJoyPadInputState(eDirectInputAssign_POV1) == 4500 ||
						pPad->GetJoyPadInputState(eDirectInputAssign_POV1) == 9000 ||
						pPad->GetJoyPadInputState(eDirectInputAssign_POV1) == 13500)) {
					mButtonState.mDPad.at(i) = true;
				}
				else {
					mButtonState.mDPad.at(i) = false;
				}
				break;
			}
		}
	}

	for (int i = 0; i < eButton_TotalNum; i++) {
		if (mButtonState.mButton.at(i)) {
			mButtonInputState.at(i)++;
		}
		else {
			mButtonInputState.at(i) = 0;
		}
	}

	for (int i = 0; i < eDPad_TotalNum; i++) {
		if (mButtonState.mDPad.at(i)) {
			mDPadInputState.at(i)++;
		}
		else {
			mDPadInputState.at(i) = 0;
		}
	}
}

void cVirtualPad::Draw() {
	std::array<std::tstring, eButton_TotalNum> tButtonAssign;
	std::array<std::tstring, eDPad_TotalNum> tDPadAssign;

	tButtonAssign.at(eButton_Shot) = _T("Shot");
	tButtonAssign.at(eButton_Possess) = _T("Possess");
	tButtonAssign.at(eButton_Bomb) = _T("Bomb");
	tButtonAssign.at(eButton_FullAuto) = _T("FullAuto");
	tButtonAssign.at(eButton_Pause) = _T("Pause");
	tButtonAssign.at(eButton_Coin) = _T("Coin");
	tButtonAssign.at(eButton_Service) = _T("Service");

	tDPadAssign.at(eDPad_Up) = _T("Up");
	tDPadAssign.at(eDPad_Down) = _T("Down");
	tDPadAssign.at(eDPad_Left) = _T("Left");
	tDPadAssign.at(eDPad_Right) = _T("Right");

	for (int i = 0; i < eButton_TotalNum; i++) {
		DrawFormatString(0, 18 * i, GetColor(0xFF, 0xFF, 0xFF), _T("%s: %u"), tButtonAssign.at(i).c_str(), this->GetInputState(static_cast<eButtonAssign>(i)));
	}
	for (int i = 0; i < eDPad_TotalNum; i++) {
		DrawFormatString(0, 18 * (i + eButton_TotalNum + 1), GetColor(0xFF, 0xFF, 0xFF), _T("%s: %u"), tDPadAssign.at(i).c_str(), this->GetInputState(static_cast<eDPadAssign>(i)));
	}
}