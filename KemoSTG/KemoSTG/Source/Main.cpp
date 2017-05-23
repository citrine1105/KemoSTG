#include "../Header/Include.h"
#include "../Header/Timer.h"
#include "../Header/Vector.h"
#include "../Header/CoinChute.h"
#include "../Header/StringResource.h"

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

	int hand;
	hand = CreateFontToHandle(_T("Palatino Linotype"), 18, 0, DX_FONTTYPE_ANTIALIASING_EDGE_4X4, -1, 1);
	cTimer timer(static_cast<AUTO_INT>(0), eCountMode_CountUp);
	timer.Start();
	cVector2D v(320.0, 240.0), a, b, c;
	cCoinChute coin(4);
	v.SetMagnitude(200.0);
	a.SetStartPoint(320.0, 320.0);
	a.SetComponent(0.0, -150.0);
	b.SetStartPoint(a);
	c.SetStartPoint(a);
	b.SetPolarForm(PI / 180.0 * -180.0, 100.0);
	c.SetPolarForm(PI / 180.0 * 0.0, 100.0);
	while (ProcessMessage() == 0 && ClearDrawScreen() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0) {
		timer.Update();
		//v.SetAngle(PI / 180.0 * static_cast<double>(timer.GetValue()));

		//if (CheckHitKey(KEY_INPUT_LEFT) != 0) {
		//	b.AddAngle(-0.02);
		//	c.AddAngle(-0.02);
		//}
		//else if (CheckHitKey(KEY_INPUT_RIGHT) != 0) {
		//	b.AddAngle(0.02);
		//	c.AddAngle(0.02);
		//}

		if (timer.GetValue() % 90 == 0) {
			coin.AddCoin();
		}

		if (timer.GetValue() <= 0) {
			timer.Stop();
		}
		DrawBox(0, 0, 480, 480, GetColor(0x9F, 0x9F, 0x9F), TRUE);
		//a.Draw();
		//b.Draw();
		//c.Draw();
		//v.Draw();
		//DrawFormatStringToHandle(8, 8, GetColor(0xFF, 0xFF, 0xFF), hand, _T("timer = %.0lf"), floor(timer.GetSecond()));

		//DrawFormatStringToHandle(94 - GetDrawFormatStringWidthToHandle(hand, _T("PRESS 1P START")) / 2, 8, GetColor(0xFF, 0xFF, 0xFF), hand, _T("PRESS 1P START"));
		//DrawFormatStringToHandle(386 - GetDrawFormatStringWidthToHandle(hand, _T("PRESS 2P START")) / 2, 8, GetColor(0xFF, 0xFF, 0xFF), hand, _T("PRESS 2P START"));
		//DrawFormatStringToHandle(94 - GetDrawFormatStringWidthToHandle(hand, _T("INSERT 2 COINS")) / 2, 8, GetColor(0xFF, 0xFF, 0xFF), hand, _T("INSERT 2 COINS"));
		//DrawFormatStringToHandle(386 - GetDrawFormatStringWidthToHandle(hand, _T("INSERT 2 COINS")) / 2, 8, GetColor(0xFF, 0xFF, 0xFF), hand, _T("INSERT 2 COINS"));

		//DrawFormatStringToHandle(120 - GetDrawFormatStringWidthToHandle(hand, _T("INSERT 2\nMORE COINS")) / 2, 8 + 24 * 13 - 160, GetColor(0xFF, 0xFF, 0xFF), hand, _T("INSERT 2\nMORE COINS"));
		//DrawFormatStringToHandle(120 - GetDrawFormatStringWidthToHandle(hand, _T("INSERT 2")) / 2, 8 + 24 * 15 - 160, GetColor(0xFF, 0xFF, 0xFF), hand, _T("INSERT 2"));
		//DrawFormatStringToHandle(120 - GetDrawFormatStringWidthToHandle(hand, _T("MORE COINS")) / 2, 8 + 24 * 16 - 160, GetColor(0xFF, 0xFF, 0xFF), hand, _T("MORE COINS"));
		//DrawFormatStringToHandle(360 - GetDrawFormatStringWidthToHandle(hand, _T("INSERT 3 COINS")) / 2, 8 + 24 * 15 - 160, GetColor(0xFF, 0xFF, 0xFF), hand, _T("INSERT 3 COINS"));
		if (timer.GetValue() % 30 < 20) {
			if (coin.GetFreePlayFlag() || coin.GetCredit() > 0U) {
				DrawFormatStringToHandle(240 - GetDrawFormatStringWidthToHandle(hand, _T("PRESS 1P OR 2P START BUTTON")) / 2, 8 + 24 * 15 - 160, GetColor(0xFF, 0xFF, 0xFF), hand, _T("PRESS 1P OR 2P START BUTTON"));
			}
			else if (coin.GetNeedCoinTo1Credit() >= 2) {
				if (coin.GetCoin() == 0U) {
					DrawFormatStringToHandle(240 - GetDrawFormatStringWidthToHandle(hand, _T("INSERT %u COINS"), coin.GetNeedStartCoin()) / 2, 8 + 24 * 15 - 160, GetColor(0xFF, 0xFF, 0xFF), hand, _T("INSERT %u COINS"), coin.GetNeedStartCoin());
				}
				else {
					DrawFormatStringToHandle(240 - GetDrawFormatStringWidthToHandle(hand, coin.GetNeedStartCoin() >= 2U ? _T("INSERT %u MORE COINS") : _T("INSERT %u MORE COIN"), coin.GetNeedStartCoin()) / 2, 8 + 24 * 15 - 160, GetColor(0xFF, 0xFF, 0xFF), hand, coin.GetNeedStartCoin() >= 2U ? _T("INSERT %u MORE COINS") : _T("INSERT %u MORE COIN"), coin.GetNeedStartCoin());
				}
			}
			else {
				DrawFormatStringToHandle(240 - GetDrawFormatStringWidthToHandle(hand, _T("INSERT COIN")) / 2, 8 + 24 * 15 - 160, GetColor(0xFF, 0xFF, 0xFF), hand, _T("INSERT COIN"));
			}
		}

		DrawFormatStringToHandle(240 - GetDrawFormatStringWidthToHandle(hand, _T("RANK: NORMAL")) / 2, 8 + 24 * 18 - 160, GetColor(0xFF, 0xFF, 0xFF), hand, _T("RANK: NORMAL"));
		DrawFormatStringToHandle(240 - GetDrawFormatStringWidthToHandle(hand, _T("-EXTEND-")) / 2, 8 + 24 * 20 - 160, GetColor(0xFF, 0xFF, 0xFF), hand, _T("-EXTEND-"));
		DrawFormatStringToHandle(133, 8 + 24 * 21 - 160, GetColor(0xFF, 0xFF, 0xFF), hand, _T("1ST"));
		DrawFormatStringToHandle(347 - GetDrawFormatStringWidthToHandle(hand, _T("40,000,000PTS")), 8 + 24 * 21 - 160, GetColor(0xFF, 0xFF, 0xFF), hand, _T("40,000,000PTS"));
		DrawFormatStringToHandle(133, 8 + 24 * 22 - 160, GetColor(0xFF, 0xFF, 0xFF), hand, _T("2ND"));
		DrawFormatStringToHandle(347 - GetDrawFormatStringWidthToHandle(hand, _T("100,000,000PTS")), 8 + 24 * 22 - 160, GetColor(0xFF, 0xFF, 0xFF), hand, _T("100,000,000PTS"));
		//DrawFormatStringToHandle(240 - GetDrawFormatStringWidthToHandle(hand, _T("35,000,000PTS EVERY")) / 2, 8 + 24 * 22 - 160, GetColor(0xFF, 0xFF, 0xFF), hand, _T("35,000,000PTS EVERY"));
		//DrawFormatStringToHandle(240 - GetDrawFormatStringWidthToHandle(hand, _T("NO EXTEND")) / 2, 8 + 24 * 22 - 160, GetColor(0xFF, 0xFF, 0xFF), hand, _T("NO EXTEND"));

		//DrawFormatStringToHandle(120 - GetDrawFormatStringWidthToHandle(hand, _T("CREDIT: 0(1/3)")) / 2, 8 + 24 * 25 - 160, GetColor(0xFF, 0xFF, 0xFF), hand, _T("CREDIT: 0(1/3)"));
		//DrawFormatStringToHandle(360 - GetDrawFormatStringWidthToHandle(hand, _T("CREDIT: 0(0/3)")) / 2, 8 + 24 * 25 - 160, GetColor(0xFF, 0xFF, 0xFF), hand, _T("CREDIT: 0(0/3)"));
		//DrawFormatStringToHandle(240 - GetDrawFormatStringWidthToHandle(hand, _T("CREDITS: 3")) / 2, 8 + 24 * 25 - 160, GetColor(0xFF, 0xFF, 0xFF), hand, _T("CREDITS: 3"));

		if (coin.GetFreePlayFlag()) {
			DrawFormatStringToHandle(240 - GetDrawFormatStringWidthToHandle(hand, _T("FREE PLAY")) / 2, 8 + 24 * 25 - 160, GetColor(0xFF, 0xFF, 0xFF), hand, _T("FREE PLAY"));
		}
		else if (coin.GetNeedCoinTo1Credit() <= 1) {
			DrawFormatStringToHandle(240 - GetDrawFormatStringWidthToHandle(hand, coin.GetCredit() >= 2U ? _T("CREDITS: %u") : _T("CREDIT: %u"), coin.GetCredit()) / 2, 8 + 24 * 25 - 160, GetColor(0xFF, 0xFF, 0xFF), hand, coin.GetCredit() >= 2U ? _T("CREDITS: %u") : _T("CREDIT: %u"), coin.GetCredit());
		}
		else {
			DrawFormatStringToHandle(240 - GetDrawFormatStringWidthToHandle(hand, coin.GetCredit() >= 2U ? _T("CREDITS: %u(%u/%d)") : _T("CREDIT: %u(%u/%d)"), coin.GetCredit(), coin.GetCoin(), coin.GetNeedCoinTo1Credit()) / 2, 8 + 24 * 25 - 160, GetColor(0xFF, 0xFF, 0xFF), hand, coin.GetCredit() >= 2U ? _T("CREDITS: %u(%u/%d)") : _T("CREDIT: %u(%u/%d)"), coin.GetCredit(), coin.GetCoin(), coin.GetNeedCoinTo1Credit());
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
	SetMultiThreadFlag(TRUE);	// マルチスレッド動作有効
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