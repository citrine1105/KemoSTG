#pragma once
#include "../Scene.h"
#include "../GameSceneManager.h"

class cGameScene : public cScene {
protected:
	int mGameScreen;
	cGameSceneManager mGame;
public:
	cGameScene(iSceneChanger<eScene> *Changer);
	~cGameScene();

	void Initialize() override;
	void Finalize() override;
	void Update() override;
	void Draw() override;
};