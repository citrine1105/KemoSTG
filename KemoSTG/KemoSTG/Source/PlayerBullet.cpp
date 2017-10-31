#include "../Header/PlayerBullet.h"

cPlayerBullet::cPlayerBullet() : pTargetEnemy(nullptr) {

}

void cPlayerBullet::Initialize(cVector2D &MoveVector, const ePlayerCharacter Type) {
	cBullet::Initialize(MoveVector);
	mType = Type;
	fActive = true;
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