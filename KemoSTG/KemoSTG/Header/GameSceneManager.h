#pragma once
#include "Include.h"
#include "SceneChanger.h"
#include "GameBaseScene.h"

class cGameSceneManager : public iSceneChanger<eGameScene>, iInitialization, iActivity {
protected:
	cGameBaseScene *pScene;
	eGameScene mNowScene;
	eGameScene mNextScene;

	bool fPause;
public:
	cGameSceneManager();

	void Pause();

	bool GetPauseFlag();
	eGameScene GetNowScene();

	void Initialize() override;
	void Finalize() override;
	void Update() override;
	void Draw() override;

	void SetVirtualPad(cVirtualPad Pad[2]);

	void ChangeScene(eGameScene NextScene) override;
};