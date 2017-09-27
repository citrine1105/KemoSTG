#pragma once
#include "Timer.h"
#include "ImageResourceContainer.h"
#include "FontContainer.h"

class cSelectTimer : public cTimer {
public:
	cSelectTimer();
	~cSelectTimer();

	void Draw() override;
	void Draw(const int X, const int Y);
};