#pragma once
#include "Bullet.h"
#include "Player.h"
#include "Enemy.h"

class cPlayerBullet : public cBullet {
protected:
	ePlayerCharacter mType;
	cEnemy *pTargetEnemy;
public:
	void Initialize(cPoint2D &Position, cVector2D &MoveVector, const ePlayerCharacter Type);
	void Update() override;
};