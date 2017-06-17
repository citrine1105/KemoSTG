#include "../Header/Pad.h"

cPad::cPad() {
	this->Initialize();
}

cPad::cPad(const int PadNum) {
	this->Initialize();
	this->SetJoyPadNum(PadNum);
}

cPad::~cPad() {
	this->Finalize();
}

void cPad::SetJoyPadNum(const int PadNum) {
	TCHAR *tInstanceBuffer = new TCHAR[256];
	TCHAR *tProductBuffer = new TCHAR[256];
	mPadNumber = PadNum;
	fXInput = CheckJoypadXInput(mPadNumber);
	GetJoypadName(mPadNumber, tInstanceBuffer, tProductBuffer);
	mInstanceName = tInstanceBuffer;
	mProductName = tProductBuffer;
}

int cPad::GetJoyPadNum() {
	return mPadNumber;
}

std::tstring cPad::GetJoyPadInstanceName() {
	return mInstanceName;
}

std::tstring cPad::GetJoyPadProductName() {
	return mProductName;
}

bool cPad::GetXInputFlag() {
	return fXInput;
}

int cPad::GetJoyPadInputState(eDirectInputAssign Assign) {
	switch (Assign) {
	case eDirectInputAssign_Button1:
	case eDirectInputAssign_Button2:
	case eDirectInputAssign_Button3:
	case eDirectInputAssign_Button4:
	case eDirectInputAssign_Button5:
	case eDirectInputAssign_Button6:
	case eDirectInputAssign_Button7:
	case eDirectInputAssign_Button8:
	case eDirectInputAssign_Button9:
	case eDirectInputAssign_Button10:
	case eDirectInputAssign_Button11:
	case eDirectInputAssign_Button12:
	case eDirectInputAssign_Button13:
	case eDirectInputAssign_Button14:
	case eDirectInputAssign_Button15:
	case eDirectInputAssign_Button16:
	case eDirectInputAssign_Button17:
	case eDirectInputAssign_Button18:
	case eDirectInputAssign_Button19:
	case eDirectInputAssign_Button20:
	case eDirectInputAssign_Button21:
	case eDirectInputAssign_Button22:
	case eDirectInputAssign_Button23:
	case eDirectInputAssign_Button24:
	case eDirectInputAssign_Button25:
	case eDirectInputAssign_Button26:
	case eDirectInputAssign_Button27:
	case eDirectInputAssign_Button28:
	case eDirectInputAssign_Button29:
	case eDirectInputAssign_Button30:
	case eDirectInputAssign_Button31:
	case eDirectInputAssign_Button32:
		return mDirectInputState.Buttons[static_cast<int>(Assign)];
		break;
	case eDirectInputAssign_X:
		return mDirectInputState.X;
		break;
	case eDirectInputAssign_Y:
		return mDirectInputState.Y;
		break;
	case eDirectInputAssign_Z:
		return mDirectInputState.Z;
		break;
	case eDirectInputAssign_Rx:
		return mDirectInputState.Rx;
		break;
	case eDirectInputAssign_Ry:
		return mDirectInputState.Ry;
		break;
	case eDirectInputAssign_Rz:
		return mDirectInputState.Rz;
		break;
	case eDirectInputAssign_POV1:
		return mDirectInputState.POV[0];
		break;
	case eDirectInputAssign_POV2:
		return mDirectInputState.POV[1];
		break;
	case eDirectInputAssign_POV3:
		return mDirectInputState.POV[2];
		break;
	case eDirectInputAssign_POV4:
		return mDirectInputState.POV[3];
		break;
	case eDirectInputAssign_Slider1:
		return mDirectInputState.Slider[0];
		break;
	case eDirectInputAssign_Slider2:
		return mDirectInputState.Slider[1];
		break;
	default:
		return 0;
		break;
	}
}

