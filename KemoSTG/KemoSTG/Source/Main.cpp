#include "DxLib.h"
#include "../Header/Timer.h"

int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow) {
	ChangeWindowMode(TRUE);
	SetMainWindowText(CAPTION_STRING);
	MessageBox(GetMainWindowHandle(), _T("Application Begin"), CAPTION_STRING, MB_OK | MB_ICONINFORMATION);
	DxLib_Init();
	SetDrawScreen(DX_SCREEN_BACK);

	int hand;
	hand = CreateFontToHandle(_T("Palatino Linotype"), 20, 0, DX_FONTTYPE_ANTIALIASING_4X4, -1, 1);
	cTimer timer(10.0, eCountMode_CountDown);
	timer.Start();

	while (ProcessMessage() == 0 && ClearDrawScreen() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0) {
		timer.Update();
		if (timer.GetValue() <= 0) {
			timer.Stop();
		}
		DrawFormatStringToHandle(8, 8, GetColor(0xFF, 0xFF, 0xFF), hand, _T("timer = %lf"), timer.GetSecond());

		ScreenFlip();
	}

	DxLib_End();

	return 0;
}