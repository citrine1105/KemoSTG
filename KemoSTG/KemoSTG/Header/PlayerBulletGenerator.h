#pragma once
#include "BulletGenerator.h"
#include "PlayerBullet.h"

class cPlayerBulletGenerator : public cSprite, iBulletGenerator {
protected:
	std::list<cPlayerBullet> mBuffer;
	std::list<cPlayerBullet> *pTargetContainer;
public:
	cPlayerBulletGenerator();
	~cPlayerBulletGenerator();

	void SetOutputTarget(std::list<cPlayerBullet> *Container);
	void AddBullet(cPlayerBullet &Bullet);
	// TODO: listやarrayで追加するメゾッドも作る
	void Generate() override;
	void Clear() override;
};