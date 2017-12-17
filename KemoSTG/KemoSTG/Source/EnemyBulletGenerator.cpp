#include "../Header/EnemyBulletGenerator.h"

cEnemyBulletGenerator::cEnemyBulletGenerator()
	: pTargetContainer(nullptr) {
	mBuffer.clear();
}

cEnemyBulletGenerator::~cEnemyBulletGenerator() {
	mBuffer.clear();
}
void cEnemyBulletGenerator::SetOutputTarget(std::list<cEnemyBullet> *Container) {
	pTargetContainer = Container;
}

void cEnemyBulletGenerator::AddBullet(cEnemyBullet &Bullet) {
	mBuffer.push_back(Bullet);
}

void cEnemyBulletGenerator::AddBullet(std::list<cEnemyBullet> &Bullet) {
	for (auto &i : Bullet) {
		mBuffer.push_back(i);
	}
}

void cEnemyBulletGenerator::AddBullet(std::vector<cEnemyBullet> &Bullet) {
	for (auto &i : Bullet) {
		mBuffer.push_back(i);
	}
}

void cEnemyBulletGenerator::Generate() {
	for (auto &i : mBuffer) {
		i.SetPosition(mPosition);	// 座標設定
		i.GetColliderPointer()->at(0).SetPosition(mPosition);
	}
	if (pTargetContainer != nullptr) {
		for (auto &i : mBuffer) {
			pTargetContainer->push_back(i);	// 出力
		}
		mBuffer.clear();
	}
}

void cEnemyBulletGenerator::Clear() {
	mBuffer.clear();
}