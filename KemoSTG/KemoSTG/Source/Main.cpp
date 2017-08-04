#include "../Header/Include.h"
#include "../Header/StringResource.h"
#include "../Header/SceneManager.h"
#include "../Header/Config.h"

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
	SetDrawMode(DX_DRAWMODE_BILINEAR);

	cSceneManager scene;
	scene.Initialize();

	while (ProcessMessage() == 0 && ClearDrawScreen() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0) {
		scene.Update();
		scene.Draw();
		ScreenFlip();
	}

	scene.Finalize();

	DxLib_End();

	cSystemConfig::GetInstance()->Write();

	return 0;
}

int Game_Init() {
	cSystemConfig::GetInstance()->Load();
#ifdef _DEBUG
	SetOutApplicationLogValidFlag(TRUE);		// デバッグモード時はログを出力
#else
	SetOutApplicationLogValidFlag(FALSE);	// リリースモード時はログを出力しない
#endif // _DEBUG
	//SetUseCharCodeFormat(DX_CHARCODEFORMAT_UTF8);	// 文字列引数にUTF-8を使用
	SetUseDXArchiveFlag(TRUE);	// DXアーカイブを有効に
	SetDXArchiveKeyString(DX_ARCHIVE_KEY_STRING);	// DXアーカイブキー
	SetMultiThreadFlag(TRUE);	// マルチスレッド動作有効
	SetAlwaysRunFlag(TRUE);	// 非アクティブ時も動作
	SetGraphMode(DISPLAY_WIDTH, DISPLAY_HEIGHT, 32);	// 解像度設定
	ChangeWindowMode(cSystemConfig::GetInstance()->GetConfig().fWindowMode);	// ウィンドウモード設定
	SetMainWindowText(CAPTION_STRING);	// タイトルバー文字列を設定
	SetFullScreenResolutionMode(DX_FSRESOLUTIONMODE_NATIVE);		// フルスクリーン時の挙動を設定
	SetUseDirect3DVersion(DX_DIRECT3D_9EX);	// Direct3D 9Exを使用する
	//SetEnableXAudioFlag(TRUE);	// XAudio2を使用する
	SetUseASyncLoadFlag(TRUE);	// 非同期読み込みを有効に
	if (DxLib_Init() != 0) {
		return -1;
	}	// DXライブラリ初期化

	return 0;
}