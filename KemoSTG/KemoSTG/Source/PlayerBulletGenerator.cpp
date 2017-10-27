#include "../Header/PlayerBulletGenerator.h"
#include "../Header/GameScene/GameMain.h"

cPlayerBulletGenerator::cPlayerBulletGenerator() 
	: pTargetContainer(nullptr) {
	mBuffer.clear();
}

cPlayerBulletGenerator::~cPlayerBulletGenerator() {
	mBuffer.clear();
}

void cPlayerBulletGenerator::SetOutputTarget(std::list<cPlayerBullet> *Container) {
	pTargetContainer = Container;
}

void cPlayerBulletGenerator::AddBullet(cPlayerBullet &Bullet) {
	mBuffer.push_back(Bullet);
}

void cPlayerBulletGenerator::Generate() {
	for (auto &i : mBuffer) {
		i.SetPosition(mPosition.GetX(), mPosition.GetY());	// 座標設定
	}
	if (pTargetContainer != nullptr) {
		for (auto &i : mBuffer) {
			pTargetContainer->push_back(i);	// 出力
		}
		mBuffer.clear();
	}
}

void cPlayerBulletGenerator::Clear() {
	mBuffer.clear();
}