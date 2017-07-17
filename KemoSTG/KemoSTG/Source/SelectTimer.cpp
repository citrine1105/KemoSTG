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
	int tX = 0, tY = -15;
	tX -= GetDrawFormatStringWidthToHandle(mBigFont, _T("%d"), mValue / 60);
	tX -= GetDrawFormatStringWidthToHandle(mSmallFont, _T(".%d"), abs(mValue % 60 / 6));
	tX /= 2;

	DrawGraph(X - cImageResourceContainer::GetInstance()->GetElement(eImage_CaptionTime)->GetSizeX() / 2, Y - 7 - 8 + tY, cImageResourceContainer::GetInstance()->GetElement(eImage_CaptionTime)->GetHandle(), TRUE);
	//SetDrawBlendMode(DX_BLENDMODE_ALPHA, static_cast<int>(255.0 * 8.0 / 10.0));
	//DrawGraph(X - 32, Y - 16, cImageResourceContainer::GetInstance()->GetElement(eImage_SelectTimer)->GetHandle(mValue / 5 % 12), TRUE);
	//SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
	DrawFormatStringToHandle(tX + X, tY + Y, GetColor(0xFF, 0xFF, 0xFF), mBigFont, _T("%d"), mValue / 60);
	DrawFormatStringToHandle(tX + X + GetDrawFormatStringWidthToHandle(mBigFont, _T("%d"), mValue / 60), tY + Y + 8, GetColor(0xFF, 0xFF, 0xFF), mSmallFont, _T(".%d"), mValue % 60 / 6);
}