﻿#pragma once
#include "../GameBaseScene.h"
#include "../Player.h"
#include "../Enemy.h"
#include "../PlayerBullet.h"
#include "../EnemyBullet.h"
#include "../SelectTimer.h"

class cMainGameScene : public cGameBaseScene {
private:
	cTimer mTimer;			// 経過時間
	cTimer mBombAnimeTimer;	// 残りボムのアニメーション用
	cSprite mBackground;	// 背景
	cSelectTimer mBossTimer;	// ボス戦残り時間

	cSprite mBulletOutCollider;	// 弾画面外判定用

	std::array<cPlayer, 2> mPlayer;	// 自機
	std::list<cEnemy> mEnemy;	// 敵
	std::list<cPlayerBullet> mPlayerBullet;	// 自機弾
	std::list<cEnemyBullet> mEnemyBullet;	// 敵弾
public:
	cMainGameScene(iSceneChanger<eGameScene> *Changer);
	~cMainGameScene();

	void Initialize() override;
	void Finalize() override;
	void Update() override;
	void Draw() override;
};