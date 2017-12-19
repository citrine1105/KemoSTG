#include "../../Header/GameScene/GameNameEntry.h"

cNameEntryGameScene::cNameEntryGameScene(iSceneChanger<eGameScene> *Changer) : cGameBaseScene(Changer) {

}

cNameEntryGameScene::~cNameEntryGameScene() {

}

void cNameEntryGameScene::Initialize() {
	mItem.at(0) = _T("Maximum Rate");
	mItem.at(1) = _T("Bomb Count");
	mItem.at(2) = _T("Damage Count");
	mItem.at(3) = _T("Continue");
	mItem.at(4) = _T("Reached Stage");
	mItem.at(5) = _T("Total Score");

	for (int i = 0; i < mResult.size(); i++) {
		mResult.at(i).at(0) = _T("×");
		mResult.at(i).at(0) += std::to_tstring(cGameManager::GetInstance()->GetPlayerPointer()->at(i).GetScore().mMaxRate);
		mResult.at(i).at(1) = std::to_tstring(cGameManager::GetInstance()->GetPlayerPointer()->at(i).GetScore().mBomb);
		mResult.at(i).at(2) = std::to_tstring(cGameManager::GetInstance()->GetPlayerPointer()->at(i).GetScore().mDamaged);
		mResult.at(i).at(3) = std::to_tstring(cGameManager::GetInstance()->GetPlayerPointer()->at(i).GetScore().mContinue);
		mResult.at(i).at(4) = _T("1");
		mResult.at(i).at(5) = std::to_tstring(cGameManager::GetInstance()->GetPlayerPointer()->at(i).GetScore().mScore);
	}

	for (auto &i : mItemFade) {
		i.Initialize();
	}

	mTimer.Initialize(30.0, 30.0, eCountMode_CountDown);

	mSceneTimer.Start();
	//mTimer.Start();
}

void cNameEntryGameScene::Finalize() {

}

void cNameEntryGameScene::Update() {
	mSceneTimer.Update();
	mTimer.Update();
	for (auto &i : mItemFade) {
		i.Update();
	}

	for (int i = 0; i < mItem.size(); i++) {
		if (mSceneTimer.GetTime() == 10 * (i + 1)) {
			mItemFade.at(i).MoveToPointX(255.0, 8, eEasing_Linear, eEasingFunction_In);
		}
	}

	if (ppVirtualPad[0]->GetInputState(eButton_Shot) == 1) {
		pSceneChanger->ChangeScene(eGameScene_Logo);
	}
}

void cNameEntryGameScene::Draw() {
	DrawFormatStringToHandle(12, 8, GetColor(0xFF, 0xFF, 0xFF), gGameFontContainer.GetElement(eGameFont_Interface)->GetHandle(), _T("Result"));
	for (int i = 0; i < mItem.size(); i++) {
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, mItemFade.at(i).GetPositionX());
		if (cGameManager::GetInstance()->GetPlayerPointer()->at(0).GetEntryFlag() && cGameManager::GetInstance()->GetPlayerPointer()->at(1).GetEntryFlag()) {
			DrawStringToHandle(GAME_SCREEN_WIDTH * 1 / 6 - GetDrawStringWidthToHandle(mResult.at(0).at(i).c_str(), mResult.at(0).at(i).size(), gGameFontContainer.GetElement(eGameFont_Interface)->GetHandle()) / 2, 8 + 24 * (6 + i * 2), mResult.at(0).at(i).c_str(), GetColor(0xFF, 0xFF, 0xFF), gGameFontContainer.GetElement(eGameFont_Interface)->GetHandle());
			DrawStringToHandle(GAME_SCREEN_WIDTH * 5 / 6 - GetDrawStringWidthToHandle(mResult.at(1).at(i).c_str(), mResult.at(1).at(i).size(), gGameFontContainer.GetElement(eGameFont_Interface)->GetHandle()) / 2, 8 + 24 * (6 + i * 2), mResult.at(1).at(i).c_str(), GetColor(0xFF, 0xFF, 0xFF), gGameFontContainer.GetElement(eGameFont_Interface)->GetHandle());
		}
		else if (cGameManager::GetInstance()->GetPlayerPointer()->at(0).GetEntryFlag() && !cGameManager::GetInstance()->GetPlayerPointer()->at(1).GetEntryFlag()) {
			DrawStringToHandle(GAME_SCREEN_WIDTH * 5 / 6 - GetDrawStringWidthToHandle(mResult.at(0).at(i).c_str(), mResult.at(0).at(i).size(), gGameFontContainer.GetElement(eGameFont_Interface)->GetHandle()) / 2, 8 + 24 * (6 + i * 2), mResult.at(0).at(i).c_str(), GetColor(0xFF, 0xFF, 0xFF), gGameFontContainer.GetElement(eGameFont_Interface)->GetHandle());
		}
		else if (!cGameManager::GetInstance()->GetPlayerPointer()->at(0).GetEntryFlag() && cGameManager::GetInstance()->GetPlayerPointer()->at(1).GetEntryFlag()) {
			DrawStringToHandle(GAME_SCREEN_WIDTH * 1 / 6 - GetDrawStringWidthToHandle(mResult.at(1).at(i).c_str(), mResult.at(1).at(i).size(), gGameFontContainer.GetElement(eGameFont_Interface)->GetHandle()) / 2, 8 + 24 * (6 + i * 2), mResult.at(1).at(i).c_str(), GetColor(0xFF, 0xFF, 0xFF), gGameFontContainer.GetElement(eGameFont_Interface)->GetHandle());
		}
		DrawStringToHandle(GAME_SCREEN_WIDTH / 2 - GetDrawStringWidthToHandle(mItem.at(i).c_str(), mItem.at(i).size(), gGameFontContainer.GetElement(eGameFont_Interface)->GetHandle()) / 2, 8 + 24 * (6 + i * 2), mItem.at(i).c_str(), GetColor(0x00, 0xFF, 0xFF), gGameFontContainer.GetElement(eGameFont_Interface)->GetHandle());
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
	}

	//mTimer.Draw(GAME_SCREEN_WIDTH * 6 / 7, GAME_SCREEN_WIDTH / 8);
}