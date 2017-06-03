#include "../Header/Timer.h"

cTimer::cTimer() : mValue(0), mDefaultValue(0), 
	mCountMode(eCountMode_CountUp), fActive(false) {

}

cTimer::cTimer(const AUTO_INT Value) : mValue(Value), mDefaultValue(Value),
	mCountMode(eCountMode_CountUp), fActive(false) {

}

cTimer::cTimer(const double Second) : mValue(static_cast<AUTO_INT>(Second * 60.0)), mDefaultValue(static_cast<AUTO_INT>(Second * 60.0)),
	mCountMode(eCountMode_CountUp), fActive(false) {

}

cTimer::cTimer(const AUTO_INT Value, const eCountMode CountMode) : mValue(Value), mDefaultValue(Value),
	mCountMode(eCountMode_CountUp), fActive(false) {

}

cTimer::cTimer(const double Second, const eCountMode CountMode) : mValue(static_cast<AUTO_INT>(Second * 60.0)), mDefaultValue(static_cast<AUTO_INT>(Second * 60.0)),
	mCountMode(CountMode), fActive(false) {

}

cTimer::~cTimer() {
	this->Finalize();
}

void cTimer::SetValue(const AUTO_INT Value) {
	mValue = Value;
}

void cTimer::SetSecond(const double Second) {
	mValue = static_cast<AUTO_INT>(Second * 60.0);
}

void cTimer::SetDefaultValue(const AUTO_INT Value) {
	mDefaultValue = Value;
}

void cTimer::SetDefaultSecond(const double Second) {
	mDefaultValue = static_cast<AUTO_INT>(Second * 60.0);
}

void cTimer::SetCountMode(const eCountMode Mode) {
	mCountMode = Mode;
}

void cTimer::AddValue(const AUTO_INT Value) {
	mValue += Value;
}

void cTimer::AddSecond(const double Second) {
	mValue += static_cast<AUTO_INT>(Second * 60.0);
}

AUTO_INT cTimer::GetValue() {
	return mValue;
}

double cTimer::GetSecond() {
	return static_cast<double>(mValue) / 60.0;
}

eCountMode cTimer::GetCountMode() {
	return mCountMode;
}

bool cTimer::GetActiveFlag() {
	return fActive;
}

void cTimer::operator = (const AUTO_INT Value) {
	this->SetValue(Value);
}

void cTimer::operator = (const double Second) {
	this->SetSecond(Second);
}

void cTimer::operator += (const AUTO_INT Value) {
	this->AddValue(Value);
}

void cTimer::operator += (const double Second) {
	this->AddSecond(Second);
}

void cTimer::operator -= (const AUTO_INT Value) {
	this->AddValue(-Value);
}

void cTimer::operator -= (const double Second) {
	this->AddSecond(-Second);
}

void cTimer::Start() {
	fActive = true;
}

void cTimer::Stop() {
	fActive = false;
}

void cTimer::Reset() {
	mValue = mDefaultValue;
}

void cTimer::Initialize() {
	mValue = 0;
	mDefaultValue = 0;
	mCountMode = eCountMode_CountUp;
	fActive = false;
}

void cTimer::Finalize() {
	mValue = 0;
	fActive = false;
}

void cTimer::Update() {
	if (fActive) {
		switch (mCountMode) {
		case eCountMode_CountUp:
			++mValue;
			break;
		case eCountMode_CountDown:
			--mValue;
			break;
		}
	}
}

void cTimer::Draw() {
	
}