#include "../Header/PlayerBullet.h"

cImageResourceContainer gPlayerBulletImageContainer;
cSoundResourceContainer gPlayerShotSoundContainer;

cPlayerBullet::cPlayerBullet() 
	: pTargetEnemy(nullptr), mType(ePlayer_TotalNum) {

}

int cPlayerBullet::GetPower() {
	switch (mType) {
	case ePlayer_Rin:
		return 5;
		break;
	case ePlayer_Kakeru:
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
	DrawRotaGraphF(mPosition.GetX(), mPosition.GetY(), 1.0, mMoveVector.GetAngle(), gPlayerBulletImageContainer.GetElement(mType)->GetHandle(), TRUE);
}