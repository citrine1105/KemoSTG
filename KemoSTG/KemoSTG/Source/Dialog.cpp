#include "../Header/Dialog.h"

cDialog::cDialog() {
	this->Initialize();
}

cDialog::cDialog(const cStringResource Message) : mMessage(Message) {
	this->Initialize();
	mMessage = Message;
}

cDialog::~cDialog() {
	this->Finalize();
}

void cDialog::Show() {
	fActive = true;
}

void cDialog::Hide() {
	fActive = false;
}

void cDialog::Initialize() {
	mMessage.Initialize();
}

void cDialog::Initialize(const cStringResource Message, const eDialogIcon Icon) {
	this->Initialize();
	mMessage = Message;
	mIcon = Icon;
}

void cDialog::Finalize() {
	mMessage.Finalize();
	mIcon = eDialogIcon_None;
	fActive = false;
}

void cDialog::Update() {
	if (fActive) {
		// ここに処理を書いて
	}
}

void cDialog::Draw() {
	if (fActive) {
		// 処理書いて
	}
}

cOKDialog::cOKDialog() {
	this->Initialize();
}

cOKDialog::cOKDialog(const cStringResource Message) {
	this->Initialize();
	mMessage = Message;
}

cOKDialog::~cOKDialog() {
	this->Finalize();
}

bool cOKDialog::GetDecideFlag() {
	return fDecide;
}

void cOKDialog::Initialize() {
	cDialog::Initialize();
	fDecide = false;
}

void cOKDialog::Finalize() {
	cDialog::Finalize();
	fDecide = false;
}

void cOKDialog::Update() {
	cDialog::Update();
}

void cOKDialog::Draw() {

}

cTimerDialog::cTimerDialog() {
	cDialog::Initialize();
	this->Initialize();
}

cTimerDialog::~cTimerDialog() {
	cDialog::Finalize();
	this->Finalize();
}

void cTimerDialog::SetHideTime(const int Value) {
	mTimer.SetValue(Value);
	mTimer.SetDefaultValue(Value);
}

void cTimerDialog::SetHideTime(const double Second) {
	mTimer.SetSecond(Second);
	mTimer.SetDefaultSecond(Second);
}

void cTimerDialog::Show() {
	mTimer.SetDefaultValue(10);	// test
}

void cTimerDialog::Initialize() {
	cDialog::Initialize();
	mTimer.Initialize();
	mTimer.SetCountMode(eCountMode_CountDown);
}

void cTimerDialog::Finalize() {
	cDialog::Finalize();
	mTimer.Finalize();
}

void cTimerDialog::Update() {
	if (fActive) {
		cDialog::Update();
		mTimer.Update();
		if (mTimer.GetValue() <= 0) {
			this->Hide();
		}
	}
}

void cTimerDialog::Draw() {

}

cYesNoDialog::cYesNoDialog() {
	cDialog::Initialize();
	this->Initialize();
}

cYesNoDialog::~cYesNoDialog() {
	cDialog::Finalize();
	this->Finalize();
}

void cYesNoDialog::Initialize() {
	mYes.Initialize();
	mNo.Initialize();

	mYes.SetString(eLanguage_Japanese, _T("はい"));
	mYes.SetString(eLanguage_English, _T("Yes"));

	mNo.SetString(eLanguage_Japanese, _T("いいえ"));
	mNo.SetString(eLanguage_English, _T("No"));
}

void cYesNoDialog::Finalize() {
	mYes.Finalize();
	mNo.Finalize();
}