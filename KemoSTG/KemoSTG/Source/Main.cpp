#include "../Header/Include.h"
#include "../Header/StringResource.h"
#include "../Header/Sprite.h"

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

	cSprite *sp = new cSprite[11];
	cSprite spr;
	for (int i = 0; i < 11; i++) {
		sp[i].SetPosition(20.0 + 59.0 * i, 40.0 );
		sp[i].MoveToPoint(20.0 + 59.0 * i, 420.0, 180, static_cast<eEasingType>(i));
	}

	spr.SetCollisionRange(30.0, 30.0);
	spr.SetPosition(320.0, 240.0);
	bool in = false;

	while (ProcessMessage() == 0 && ClearDrawScreen() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0) {
		//for (int i = 0; i < 11; i++) {
		//	sp[i].Update();
		//	sp[i].Draw();
		//}
		if (GetMouseInput() & MOUSE_INPUT_LEFT) {
			if (!in) {
				int tX, tY;
				GetMousePoint(&tX, &tY);
				spr.MoveToPoint(tX, tY, 40, eEasing_Quart);
			}
			in = true;
		}
		else {
			in = false;
		}
		spr.Update();
		spr.Draw();
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
	SetGraphMode(640, 480, 32);	// テスト
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