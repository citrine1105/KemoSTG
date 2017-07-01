#pragma once
#include "Timer.h"
#include "ImageResourceContainer.h"

class cSelectTimer : public cTimer {
protected:
	static int mBigFont;
	static int mSmallFont;
public:
	cSelectTimer();
	~cSelectTimer();

	void Draw() override;
	void Draw(const int X, const int Y);
};