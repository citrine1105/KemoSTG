#include "../Header/Enemy.h"

cEnemy::cEnemy() : mLife(50) {
	this->Initialize();
}

cEnemy::~cEnemy() {

}

void cEnemy::Damage(const int Damage) {
	if (Damage > 0) {
		mLife -= Damage;
	}
}

void cEnemy::SetBulletGenerateTarget(std::list<cEnemyBullet> *Container) {
	for (auto &i : mBulletGenerator) {
		i.SetOutputTarget(Container);	// 弾の出力先を設定
	}
}

int cEnemy::GetLife() {
	return mLife;
}

bool cEnemy::GetAliveFlag() {
	if (mLife <= 0) {
		return false;
	}
	return true;
}

void cEnemy::Initialize() {
	mCollider.resize(1);
	mCollider.at(0).SetRange(32.0, 32.0);
	mCollider.at(0).SetCollisionType(eCollision_Rectangle);
	mAnimeTimer.Start();
	mBulletGenerator.resize(1);
	mBulletGeneratorVector.resize(1);
}

void cEnemy::Update() {
	cSprite::Update();
	// 弾源
	for (auto &i : mBulletGeneratorVector) {
		i.SetStartPoint(mPosition);
	}

	for (int i = 0; i < mBulletGenerator.size(); i++) {
		mBulletGenerator.at(i).SetPosition(mBulletGeneratorVector.at(i).GetEndPoint());	// 座標セット
	}

	for (int i = 0; i < mBulletGenerator.size(); i++) {
		cEnemyBullet tBullet;	// 弾
		cVector2D tMoveVector;	// 弾移動速度
		tMoveVector.SetPolarForm(TO_RADIAN(GetRand(360)), 3.2);
		for (int j = 0; j < 1; j++) {
			tMoveVector.AddAngle(TO_RADIAN(360.0 / 1.0));
			tBullet.Initialize(tMoveVector, eBullet_Normal);
			mBulletGenerator.at(i).AddBullet(tBullet);
		}

		mBulletGenerator.at(i).Generate();
	}
}

void cEnemy::Draw() {
	cSprite::Draw();
}