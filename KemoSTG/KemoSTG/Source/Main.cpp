#include "DxLib.h"
#include "../Header/Timer.h"
#include "../Header/StringResource.h"

int Game_Init();	 // アプリケーション初期化処理

int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow) {
	if (Game_Init() == 0) {
		cStringResource tMes;
		tMes.SetString(eLanguage_Japanese, _T("アプリケーションを開始します"));
		tMes.SetString(eLanguage_English, _T("Application Start"));

		MessageBox(GetMainWindowHandle(), tMes.GetString()->c_str(), CAPTION_STRING, MB_OK | MB_ICONINFORMATION);
	}
	else {
		cStringResource tErrMes;
		tErrMes.SetString(eLanguage_Japanese, _T("初期化に失敗しました"));
		tErrMes.SetString(eLanguage_English, _T("Initialization Failed"));

		MessageBox(GetMainWindowHandle(), tErrMes.GetString()->c_str(), CAPTION_STRING, MB_OK | MB_ICONERROR);
	}
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

int Game_Init() {
#ifdef _DEBUG
	SetOutApplicationLogValidFlag(TRUE);		// デバッグモード時はログを出力
#else
	SetOutApplicationLogValidFlag(FALSE);	// リリースモード時はログを出力しない
#endif // _DEBUG
	SetAlwaysRunFlag(TRUE);	// 非アクティブ時も動作
	ChangeWindowMode(TRUE);	// テスト
	SetMainWindowText(CAPTION_STRING);	// タイトルバー文字列を設定
	SetFullScreenResolutionMode(DX_FSRESOLUTIONMODE_NATIVE);		// フルスクリーン時の挙動を設定
	SetUseDirect3DVersion(DX_DIRECT3D_9EX);	// Direct3D 9Exを使用する
	SetUseASyncLoadFlag(TRUE);	// 非同期読み込みを有効に
	if (DxLib_Init() != 0) {
		return -1;
	}	// DXライブラリ初期化

	return 0;
}