#include "../Header/EnemyBullet.h"

cImageResourceContainer gEnemyBulletImageContainer;

cEnemyBullet::cEnemyBullet() 
	: pTarget(nullptr) {

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
		mCollider.at(0).SetRange(16.0, 16.0);
		break;
	default:
		mCollider.at(0).SetCollisionType(eCollision_Ellipse);
		mCollider.at(0).SetRange(20.0, 10.0);
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
	case eBullet_Normal:
		DrawRotaGraphF(mPosition.GetX(), mPosition.GetY(), 1.0, 0.0, gEnemyBulletImageContainer.GetElement(mType)->GetHandle(), TRUE);
		break;
	case eBullet_Arrow:
		DrawRotaGraphF(mPosition.GetX(), mPosition.GetY(), 1.0, mMoveVector.GetAngle(), gEnemyBulletImageContainer.GetElement(mType)->GetHandle(), TRUE);
		break;
	default:
		DrawRotaGraphF(mPosition.GetX(), mPosition.GetY(), 1.0, 0.0, gEnemyBulletImageContainer.GetElement(eBullet_Normal)->GetHandle(), TRUE);
		break;
	}
#ifdef _DEBUG
	for (auto &i : cSprite::mCollider) {
		i.Draw();
	}
#endif
}