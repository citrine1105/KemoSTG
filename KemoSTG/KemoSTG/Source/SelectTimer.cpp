#include "../Header/SelectTimer.h"

cSelectTimer::cSelectTimer() {
	this->Initialize();
}

cSelectTimer::~cSelectTimer() {
	this->Finalize();
}

void cSelectTimer::Draw() {
	this->Draw(0, 0);
}

void cSelectTimer::Draw(const int X, const int Y) {
	int tX = 0, tY = -15;
	tX -= GetDrawFormatStringWidthToHandle(cFontContainer::GetInstance()->GetElement(eFont_TimerFont), _T("%d"), mTime / static_cast<int>(REFRESH_RATE));
	tX -= GetDrawFormatStringWidthToHandle(cFontContainer::GetInstance()->GetElement(eFont_MiniTimerFont), _T(".%d"), abs(mTime % static_cast<int>(REFRESH_RATE) / static_cast<int>(REFRESH_RATE / 10.0)));
	tX /= 2;

	DrawGraph(X - cImageResourceContainer::GetInstance()->GetElement(eImage_CaptionTime)->GetSizeX() / 2, Y - 7 - 8 + tY, cImageResourceContainer::GetInstance()->GetElement(eImage_CaptionTime)->GetHandle(), TRUE);
	//SetDrawBlendMode(DX_BLENDMODE_ALPHA, static_cast<int>(255.0 * 8.0 / 10.0));
	//DrawGraph(X - 32, Y - 16, cImageResourceContainer::GetInstance()->GetElement(eImage_SelectTimer)->GetHandle(mValue / 5 % 12), TRUE);
	//SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
	DrawFormatStringToHandle(tX + X, tY + Y, GetColor(0xFF, 0xFF, 0xFF), cFontContainer::GetInstance()->GetElement(eFont_TimerFont), _T("%d"), mTime / static_cast<int>(REFRESH_RATE));
	DrawFormatStringToHandle(tX + X + GetDrawFormatStringWidthToHandle(cFontContainer::GetInstance()->GetElement(eFont_TimerFont), _T("%d"), mTime / static_cast<int>(REFRESH_RATE)), tY + Y + 8, GetColor(0xFF, 0xFF, 0xFF), cFontContainer::GetInstance()->GetElement(eFont_MiniTimerFont), _T(".%d"), abs(mTime % static_cast<int>(REFRESH_RATE) / static_cast<int>(REFRESH_RATE / 10.0)));
}