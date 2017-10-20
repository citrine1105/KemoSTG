#pragma once
#include "Bullet.h"

class cBulletGenerator {
protected:
	std::list<cBullet> mBuffer;
public:
	cBulletGenerator();
	~cBulletGenerator();

	void AddBullet(cBullet &Bullet);	// 要素を追加
	void Generate();	// 弾を生成
	void Clear();	// コンテナの中身を消去
};