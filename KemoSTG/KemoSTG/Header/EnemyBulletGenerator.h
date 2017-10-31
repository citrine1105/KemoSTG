#pragma once
#include "BulletGenerator.h"
#include "EnemyBullet.h"

class cEnemyBulletGenerator : public cSprite, iBulletGenerator {
protected:
	std::list<class cEnemyBullet> mBuffer;
	std::list<class cEnemyBullet> *pTargetContainer;
public:
	cEnemyBulletGenerator();
	~cEnemyBulletGenerator();

	void SetOutputTarget(std::list<class cEnemyBullet> *Container);	// 敵弾の出力先を設定
	void AddBullet(class cEnemyBullet &Bullet);	// バッファに弾を追加
	void AddBullet(std::list<class cEnemyBullet> &Bullet);	// ↑のlist版
	void AddBullet(std::vector<class cEnemyBullet> &Bullet);	// ↑のvector版
	void Generate() override;	// 弾を生成
	void Clear() override;	// バッファを消去
};