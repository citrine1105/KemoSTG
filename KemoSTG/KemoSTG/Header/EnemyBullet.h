#pragma once
#include "Bullet.h"
#include "Enemy.h"
#include "Player.h"

enum eBulletType {
	eBullet_Normal,		// 通常弾
	eBullet_Arrow,		// 矢弾

	eBullet_TotalNum	// 総要素数
};

class cEnemyBullet : public cBullet {
protected:
	eBulletType mType;
	cPlayer *pTargetPlayer;
public:
	void Initialize(cPoint2D &Position, cVector2D &MoveVector, const eBulletType Type);
	void Update() override;
};