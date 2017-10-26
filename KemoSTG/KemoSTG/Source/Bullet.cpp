#include "../Header/Bullet.h"

void cBullet::Erase() {
	fActive = false;
}

bool cBullet::GetActiveFlag() {
	return fActive;
}

void cBullet::Initialize() {

}

void cBullet::Initialize(cPoint2D &Position, cVector2D &MoveVector) {
	mPosition = Position;
	mMoveVector = MoveVector;
}

void cBullet::Update() {
	this->Move();
	cSprite::Update();
}