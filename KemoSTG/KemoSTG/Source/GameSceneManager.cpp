﻿#include "../Header/GameSceneManager.h"
#include "../Header/GameScene/GameNotice.h"
#include "../Header/GameScene/GameLogo.h"
#include "../Header/GameScene/GameTitle.h"
#include "../Header/GameScene/GameMain.h"
#include "../Header/GameScene/GameRanking.h"

cGameSceneManager::cGameSceneManager() : mNextScene(eGameScene_None) {
	pScene = static_cast<cGameBaseScene*>(new cLogoGameScene(this));
}

void cGameSceneManager::Initialize() {
	pScene->cGameBaseScene::Initialize();
	pScene->Initialize();
}

void cGameSceneManager::Finalize() {
	pScene->Finalize();
	pScene->cGameBaseScene::Finalize();
}

void cGameSceneManager::Update() {
	if (mNextScene != eGameScene_None) {
		pScene->Finalize();
		delete pScene;
		switch (mNextScene) {
		case eGameScene_Notice:
			pScene = static_cast<cGameBaseScene*>(new cNoticeGameScene(this));
			break;
		case eGameScene_Logo:
			pScene = static_cast<cGameBaseScene*>(new cLogoGameScene(this));
			break;
		case eGameScene_Title:
			pScene = static_cast<cGameBaseScene*>(new cTitleGameScene(this));
			break;
		case eGameScene_Game:
			pScene = static_cast<cGameBaseScene*>(new cMainGameScene(this));
			break;
		case eGameScene_Ranking:
			pScene = static_cast<cGameBaseScene*>(new cRankingGameScene(this));
			break;
		}
		mNextScene = eGameScene_None;
		pScene->Initialize();
	}
	pScene->Update();
}

void cGameSceneManager::Draw() {
	pScene->Draw();
}

void cGameSceneManager::SetVirtualPad(cVirtualPad Pad[2]) {
	pScene->SetVirtualPad(Pad);
}

void cGameSceneManager::ChangeScene(eGameScene NextScene) {
	mNextScene = NextScene;
}