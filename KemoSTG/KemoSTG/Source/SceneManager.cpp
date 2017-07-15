#include "../Header/SceneManager.h"
#include "../Header/Scene/Load.h"
#include "../Header/Scene/Title.h"
#include "../Header/Scene/Game.h"

cSceneManager::cSceneManager() : mNextScene(eScene_None) {
	pScene = static_cast<cScene*>(new cLoadScene(this));
}

void cSceneManager::Initialize() {
	pScene->Initialize();
}

void cSceneManager::Finalize() {
	pScene->Finalize();
}

void cSceneManager::Update() {
	if (mNextScene != eScene_None) {
		pScene->Finalize();
		delete pScene;
		switch (mNextScene) {
		case eScene_Load:
			pScene = static_cast<cScene*>(new cLoadScene(this));
			break;
		case eScene_Title:
			pScene = static_cast<cScene*>(new cTitleScene(this));
			break;
		case eScene_Game:
			pScene = static_cast<cScene*>(new cGameScene(this));
			break;
		}
		mNextScene = eScene_None;
		pScene->Initialize();
	}
	pScene->Update();
}

void cSceneManager::Draw() {
	pScene->Draw();
}

void cSceneManager::ChangeScene(eScene NextScene) {
	mNextScene = NextScene;
}