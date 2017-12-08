#pragma once
#include "Timer.h"
#include "ImageResourceContainer.h"
#include "FontContainer.h"

extern cFontContainer gTimerFontContainer;

enum eTimerFontIndex {
	eTimerFont_Big,		// 秒
	eTimerFont_Small,	// ミリ秒

	eTimerFont_TotalNum	// 総要素数
};

class cSelectTimer : public cTimer {
public:
	cSelectTimer();
	~cSelectTimer();

	void Draw() override;
	void Draw(const int X, const int Y);
};