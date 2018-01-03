#include "../Header/Scene.h"

std::array<cPad, 2> cScene::mPad;
std::array<cVirtualPad, 2> cScene::mVirtualPad;
cFontContainer gSystemFont;

cScene::cScene(iSceneChanger<eScene> *Changer) {
	pSceneChanger = Changer;
	cKeyboard::GetInstance()->Initialize();
	mPad[0].SetJoyPadNum(DX_INPUT_PAD1);
	mPad[1].SetJoyPadNum(DX_INPUT_PAD2);
	mVirtualPad[0].SetJoyPad(&mPad[0]);
	mVirtualPad[0].SetDefaultAssign(0);
	mVirtualPad[1].SetJoyPad(&mPad[1]);
	mVirtualPad[1].SetDefaultAssign(1);
}

cScene::~cScene() {

}

void cScene::Initialize() {

}

void cScene::Finalize() {

}

void cScene::Update() {
	cKeyboard::GetInstance()->Update();
	mVirtualPad[0].Update();
	mVirtualPad[1].Update();
	// スクリーンショット
	if (((cKeyboard::GetInstance()->GetKeyPushState(KEY_INPUT_LCONTROL) || cKeyboard::GetInstance()->GetKeyPushState(KEY_INPUT_RCONTROL))
		&& cKeyboard::GetInstance()->GetKeyPushStateOnce(KEY_INPUT_P)) ||	// Ctrl+Pが押された場合
		cKeyboard::GetInstance()->GetKeyPushStateOnce(KEY_INPUT_SYSRQ)	// PrintScreenが押された場合
		) {
		std::tstring tFileName;	// ファイル名
		std::array<std::tostringstream, 7> tStream;	// ファイル名生成用
		SYSTEMTIME tTime;	// 時刻格納用
		GetLocalTime(&tTime);	// ローカル時刻取得

		tFileName = _T("./ScreenShot/");
		if (!PathIsDirectory(tFileName.c_str())) {	// ディレクトリが存在しない場合
			CreateDirectory(tFileName.c_str(), NULL);	// ディレクトリを作成
		}

		for (auto &i : tStream) {
			i.fill(_T('0'));	// 空いた部分を0で埋める
			i.width(2);	// 桁数を2に
		}
		tStream.at(6).width(1);	// ミリ秒は1桁

		// 時刻を文字列にする
		tStream.at(0) << tTime.wYear % 100;
		tStream.at(1) << tTime.wMonth;
		tStream.at(2) << tTime.wDay;
		tStream.at(3) << tTime.wHour;
		tStream.at(4) << tTime.wMinute;
		tStream.at(5) << tTime.wSecond;
		tStream.at(6) << tTime.wMilliseconds / 100;

		for (auto &i : tStream) {
			tFileName += i.str();	// ファイル名生成
			tFileName += _T("_");
		}

		tFileName.pop_back();	// 1文字消す
		tFileName += _T(".png");

		SaveDrawScreenToPNG(0, 0, DISPLAY_WIDTH, DISPLAY_HEIGHT, tFileName.c_str());	// スクリーンショットを保存
	}
}

void cScene::Draw() {

}