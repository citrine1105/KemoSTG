#include "../Header/PlayerBullet.h"

void cPlayerBullet::Initialize(cPoint2D &Position, cVector2D &MoveVector, const ePlayerCharacter Type) {
	cBullet::Initialize(Position, MoveVector);
	mType = Type;
}

void cPlayerBullet::Update() {
	if (pTargetEnemy != nullptr) {	// 目標の敵がいたら
		mMoveVector.SetAngle(this->GetAngleToSprite(*pTargetEnemy));	// その敵を追尾する
	}
	cBullet::Update();
}