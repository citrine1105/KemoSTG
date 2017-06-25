#include "../Header/Include.h"
#include "../Header/StringResource.h"
#include "../Header/VirtualPad.h"

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

	cPad *p = new cPad[2];
	cVirtualPad *vp = new cVirtualPad[2];
	p[0].SetJoyPadNum(DX_INPUT_PAD1);
	p[1].SetJoyPadNum(DX_INPUT_PAD3);
	vp[0].SetJoyPad(&p[0]);
	vp[1].SetJoyPad(&p[1]);
	vp[0].SetDefaultAssign(0);
	vp[1].SetDefaultAssign(1);
	vp[0].SetVibrationFlag(true);

	while (ProcessMessage() == 0 && ClearDrawScreen() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0) {
		vp[0].Update();
		vp[1].Update();
		if ((vp[0].GetJoyPad()->GetJoyPadInputState(eXInputAssign_LT) > 0 || vp[0].GetJoyPad()->GetJoyPadInputState(eXInputAssign_RT) > 0) && 
			vp[0].GetVibrationFlag()) {
			vp[0].StartVibration(static_cast<double>(vp[0].GetJoyPad()->GetJoyPadInputState(eXInputAssign_LT) + vp[0].GetJoyPad()->GetJoyPadInputState(eXInputAssign_RT)) * (1000.0 / 510.0), -1);
		}
		else {
			vp[0].StopVibration();
		}
		if (CheckHitKey(KEY_INPUT_SPACE) != 0) {
			vp[1].Draw();
		}
		else {
			vp[0].Draw();
		}
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
	//SetUseCharCodeFormat(DX_CHARCODEFORMAT_UTF8);	// 文字列引数にUTF-8を使用
	SetUseDXArchiveFlag(TRUE);	// DXアーカイブを有効に
	SetDXArchiveKeyString(DX_ARCHIVE_KEY_STRING);	// DXアーカイブキー
	SetMultiThreadFlag(TRUE);	// マルチスレッド動作有効
	SetAlwaysRunFlag(TRUE);	// 非アクティブ時も動作
	SetGraphMode(640, 480, 32);	// テスト
	ChangeWindowMode(TRUE);	// テスト
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