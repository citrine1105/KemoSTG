#include "../Header/PlayerBullet.h"

cPlayerBullet::cPlayerBullet() 
	: pTargetEnemy(nullptr), mType(ePlayer_TotalNum) {

}

int cPlayerBullet::GetPower() {
	switch (mType) {
	case ePlayer_Rin:
		return 5;
		break;
	case ePlayer_Boy:
		return 3;
		break;
	default:
		return 1;
		break;
	}
}

void cPlayerBullet::Initialize(cVector2D &MoveVector, const ePlayerCharacter Type) {
	cBullet::Initialize(MoveVector);
	mType = Type;
	fActive = true;
	mCollider.resize(1);
	mCollider.at(0).SetRange(24.0, 48.0);
}

void cPlayerBullet::Update() {
	if (pTargetEnemy != nullptr) {	// 目標の敵がいたら
		mMoveVector.SetAngle(this->GetAngleToSprite(*pTargetEnemy));	// その敵を追尾する
	}
	cBullet::Update();
}

void cPlayerBullet::Draw() {
	switch (mType) {
	default:
		DrawRotaGraphF(mPosition.GetX(), mPosition.GetY(), 1.0, mMoveVector.GetAngle(), cImageResourceContainer::GetInstance()->GetElement(eImage_PlayerBullet)->GetHandle(), TRUE);
		break;
	}
}