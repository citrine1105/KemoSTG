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
	cTimer timer(30.0, eCountMode_CountDown);
	timer.Start();

	while (ProcessMessage() == 0 && ClearDrawScreen() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0) {
		//switch (GetUserDefaultUILanguage()) {
		//case MAKELANGID(LANG_JAPANESE, SUBLANG_JAPANESE_JAPAN):
		//	DrawString(0, 0, _T("日本語"), GetColor(0xFF, 0xFF, 0xFF));
		//	break;
		//case MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US):
		//	DrawString(0, 0, _T("English(United Stats)"), GetColor(0xFF, 0xFF, 0xFF));
		//	break;
		//case MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_UK):
		//	DrawString(0, 0, _T("English(United Kingdom)"), GetColor(0xFF, 0xFF, 0xFF));
		//	break;
		//case MAKELANGID(LANG_CHINESE, SUBLANG_CHINESE_SIMPLIFIED):
		//	DrawString(0, 0, _T("简体中文"), GetColor(0xFF, 0xFF, 0xFF));
		//	break;
		//case MAKELANGID(LANG_CHINESE, SUBLANG_CHINESE_TRADITIONAL):
		//	DrawString(0, 0, _T("繁体中文"), GetColor(0xFF, 0xFF, 0xFF));
		//	break;
		//case MAKELANGID(LANG_KOREAN, SUBLANG_KOREAN):
		//	DrawString(0, 0, _T("한국어"), GetColor(0xFF, 0xFF, 0xFF));
		//	break;
		//default:
		//	DrawString(0, 0, _T("Other Language"), GetColor(0xFF, 0xFF, 0xFF));
		//	break;
		//}
		timer.Update();
		if (timer.GetSecond() <= 0.0) {
			timer.Reset();
		}
		//DrawBox(0, 0, 640, 480, GetColor(0xFF, 0xFF, 0xFF), TRUE);
		DrawFormatStringToHandle(8, 8, GetColor(0xFF, 0xFF, 0xFF), hand, _T("timer = %lf"), timer.GetSecond());
		//DrawFormatStringToHandle(8, 8, GetColor(0xFF, 0xFF, 0xFF), hand, _T("%lf"), 19.9);

		ScreenFlip();
	}

	DxLib_End();

	return 0;
}