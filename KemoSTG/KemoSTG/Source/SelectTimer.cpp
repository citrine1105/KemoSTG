#include "../Header/SelectTimer.h"

int cSelectTimer::mBigFont;
int cSelectTimer::mSmallFont;

cSelectTimer::cSelectTimer() {
	this->Initialize();
	mBigFont = CreateFontToHandle(_T("Palatino Linotype"), 26, 0, DX_FONTTYPE_ANTIALIASING_EDGE_4X4);	// フォントハンドルの取得
	mSmallFont = CreateFontToHandle(_T("Palatino Linotype"), 18, 0, DX_FONTTYPE_ANTIALIASING_EDGE_4X4);
}

cSelectTimer::~cSelectTimer() {
	this->Finalize();
	DeleteFontToHandle(mBigFont);
	DeleteFontToHandle(mSmallFont);
}

void cSelectTimer::Draw() {
	this->Draw(0, 0);
}

void cSelectTimer::Draw(const int X, const int Y) {
	int tX = 0, tY = -13;
	tX -= GetDrawFormatStringWidthToHandle(mBigFont, _T("%d"), mValue / 60);
	tX -= GetDrawFormatStringWidthToHandle(mBigFont, _T(".%d"), mValue % 60 / 6);
	tX /= 2;

	DrawGraph(X, Y, cImageResourceContainer::GetInstance()->GetElement(eImage_SelectTimer)->GetHandle(mValue / 5 % 12), TRUE);
	DrawFormatStringToHandle(tX + X, tY + Y, GetColor(0xFF, 0xFF, 0xFF), mBigFont, _T("%d"), mValue / 60);
	DrawFormatStringToHandle(tX + X + GetDrawFormatStringWidthToHandle(mBigFont, _T("%d"), mValue / 60), tY + Y + 8, GetColor(0xFF, 0xFF, 0xFF), mSmallFont, _T(".%d"), mValue % 60 / 6);
}