#pragma once
#include "BulletGenerator.h"
#include "PlayerBullet.h"

class cPlayerBulletGenerator : public cSprite, iBulletGenerator {
protected:
	std::list<class cPlayerBullet> mBuffer;
	std::list<class cPlayerBullet> *pTargetContainer;
public:
	cPlayerBulletGenerator();
	~cPlayerBulletGenerator();

	void SetOutputTarget(std::list<class cPlayerBullet> *Container);	// 自機弾の出力先を設定
	void AddBullet(class cPlayerBullet &Bullet);	// バッファに弾を追加
	void AddBullet(std::list<class cPlayerBullet> &Bullet);	// ↑のlist版
	void AddBullet(std::vector<class cPlayerBullet> &Bullet);	// ↑のvector版
	void Generate() override;	// 弾を生成
	void Clear() override;	// バッファを消去
};