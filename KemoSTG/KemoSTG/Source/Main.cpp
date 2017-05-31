#include "../Header/Include.h"
#include "../Header/StringResource.h"
#include "../Header/Easing.h"

int Game_Init();	 // アプリケーション初期化処理

int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow) {
	if (Game_Init() == 0) {
		//cStringResource tMes;
		//tMes.SetString(eLanguage_Japanese, _T("アプリケーションを開始します"));
		//tMes.SetString(eLanguage_English, _T("Application Start"));

		//MessageBox(GetMainWindowHandle(), tMes.GetString()->c_str(), CAPTION_STRING, MB_OK | MB_ICONINFORMATION);
	}
	else {
		cStringResource tErrMes;
		tErrMes.SetString(eLanguage_Japanese, _T("初期化に失敗しました"));
		tErrMes.SetString(eLanguage_English, _T("Initialization Failed"));

		MessageBox(GetMainWindowHandle(), tErrMes.GetString()->c_str(), CAPTION_STRING, MB_OK | MB_ICONERROR);
	}
	SetDrawScreen(DX_SCREEN_BACK);

	int time = 0;
	double in = 0.0, out = 0.0, inout = 0.0;
	cEasing e;

	while (ProcessMessage() == 0/* && ClearDrawScreen() == 0*/ && CheckHitKey(KEY_INPUT_ESCAPE) == 0) {
		++time;
		//if (time >= 60) {
		//	time = 0;
		//}
		in = e.easeOut(eEasing_Quad, static_cast<double>(time % 120) / 120.0, 1.0);
		out = e.easeOut(eEasing_Cubic, static_cast<double>(time % 120) / 120.0, 1.0);
		inout = e.easeOut(eEasing_Quart, static_cast<double>(time % 120) / 120.0, 1.0);
		DrawString(8, 25, _T("easeIn"), GetColor(0xFF, 0xFF, 0xFF));
		DrawPixel(time, -static_cast<int>(in * 100.0) + 145, GetColor(0xFF, 0xFF, 0xFF));
		DrawString(8, 170, _T("easeOut"), GetColor(0xFF, 0xFF, 0xFF));
		DrawPixel(time, -static_cast<int>(out * 100.0) + 290, GetColor(0xFF, 0xFF, 0xFF));
		DrawString(8, 315, _T("easeInOut"), GetColor(0xFF, 0xFF, 0xFF));
		DrawPixel(time, -static_cast<int>(inout * 100.0) + 435, GetColor(0xFF, 0xFF, 0xFF));
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
	SetMultiThreadFlag(TRUE);	// マルチスレッド動作有効
	SetAlwaysRunFlag(TRUE);	// 非アクティブ時も動作
	ChangeWindowMode(TRUE);	// テスト
	SetUseCharCodeFormat(DX_CHARCODEFORMAT_UTF8);	// 文字列引数にUTF-8を使用
	SetMainWindowText(CAPTION_STRING);	// タイトルバー文字列を設定
	SetFullScreenResolutionMode(DX_FSRESOLUTIONMODE_NATIVE);		// フルスクリーン時の挙動を設定
	SetUseDirect3DVersion(DX_DIRECT3D_9EX);	// Direct3D 9Exを使用する
	SetUseASyncLoadFlag(TRUE);	// 非同期読み込みを有効に
	if (DxLib_Init() != 0) {
		return -1;
	}	// DXライブラリ初期化

	return 0;
}