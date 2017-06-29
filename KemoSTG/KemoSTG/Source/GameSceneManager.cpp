#include "../Header/GameSceneManager.h"
#include "../Header/GameScene/Notice.h"
#include "../Header/GameScene/Logo.h"

cGameSceneManager::cGameSceneManager() : mNextScene(eGameScene_Notice) {
	pScene = static_cast<cGameBaseScene*>(new cNoticeGameScene(this));
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