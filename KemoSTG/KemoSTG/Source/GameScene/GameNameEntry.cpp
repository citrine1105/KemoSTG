#include "../../Header/GameScene/GameNameEntry.h"

cNameEntryGameScene::cNameEntryGameScene(iSceneChanger<eGameScene> *Changer) : cGameBaseScene(Changer) {

}

cNameEntryGameScene::~cNameEntryGameScene() {

}

void cNameEntryGameScene::Initialize() {
	mImage.SetPath(_T("./Data/Image/Game/Character/rin.png"));
	mImageMove.SetPosition(-280, GAME_SCREEN_WIDTH);
	mImageMove.MoveToPointX(0, 32, eEasing_Sine);
	mImage.Load();

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
	mImage.Finalize();
}

void cNameEntryGameScene::Update() {
	mSceneTimer.Update();
	mTimer.Update();
	mImageMove.Update();

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
	std::array<std::tstring, 2> tPlayerStr;
	tPlayerStr.at(0) = _T("PLAYER1");
	tPlayerStr.at(1) = _T("PLAYER2");
	DrawFormatStringToHandle(12, 8, GetColor(0xFF, 0xFF, 0xFF), gGameFontContainer.GetElement(eGameFont_Interface)->GetHandle(), _T("Result"));

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, static_cast<int>(255.0 * 50.0 / 100.0));
	DrawGraph(mImageMove.GetPositionX(), GAME_SCREEN_HEIGHT - 540, mImage.GetHandle(), TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);

	for (int i = 0; i < mItem.size(); i++) {
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, mItemFade.at(i).GetPositionX());
		if (cGameManager::GetInstance()->GetPlayerPointer()->at(0).GetEntryFlag() && cGameManager::GetInstance()->GetPlayerPointer()->at(1).GetEntryFlag()) {
			DrawStringToHandle(GAME_SCREEN_WIDTH * 1 / 6 - GetDrawStringWidthToHandle(mResult.at(0).at(i).c_str(), mResult.at(0).at(i).size(), gGameFontContainer.GetElement(eGameFont_Interface)->GetHandle()) / 2, 8 + 24 * (7 + i * 2), mResult.at(0).at(i).c_str(), GetColor(0xFF, 0xFF, 0xFF), gGameFontContainer.GetElement(eGameFont_Interface)->GetHandle());
			DrawStringToHandle(GAME_SCREEN_WIDTH * 5 / 6 - GetDrawStringWidthToHandle(mResult.at(1).at(i).c_str(), mResult.at(1).at(i).size(), gGameFontContainer.GetElement(eGameFont_Interface)->GetHandle()) / 2, 8 + 24 * (7 + i * 2), mResult.at(1).at(i).c_str(), GetColor(0xFF, 0xFF, 0xFF), gGameFontContainer.GetElement(eGameFont_Interface)->GetHandle());
		}
		else if (cGameManager::GetInstance()->GetPlayerPointer()->at(0).GetEntryFlag() && !cGameManager::GetInstance()->GetPlayerPointer()->at(1).GetEntryFlag()) {
			DrawStringToHandle(GAME_SCREEN_WIDTH * 5 / 6 - GetDrawStringWidthToHandle(mResult.at(0).at(i).c_str(), mResult.at(0).at(i).size(), gGameFontContainer.GetElement(eGameFont_Interface)->GetHandle()) / 2, 8 + 24 * (7 + i * 2), mResult.at(0).at(i).c_str(), GetColor(0xFF, 0xFF, 0xFF), gGameFontContainer.GetElement(eGameFont_Interface)->GetHandle());
		}
		else if (!cGameManager::GetInstance()->GetPlayerPointer()->at(0).GetEntryFlag() && cGameManager::GetInstance()->GetPlayerPointer()->at(1).GetEntryFlag()) {
			DrawStringToHandle(GAME_SCREEN_WIDTH * 1 / 6 - GetDrawStringWidthToHandle(mResult.at(1).at(i).c_str(), mResult.at(1).at(i).size(), gGameFontContainer.GetElement(eGameFont_Interface)->GetHandle()) / 2, 8 + 24 * (7 + i * 2), mResult.at(1).at(i).c_str(), GetColor(0xFF, 0xFF, 0xFF), gGameFontContainer.GetElement(eGameFont_Interface)->GetHandle());
		}
		DrawStringToHandle(GAME_SCREEN_WIDTH / 2 - GetDrawStringWidthToHandle(mItem.at(i).c_str(), mItem.at(i).size(), gGameFontContainer.GetElement(eGameFont_Interface)->GetHandle()) / 2, 8 + 24 * (7 + i * 2), mItem.at(i).c_str(), GetColor(0x00, 0xFF, 0xFF), gGameFontContainer.GetElement(eGameFont_Interface)->GetHandle());
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
	}

	if (cGameManager::GetInstance()->GetPlayerPointer()->at(0).GetEntryFlag() && cGameManager::GetInstance()->GetPlayerPointer()->at(1).GetEntryFlag()) {
		DrawStringToHandle(GAME_SCREEN_WIDTH * 1 / 6 - GetDrawStringWidthToHandle(tPlayerStr.at(0).c_str(), tPlayerStr.at(0).size(), gGameFontContainer.GetElement(eGameFont_Interface)->GetHandle()) / 2, 8 + 24 * 5, tPlayerStr.at(0).c_str(), GetColor(0xFF, 0xFF, 0xFF), gGameFontContainer.GetElement(eGameFont_Interface)->GetHandle(), GetColor(0xE6, 0x5C, 0x73));
		DrawStringToHandle(GAME_SCREEN_WIDTH * 5 / 6 - GetDrawStringWidthToHandle(tPlayerStr.at(1).c_str(), tPlayerStr.at(1).size(), gGameFontContainer.GetElement(eGameFont_Interface)->GetHandle()) / 2, 8 + 24 * 5, tPlayerStr.at(1).c_str(), GetColor(0xFF, 0xFF, 0xFF), gGameFontContainer.GetElement(eGameFont_Interface)->GetHandle(), GetColor(0x5C, 0x8A, 0xE6));
	}
	else if (cGameManager::GetInstance()->GetPlayerPointer()->at(0).GetEntryFlag() && !cGameManager::GetInstance()->GetPlayerPointer()->at(1).GetEntryFlag()) {
		DrawStringToHandle(GAME_SCREEN_WIDTH * 5 / 6 - GetDrawStringWidthToHandle(tPlayerStr.at(0).c_str(), tPlayerStr.at(0).size(), gGameFontContainer.GetElement(eGameFont_Interface)->GetHandle()) / 2, 8 + 24 * 5, tPlayerStr.at(0).c_str(), GetColor(0xFF, 0xFF, 0xFF), gGameFontContainer.GetElement(eGameFont_Interface)->GetHandle(), GetColor(0xE6, 0x5C, 0x73));
	}
	else if (!cGameManager::GetInstance()->GetPlayerPointer()->at(0).GetEntryFlag() && cGameManager::GetInstance()->GetPlayerPointer()->at(1).GetEntryFlag()) {
		DrawStringToHandle(GAME_SCREEN_WIDTH * 1 / 6 - GetDrawStringWidthToHandle(tPlayerStr.at(1).c_str(), tPlayerStr.at(1).size(), gGameFontContainer.GetElement(eGameFont_Interface)->GetHandle()) / 2, 8 + 24 * 5, tPlayerStr.at(1).c_str(), GetColor(0xFF, 0xFF, 0xFF), gGameFontContainer.GetElement(eGameFont_Interface)->GetHandle(), GetColor(0x5C, 0x8A, 0xE6));
	}

	//mTimer.Draw(GAME_SCREEN_WIDTH * 6 / 7, GAME_SCREEN_WIDTH / 8);
}