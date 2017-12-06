#include "../Header/SelectTimer.h"
#include "../Header/GameScene/GameMain.h"

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

	DrawGraph(X - gGameUIImageContainer.GetElement(eGameUI_CaptionTime)->GetSizeX() / 2, Y - 7 - 8 + tY, gGameUIImageContainer.GetElement(eGameUI_CaptionTime)->GetHandle(), TRUE);
	DrawFormatStringToHandle(tX + X, tY + Y, GetColor(0xFF, 0xFF, 0xFF), cFontContainer::GetInstance()->GetElement(eFont_TimerFont), _T("%d"), mTime / static_cast<int>(REFRESH_RATE));
	DrawFormatStringToHandle(tX + X + GetDrawFormatStringWidthToHandle(cFontContainer::GetInstance()->GetElement(eFont_TimerFont), _T("%d"), mTime / static_cast<int>(REFRESH_RATE)), tY + Y + 8, GetColor(0xFF, 0xFF, 0xFF), cFontContainer::GetInstance()->GetElement(eFont_MiniTimerFont), _T(".%d"), abs(mTime % static_cast<int>(REFRESH_RATE) / static_cast<int>(REFRESH_RATE / 10.0)));
}