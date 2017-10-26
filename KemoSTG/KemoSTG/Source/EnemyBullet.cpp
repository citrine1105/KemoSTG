#include "../Header/EnemyBullet.h"

void cEnemyBullet::Initialize(cPoint2D &Position, cVector2D &MoveVector, const eBulletType Type) {

}

void cEnemyBullet::Update() {
	if (pTargetPlayer != nullptr) {	// 目標の敵がいたら
		mMoveVector.SetAngle(this->GetAngleToSprite(*pTargetPlayer));	// プレイヤーを追尾する
	}
	cBullet::Update();
}