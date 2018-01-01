#include "../../Header/GameScene/GameNotice.h"
#include "../../Header/Scene/Game.h"

cNoticeGameScene::cNoticeGameScene(iSceneChanger<eGameScene> *Changer) : cGameBaseScene(Changer) {

}

cNoticeGameScene::~cNoticeGameScene() {

}

void cNoticeGameScene::Initialize() {
	mTimer.SetDefaultSecond(6.0);
	mTimer.SetSecond(6.0);
	mTimer.SetCountMode(eCountMode_CountDown);
	mTimer.Start();
}

void cNoticeGameScene::Finalize() {

}

void cNoticeGameScene::Update() {
	mTimer.Update();
	if (mTimer.GetTime() <= 0) {
		pSceneChanger->ChangeScene(eGameScene_Logo);
	}
}

void cNoticeGameScene::Draw() {
	std::tstring tNotice;
	std::tstring tMessage;
	std::tstring tCopyright;
	std::tstring tVersion;

	tNotice = _T("NOTICE");
	tMessage = _T("THIS GAME IS FOR\n"
		"PERSONAL USE ONLY.\n"
		"SALES, EXPORT OR OPERATION\n"
		"OUTSIDE MAY BE CONSTRUED\n"
		"AS COPYRIGHT AND\n"
		"TRADEMARK INFRIGEMENT.\n"
		"VIOLATORS ARE SUBJECT TO\n"
		"SEVERE PENALTIES AND\n"
		"WILL BE PROSECUTED TO\n"
		"THE FULL EXTENT OF THE JAM.");
	tCopyright = _T("©2018 C-Lab All rights reserved.");
	tVersion = _T("Version ");
	tVersion += VERSION_STRING;

	DrawStringToHandle(GAME_SCREEN_WIDTH / 2 - GetDrawStringWidthToHandle(tNotice.c_str(), tNotice.size(), gGameFontContainer.GetElement(eGameFont_Interface)->GetHandle()) / 2, 24 * 3 + 8,
		tNotice.c_str(), GetColor(0xFF, 0x00, 0x00), gGameFontContainer.GetElement(eGameFont_Interface)->GetHandle());
	DrawStringToHandle(GAME_SCREEN_WIDTH / 2 - GetDrawStringWidthToHandle(tMessage.c_str(), tMessage.size(), gGameFontContainer.GetElement(eGameFont_Interface)->GetHandle()) / 2, 24 * 6 + 8,
		tMessage.c_str(), GetColor(0xFF, 0xFF, 0xFF), gGameFontContainer.GetElement(eGameFont_Interface)->GetHandle());
	DrawStringToHandle(GAME_SCREEN_WIDTH / 2 - GetDrawStringWidthToHandle(tCopyright.c_str(), tCopyright.size(), gGameFontContainer.GetElement(eGameFont_Interface)->GetHandle()) / 2, 24 * 20 + 8,
		tCopyright.c_str(), GetColor(0xFF, 0xFF, 0xFF), gGameFontContainer.GetElement(eGameFont_Interface)->GetHandle());
	DrawStringToHandle(GAME_SCREEN_WIDTH / 2 - GetDrawStringWidthToHandle(tVersion.c_str(), tVersion.size(), gGameFontContainer.GetElement(eGameFont_Interface)->GetHandle()) / 2, 24 * 22 + 8,
		tVersion.c_str(), GetColor(0xFF, 0xFF, 0xFF), gGameFontContainer.GetElement(eGameFont_Interface)->GetHandle());
	
	//mTimer.Draw(240, 32);

	//if (cGameBaseScene::ppVirtualPad[0]->GetInputState(eButton_Shot) > 0) {
	//	DrawString(0, 18, _T("5000兆円くれ"), GetColor(0xFF, 0xFF, 0x00));
	//}
	//else {
	//	DrawString(0, 18, _T("5000兆円くれ"), GetColor(0x9F, 0x9F, 0x9F));
	//}
}