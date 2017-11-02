#pragma once
//#include "Sprite.h"
#include "EnemyBulletGenerator.h"

class cEnemy : public cSprite {
protected:
	int mLife;	// 体力
	cTimer mAnimeTimer;	// アニメーション用タイマー
	std::vector<class cEnemyBulletGenerator> mBulletGenerator;	// 弾発射機構
	std::vector<cVector2D> mBulletGeneratorVector;	// 弾源移動制御用ベクトル
public:
	cEnemy();
	~cEnemy();

	void Damage(const int Damage);

	void SetBulletGenerateTarget(std::list<class cEnemyBullet> *Container);	// 弾の出力先を指定
	int GetLife();
	bool GetAliveFlag();
	void Initialize() override;
	void Update() override;
	void Draw() override;
};