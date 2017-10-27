#pragma once
#include "BulletGenerator.h"
#include "PlayerBullet.h"

class cPlayerBulletGenerator : public cSprite, iBulletGenerator {
protected:
	std::list<cPlayerBullet> mBuffer;
public:
	cPlayerBulletGenerator();
	~cPlayerBulletGenerator();

	void AddBullet(cPlayerBullet &Bullet);
	// TODO: listやarrayで追加するメゾッドも作る
	void Generate() override;
	void Clear() override;
};