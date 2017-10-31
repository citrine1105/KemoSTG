#include "../Header/EnemyBullet.h"

cEnemyBullet::cEnemyBullet() 
	: pTarget(nullptr) {
	mCollider.resize(1);
}

cEnemyBullet::~cEnemyBullet() {

}

void cEnemyBullet::Initialize(cVector2D &MoveVector, const eBulletType Type) {
	cBullet::Initialize(MoveVector);
	mType = Type;
	// 判定範囲指定
	switch (mType) {
	case eBullet_Normal:
		mCollider.at(0).SetCollisionType(eCollision_Ellipse);
		mCollider.at(0).SetRange(20.0, 20.0);
		break;
	default:
		mCollider.at(0).SetCollisionType(eCollision_Ellipse);
		mCollider.at(0).SetRange(200.0, 200.0);
		break;
	}
}

void cEnemyBullet::Update() {
	if (pTarget != nullptr) {	// 目標の敵がいたら
		mMoveVector.SetAngle(this->GetAngleToSprite(*pTarget));	// プレイヤーを追尾する
	}
	cBullet::Update();
}

void cEnemyBullet::Draw() {
	switch (mType) {
	default:
		DrawRotaGraphF(mPosition.GetX(), mPosition.GetY(), 1.0, 0.0, cImageResourceContainer::GetInstance()->GetElement(eImage_EnemyBullet)->GetHandle(), TRUE);
		break;
	}
}