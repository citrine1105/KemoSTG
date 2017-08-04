#include "../Header/Bullet.h"

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