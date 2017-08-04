#pragma once
#include "../GameBaseScene.h"
#include "../ImageResourceContainer.h"
#include "../Player.h"
#include "../Enemy.h"
#include "../Bullet.h"
#include "../SelectTimer.h"

class cMainGameScene : public cGameBaseScene {
private:
	cTimer mTimer;
	cSprite mBackground;
	cSelectTimer mBossTimer;

	cSprite mBulletOutCollider;

	std::array<cPlayer, 2> mPlayer;
	std::list<cEnemy> mEnemy;
	std::list<cBullet> mBullet;
public:
	cMainGameScene(iSceneChanger<eGameScene> *Changer);
	~cMainGameScene();

	void Initialize() override;
	void Finalize() override;
	void Update() override;
	void Draw() override;
};