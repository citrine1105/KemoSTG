#pragma once
#include "Bullet.h"
//#include "Player.h"
#include "Enemy.h"

class cPlayerBullet : public cBullet {
protected:
	enum ePlayerCharacter mType;
	class cEnemy *pTargetEnemy;
public:
	cPlayerBullet();

	void Initialize(cVector2D &MoveVector, const enum ePlayerCharacter Type);
	void Update() override;
	void Draw() override;
};