int cPad::GetJoyPadInputState(eXInputAssign Assign) {
	switch (Assign) {
	case eXInputAssign_LeftX:
		return mXInputState.ThumbLX;
		break;
	case eXInputAssign_LeftY:
		return mXInputState.ThumbLY;
		break;
	case eXInputAssign_RightX:
		return mXInputState.ThumbRX;
		break;
	case eXInputAssign_RightY:
		return mXInputState.ThumbRY;
		break;
	case eXInputAssign_LT:
		return mXInputState.LeftTrigger;
		break;
	case eXInputAssign_RT:
		return mXInputState.RightTrigger;
		break;
	case eXInputAssign_DPadUp:
		return mXInputState.Buttons[XINPUT_BUTTON_DPAD_UP];
		break;
	case eXInputAssign_DPadDown:
		return mXInputState.Buttons[XINPUT_BUTTON_DPAD_DOWN];
		break;
	case eXInputAssign_DPadLeft:
		return mXInputState.Buttons[XINPUT_BUTTON_DPAD_LEFT];
		break;
	case eXInputAssign_DPadRight:
		return mXInputState.Buttons[XINPUT_BUTTON_DPAD_RIGHT];
		break;
	case eXInputAssign_Start:
		return mXInputState.Buttons[XINPUT_BUTTON_START];
		break;
	case eXInputAssign_Back:
		return mXInputState.Buttons[XINPUT_BUTTON_BACK];
		break;
	case eXInputAssign_LeftStickButton:
		return mXInputState.Buttons[XINPUT_BUTTON_LEFT_THUMB];
		break;
	case eXInputAssign_RightStickButton:
		return mXInputState.Buttons[XINPUT_BUTTON_RIGHT_THUMB];
		break;
	case eXInputAssign_LB:
		return mXInputState.Buttons[XINPUT_BUTTON_LEFT_SHOULDER];
		break;
	case eXInputAssign_RB:
		return mXInputState.Buttons[XINPUT_BUTTON_RIGHT_SHOULDER];
		break;
	case eXInputAssign_A:
		return mXInputState.Buttons[XINPUT_BUTTON_A];
		break;
	case eXInputAssign_B:
		return mXInputState.Buttons[XINPUT_BUTTON_B];
		break;
	case eXInputAssign_X:
		return mXInputState.Buttons[XINPUT_BUTTON_X];
		break;
	case eXInputAssign_Y:
		return mXInputState.Buttons[XINPUT_BUTTON_Y];
		break;
	default:
		return 0;
		break;
	}
}


void cPad::ResetInputState() {
	for (int i = XINPUT_BUTTON_DPAD_UP; i <= XINPUT_BUTTON_Y; i++) {
		mXInputState.Buttons[i] = 0;
	}
	for (int i = 0; i < 32; i++) {
		mDirectInputState.Buttons[i] = 0;
	}
	mDirectInputState.X = 0;
	mDirectInputState.Y = 0;
	mDirectInputState.Z = 0;
	mDirectInputState.Rx = 0;
	mDirectInputState.Ry = 0;
	mDirectInputState.Rz = 0;
	for (int i = 0; i < 4; i++) {
		mDirectInputState.POV[i] = 0xFFFFFFFF;
	}
	mDirectInputState.Slider[0] = 0;
	mDirectInputState.Slider[1] = 0;
}

void cPad::Initialize() {
	mPadNumber = NULL;
	mInstanceName.clear();
	mProductName.clear();
	this->ResetInputState();
}

void cPad::Finalize() {
	mPadNumber = NULL;
	mInstanceName.clear();
	mProductName.clear();
	this->ResetInputState();
}

void cPad::Update() {
	fXInput ? GetJoypadXInputState(mPadNumber, &mXInputState) : GetJoypadDirectInputState(mPadNumber, &mDirectInputState);
}

void cPad::Draw() {
	if (this->GetXInputFlag()) {
		for (int i = 0; i < static_cast<int>(eXInputAssign_TotalNum); i++) {
			DrawFormatString(0, 18 * i + 36, GetColor(0xFF, 0xFF, 0xFF), _T("%d"), this->GetJoyPadInputState(static_cast<eXInputAssign>(i)));
		}
	}
	else {
		for (int i = 0; i < 22; i++) {
			DrawFormatString(0, 18 * i + 36, GetColor(0xFF, 0xFF, 0xFF), _T("%d"), this->GetJoyPadInputState(static_cast<eDirectInputAssign>(i)));
			DrawFormatString(320, 18 * i + 36, GetColor(0xFF, 0xFF, 0xFF), _T("%d"), this->GetJoyPadInputState(static_cast<eDirectInputAssign>(i + 22)));
		}
	}
	DrawString(0, 0, this->GetJoyPadInstanceName().c_str(), GetColor(0xFF, 0x00, 0x00));
	DrawString(0, 18, this->GetJoyPadProductName().c_str(), GetColor(0xFF, 0x00, 0x00));
}