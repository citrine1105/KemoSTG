#include "../Header/Enemy.h"

cEnemy::cEnemy() {
	this->Initialize();
}

cEnemy::~cEnemy() {

}

void cEnemy::SetBulletGenerateTarget(std::list<cEnemyBullet> *Container) {
	for (auto &i : mBulletGenerator) {
		i.SetOutputTarget(Container);	// 弾の出力先を設定
	}
}

unsigned int cEnemy::GetLife() {
	return mLife;
}

void cEnemy::Initialize() {
	mAnimeTimer.Start();
	mBulletGenerator.resize(1);
	mBulletGeneratorVector.resize(1);
}

void cEnemy::Update() {
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
		tBullet.Initialize(tMoveVector, eBullet_Normal);

		mBulletGenerator.at(i).AddBullet(tBullet);
		mBulletGenerator.at(i).Generate();
	}
}

void cEnemy::Draw() {
	cSprite::Draw();
}