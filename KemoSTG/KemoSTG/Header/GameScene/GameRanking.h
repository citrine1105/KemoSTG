#pragma once
#include "../GameBaseScene.h"
#include "../Player.h"

class cRankingGameScene : public cGameBaseScene {
private:
	cTimer mTimer;			// 経過時間

	std::array<cSprite, 10> mSprite;
	std::array<struct sScoreData, 10> mScore;
public:
	cRankingGameScene(iSceneChanger<eGameScene> *Changer);
	~cRankingGameScene();

	void Initialize() override;
	void Finalize() override;
	void Update() override;
	void Draw() override;
};