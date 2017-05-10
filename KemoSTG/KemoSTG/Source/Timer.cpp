#include "../Header/Timer.h"

cTimer::cTimer() : mValue(0), mDefaultValue(0), 
	fActive(false), mCountMode(eCountMode_CountUp) {

}

cTimer::cTimer(AUTO_INT Value) : mValue(Value), mDefaultValue(Value), 
	fActive(false), mCountMode(eCountMode_CountUp) {

}

cTimer::cTimer(double Second) : mValue(static_cast<AUTO_INT>(Second * 60.0)), mDefaultValue(static_cast<AUTO_INT>(Second * 60.0)),
	fActive(false), mCountMode(eCountMode_CountUp) {

}

cTimer::cTimer(AUTO_INT Value, eCountMode CountMode) : mValue(Value), mDefaultValue(Value),
	fActive(false), mCountMode(eCountMode_CountUp) {

}

cTimer::cTimer(double Second, eCountMode CountMode) : mValue(static_cast<AUTO_INT>(Second * 60.0)), mDefaultValue(static_cast<AUTO_INT>(Second * 60.0)),
	fActive(false), mCountMode(CountMode) {

}

void cTimer::SetValue(AUTO_INT Value) {
	mValue = Value;
}

void cTimer::SetSecond(double Second) {
	mValue = static_cast<AUTO_INT>(Second * 60.0);
}

void cTimer::SetDefaultValue(AUTO_INT Value) {
	mDefaultValue = Value;
}

void cTimer::SetCountMode(eCountMode Mode) {
	mCountMode = Mode;
}

void cTimer::EnableLoopCount(bool Flag) {
	fLoopCount = Flag;
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

void cTimer::Start() {
	fActive = true;
}

void cTimer::Stop() {
	fActive = false;
}

void cTimer::Reset() {
	mValue = mDefaultValue;
}

void cTimer::Update() {
	if (fActive) {
		switch (mCountMode) {
		case eCountMode_CountUp:
			mValue++;
			break;
		case eCountMode_CountDown:
			mValue--;
			break;
		}
	}
}

void cTimer::Draw() {
	
}