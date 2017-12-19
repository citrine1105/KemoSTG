#pragma once
#include "PlayerBullet.h"
#include "EnemyBullet.h"

class cGameManager : public iInitialization, iActivity {
private:
	cGameManager();
	cGameManager(const cGameManager& r) {};
	cGameManager& operator=(const cGameManager& r) {}
	~cGameManager();
protected:
	cSprite mBulletOutCollider;	// 弾画面外判定用

	std::array<cPlayer, 2> mPlayer;	// 自機
	std::list<cEnemy> mEnemy;	// 敵
	std::list<cPlayerBullet> mPlayerBullet;	// 自機弾
	std::list<cEnemyBullet> mEnemyBullet;	// 敵弾
public:
	static cGameManager* GetInstance() {
		static cGameManager inst;
		return &inst;
	}

	std::array<cPlayer, 2>* GetPlayerPointer();
	std::list<cEnemy>* GetEnemyPointer();
	std::list<cPlayerBullet>* GetPlayerBulletPointer();
	std::list<cEnemyBullet>* GetEnemyBulletPointer();

	void Initialize() override;
	void Finalize() override;
	void Update() override;
	void Draw() override;
};