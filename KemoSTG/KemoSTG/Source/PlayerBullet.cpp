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
	//this->mPosition.AddPosition(0.0, -23.5);	// 応急処置
	cBullet::Update();	// この関数自体に問題あり!
}

void cPlayerBullet::Draw() {
	switch (mType) {
	default:
		DrawRotaGraph(mPosition.GetX(), mPosition.GetY(), 1.0, mMoveVector.GetAngle(), cImageResourceContainer::GetInstance()->GetElement(eImage_PlayerBullet)->GetHandle(), TRUE);
		break;
	}
}