#include "../Header/Bullet.h"

void cBullet::Erase() {
	fActive = false;
}

bool cBullet::GetActiveFlag() {
	return fActive;
}

void cBullet::Initialize() {

}

void cBullet::Initialize(cVector2D &MoveVector) {
	mMoveVector = MoveVector;
}

void cBullet::Update() {
	this->Move();
	cSprite::Update();
}