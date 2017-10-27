#pragma once
#include "Bullet.h"

class iBulletGenerator {
public:
	virtual ~iBulletGenerator() {};
	virtual void Generate() = 0;	// 弾を生成
	virtual void Clear() = 0;	// コンテナの中身を消去
};