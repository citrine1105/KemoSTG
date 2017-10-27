#include "../Header/PlayerBulletGenerator.h"
#include "../Header/GameScene/GameMain.h"

cPlayerBulletGenerator::cPlayerBulletGenerator() {
	mBuffer.clear();
}

cPlayerBulletGenerator::~cPlayerBulletGenerator() {
	mBuffer.clear();
}

void cPlayerBulletGenerator::AddBullet(cPlayerBullet &Bullet) {
	mBuffer.push_back(Bullet);
}

void cPlayerBulletGenerator::Generate() {
	for (auto &i : mBuffer) {
		i.SetPosition(mPosition.GetX(), mPosition.GetY());
	}
}

void cPlayerBulletGenerator::Clear() {
	mBuffer.clear();
}