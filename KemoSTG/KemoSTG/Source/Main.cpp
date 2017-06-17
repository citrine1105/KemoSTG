#include "../Header/Include.h"
#include "../Header/StringResource.h"
#include "../Header/Sprite.h"
#include "../Header/ImageResource.h"
#include "../Header/SoundResource.h"
#include "../Header/Pad.h"

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

	cSprite spr;
	spr.SetCollisionRange(30.0, 30.0);
	spr.SetPosition(320.0, 240.0);
	bool in = false;

	cImageResource img(_T("./Data/Image/test.png"));
	cSoundResource snd(_T("./Data/Sound/Music/bgm_test.wav"), 1), se;
	img.Load();
	snd.Load();
	se.Load(_T("./Data/Sound/Effect/se_test.wav"), 1);

	cTimer r(0, eCountMode_CountUp);
	r.Start();

	cPad p(DX_INPUT_PAD1);

	while (ProcessMessage() == 0 && ClearDrawScreen() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0) {
		//clsDx();
		//printfDx(_T("%X\n"), img.GetHandle());
		//printfDx(_T("%d\n"), GetASyncLoadNum());
		//if (CheckHandleASyncLoad(snd.GetHandle()) == FALSE && CheckSoundMem(snd.GetHandle()) == 0) {
		//	PlaySoundMem(snd.GetHandle(), DX_PLAYTYPE_LOOP, FALSE);
		//}
		//if (GetASyncLoadNum() == 0) {
		//	r.Update();
		//}

		//if (GetMouseInput() & MOUSE_INPUT_LEFT) {
		//	if (!in) {
		//		int tX, tY;
		//		GetMousePoint(&tX, &tY);
		//		spr.MoveToPoint(tX, tY, 40, eEasing_Quart);
		//		PlaySoundMem(se.GetHandle(), DX_PLAYTYPE_BACK, TRUE);
		//	}
		//	in = true;
		//}
		//else {
		//	in = false;
		//}
		//if (GetMouseInput() & MOUSE_INPUT_RIGHT) {
		//	//StopSoundMem(snd.GetHandle());
		//	snd.SetVolume(128);
		//}
		//else {
		//	snd.SetVolume(255);
		//}
		//spr.Update();
		//DrawRotaGraph(320, 240, 0.2, DEGREE_TO_RADIAN(static_cast<double>(r.GetValue())), img.GetHandle(), FALSE);
		//spr.Draw();
		p.Update();
		p.Draw();
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