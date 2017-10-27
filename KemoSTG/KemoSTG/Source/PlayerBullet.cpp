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
	cSprite::Draw();	// テスト
}