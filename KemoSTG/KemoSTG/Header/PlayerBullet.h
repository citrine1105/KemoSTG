#pragma once
#include "Bullet.h"
//#include "Player.h"
#include "Enemy.h"

extern cImageResourceContainer gPlayerBulletImageContainer;

class cPlayerBullet : public cBullet {
protected:
	enum ePlayerCharacter mType;
	class cEnemy *pTargetEnemy;
public:
	cPlayerBullet();

	int GetPower();	// 攻撃力

	void Initialize(cVector2D &MoveVector, const enum ePlayerCharacter Type);
	void Update() override;
	void Draw() override;
};