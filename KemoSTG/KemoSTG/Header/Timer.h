#pragma once
#include "Macro.h"

enum eCountMode {
	eCountMode_CountUp,
	eCountMode_CountDown
};

class cTimer {
protected:
	AUTO_INT mValue;
	AUTO_INT mDefaultValue;
	eCountMode mCountMode;
	bool fActive;
	bool fLoopCount;
public:
	cTimer();
	cTimer(AUTO_INT Value);
	cTimer(double Second);
	cTimer(AUTO_INT Value, eCountMode CountMode);
	cTimer(double Second, eCountMode CountMode);

	void SetValue(AUTO_INT Value);
	void SetSecond(double Second);
	void SetDefaultValue(AUTO_INT Value);
	void SetCountMode(eCountMode Mode);
	void EnableLoopCount(bool Flag);
	AUTO_INT GetValue();
	double GetSecond();
	eCountMode GetCountMode();

	void Start();
	void Stop();
	void Reset();
	void Update();
	virtual void Draw();
};