#pragma once
#include "Bullet.h"
//#include "Enemy.h"
#include "Player.h"

enum eBulletType {
	eBullet_Normal,		// 通常弾
	eBullet_Arrow,		// 矢弾

	eBullet_TotalNum	// 総要素数
};

extern cImageResourceContainer gEnemyBulletImageContainer;

class cEnemyBullet : public cBullet {
protected:
	enum eBulletType mType;
	class cSprite *pTarget;
public:
	cEnemyBullet();
	~cEnemyBullet();

	void Initialize(cVector2D &MoveVector, const enum eBulletType Type);
	void Update() override;
	void Draw() override;
};