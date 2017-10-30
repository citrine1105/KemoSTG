#pragma once
#include "../GameBaseScene.h"
#include "../Player.h"
#include "../Enemy.h"
#include "../PlayerBullet.h"
#include "../SelectTimer.h"

class cMainGameScene : public cGameBaseScene {
private:
	cTimer mTimer;
	cTimer mBombAnimeTimer;
	cSprite mBackground;
	cSelectTimer mBossTimer;

	cSprite mBulletOutCollider;

	std::array<cPlayer, 2> mPlayer;
	std::list<cEnemy> mEnemy;
	std::list<cPlayerBullet> mPlayerBullet;
public:
	cMainGameScene(iSceneChanger<eGameScene> *Changer);
	~cMainGameScene();

	std::list<cPlayerBullet>* GetPlayerBullet();

	void Initialize() override;
	void Finalize() override;
	void Update() override;
	void Draw() override;
};