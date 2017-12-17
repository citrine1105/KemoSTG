#include "../Header/Timer.h"

cTimer::cTimer() : mTime(0), mDefaultTime(0), mMaxTime(AUTO_INT_MAX), 
	mCountMode(eCountMode_CountUp), fActive(false), fLoop(false) {

}

//cTimer::cTimer(const AUTO_INT Time) : mTime(Time), mDefaultTime(Time), mMaxTime(AUTO_INT_MAX),
//mCountMode(eCountMode_CountUp), fActive(false), fLoop(false) {
//
//}
//
//cTimer::cTimer(const double Second) : mTime(static_cast<int>(Second * REFRESH_RATE)), mDefaultTime(0), mMaxTime(AUTO_INT_MAX),
//mCountMode(eCountMode_CountUp), fActive(false), fLoop(false) {
//
//}
//
//cTimer::cTimer(const AUTO_INT Time, const eCountMode CountMode) : mTime(Time), mDefaultTime(Time),
//	mCountMode(eCountMode_CountUp), fActive(false) {
//
//}
//
//cTimer::cTimer(const double Second, const eCountMode CountMode) : mTime(static_cast<AUTO_INT>(Second * REFRESH_RATE)), mDefaultTime(static_cast<AUTO_INT>(Second * REFRESH_RATE)),
//	mCountMode(CountMode), fActive(false) {
//
//}

cTimer::cTimer(const AUTO_INT Time, const AUTO_INT MaxTime, const eCountMode CountMode, const bool Loop) {
	this->Initialize(Time, MaxTime, CountMode, Loop);
}

cTimer::cTimer(const double Second, const double MaxSecond, const eCountMode CountMode, const bool Loop) {
	this->Initialize(Second, MaxSecond, CountMode, Loop);
}

cTimer::~cTimer() {
	this->Finalize();
}

void cTimer::SetTime(const AUTO_INT Time) {
	mTime = Time;
}

void cTimer::SetSecond(const double Second) {
	mTime = static_cast<AUTO_INT>(Second * REFRESH_RATE);
}

void cTimer::SetDefaultTime(const AUTO_INT Time) {
	mDefaultTime = Time;
}

void cTimer::SetDefaultSecond(const double Second) {
	mDefaultTime = static_cast<AUTO_INT>(Second * REFRESH_RATE);
}

void cTimer::SetMaxTime(const AUTO_INT MaxTime) {
	mMaxTime = MaxTime;
}

void cTimer::SetMaxSecond(const double MaxSecond) {
	mMaxTime = static_cast<AUTO_INT>(MaxSecond * REFRESH_RATE);
}

void cTimer::SetCountMode(const eCountMode Mode) {
	mCountMode = Mode;
}

void cTimer::SetLoopFlag(const bool Flag) {
	fLoop = Flag;
}

void cTimer::AddTime(const AUTO_INT Time) {
	mTime += Time;
}

void cTimer::AddSecond(const double Second) {
	mTime += static_cast<AUTO_INT>(Second * REFRESH_RATE);
}

AUTO_INT cTimer::GetTime() {
	return mTime;
}

double cTimer::GetSecond() {
	return static_cast<double>(mTime) / REFRESH_RATE;
}

AUTO_INT cTimer::GetMaxTime() {
	return mMaxTime;
}

double cTimer::GetMaxSecond() {
	return static_cast<double>(mMaxTime) / REFRESH_RATE;
}

eCountMode cTimer::GetCountMode() {
	return mCountMode;
}

bool cTimer::GetActiveFlag() {
	return fActive;
}

void cTimer::operator=(const AUTO_INT Time) {
	this->SetTime(Time);
}

void cTimer::operator=(const double Second) {
	this->SetSecond(Second);
}

void cTimer::operator+=(const AUTO_INT Time) {
	this->AddTime(Time);
}

void cTimer::operator+=(const double Second) {
	this->AddSecond(Second);
}

void cTimer::operator-=(const AUTO_INT Time) {
	this->AddTime(-Time);
}

void cTimer::operator-=(const double Second) {
	this->AddSecond(-Second);
}

void cTimer::Start() {
	fActive = true;
}

void cTimer::Stop() {
	fActive = false;
}

void cTimer::Reset() {
	mTime = mDefaultTime;
}

void cTimer::Initialize() {
	mTime = 0;
	mDefaultTime = 0;
	mMaxTime = AUTO_INT_MAX;
	mCountMode = eCountMode_CountUp;
	fActive = false;
	fLoop = false;
}

void cTimer::Initialize(const AUTO_INT Time, const AUTO_INT MaxTime, const eCountMode CountMode, const bool Loop) {
	mTime = Time;
	mDefaultTime = Time;
	mMaxTime = MaxTime;
	mCountMode = CountMode;
	fActive = false;
	fLoop = Loop;
}

void cTimer::Initialize(const double Second, const double MaxSecond, const eCountMode CountMode, const bool Loop) {
	mTime = static_cast<AUTO_INT>(Second * REFRESH_RATE);
	mDefaultTime = static_cast<AUTO_INT>(Second * REFRESH_RATE);
	mMaxTime = static_cast<AUTO_INT>(MaxSecond * REFRESH_RATE);
	mCountMode = CountMode;
	fActive = false;
	fLoop = Loop;
}

void cTimer::Finalize() {
	mTime = 0;
	fActive = false;
}

void cTimer::Update() {
	if (fActive) {
	}
	switch (mCountMode) {
	case eCountMode_CountUp:
		if (fActive) {
			++mTime;
		}
		if (mTime >= mMaxTime) {
			if (fLoop) {
				mTime = 0;
			}
			else {
				this->Stop();

			}
		}
		break;
	case eCountMode_CountDown:
		if (mTime <= 0) {
			if (fLoop) {
				mTime = mDefaultTime;
			}
			else {
				this->Stop();
			}
		}
		if (fActive) {
			--mTime;
		}
		break;
	}
}

void cTimer::Draw() {
	
}