#include "../Header/Bullet.h"

cBullet::cBullet() : fActive(true) {
	mCollider.resize(1);
	this->Initialize();
}

cBullet::~cBullet() {

}

void cBullet::Erase() {
	fActive = false;
}

bool cBullet::GetActiveFlag() {
	return fActive;
}

void cBullet::Initialize() {
	for (auto &i : mCollider) {
		i.SetPosition(mPosition);
	}
}

void cBullet::Initialize(cVector2D &MoveVector) {
	this->Initialize();
	mMoveVector = MoveVector;
}

void cBullet::Update() {
	this->Move();
	for (auto &i : mCollider) {
		i.SetPosition(mPosition);
	}
	cSprite::Update();
}