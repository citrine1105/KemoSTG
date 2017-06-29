#pragma once
#include "Include.h"
#include "SceneChanger.h"
#include "Scene.h"

class cSceneManager : public iSceneChanger<eScene>, iInitialization, iActivity {
protected:
	cScene *pScene;
	eScene mNextScene;
public:
	cSceneManager();
	void Initialize() override;
	void Finalize() override;
	void Update() override;
	void Draw() override;

	void ChangeScene(eScene NextScene) override;
};