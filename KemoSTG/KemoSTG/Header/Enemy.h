#pragma once
//#include "Sprite.h"
#include "EnemyBulletGenerator.h"

extern cImageResourceContainer gEnemyImageContainer;

enum eEnemyType {
	eEnemy_Zako,

	eEnemy_TotalNum
};

struct sEnemyRegisterData {
public:
	eEnemyType mType;	// 敵の種類
	double mAppearanceX;	// 出現地点X
	double mAppearanceY;	// 出現地点Y
	int mMovePattern;	// 動きのパターン
	int mGeneratorPattern;	// 弾源パターン
	int mBulletPattern;	// 弾幕パターン
};

struct sEnemyPointMoveData : public sPointMoveData {
public:
	unsigned int mTiming;
};

struct sEnemyPolarFormMoveData : public sPolarFormMoveData {
public:
	unsigned int mTiming;
};

class cEnemy : public cSprite {
protected:
	bool fActive;
	eEnemyType mType;	// 種類
	int mLife;	// 体力
	int mMotion;	// 動き
	cTimer mMotionTimer;	// 経過時間
	cTimer mAnimeTimer;	// アニメーション用タイマー
	std::vector<class cEnemyBulletGenerator> mBulletGenerator;	// 弾発射機構
	std::vector<cVector2D> mBulletGeneratorVector;	// 弾源移動制御用ベクトル
	std::list<sEnemyPointMoveData> mPointMoveData;	// 移動データ
	std::list<sEnemyPolarFormMoveData> mPolarFormMoveData;	// 移動データ
public:
	cEnemy();
	cEnemy(sEnemyRegisterData &Data);
	~cEnemy();

	void Damage(const int Damage);
	void Erase();

	void SetBulletGenerateTarget(std::list<class cEnemyBullet> *Container);	// 弾の出力先を指定
	int GetLife();
	bool GetActiveFlag();
	bool GetAliveFlag();
	void Initialize() override;
	void Initialize(const sEnemyRegisterData &Data);
	void Update() override;
	void Draw() override;
};