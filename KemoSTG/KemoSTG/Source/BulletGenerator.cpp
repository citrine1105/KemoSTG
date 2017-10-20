#include "../Header/BulletGenerator.h"

cBulletGenerator::cBulletGenerator() {
	mBuffer.clear();
}

cBulletGenerator::~cBulletGenerator() {
	mBuffer.clear();
}

void cBulletGenerator::AddBullet(cBullet &Bullet) {
	mBuffer.push_back(Bullet);
}

void cBulletGenerator::Generate() {
	return;
}

void cBulletGenerator::Clear() {
	mBuffer.clear();
}