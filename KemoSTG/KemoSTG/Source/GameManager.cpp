#include "../Header/GameManager.h"

cGameManager::cGameManager() {
	this->Initialize();
}

cGameManager::~cGameManager() {
	this->Finalize();
}

std::array<cPlayer, 2>* cGameManager::GetPlayerPointer() {
	return &mPlayer;
}

std::list<cEnemy>* cGameManager::GetEnemyPointer() {
	return &mEnemy;
}

std::list<cPlayerBullet>* cGameManager::GetPlayerBulletPointer() {
	return &mPlayerBullet;
}

std::list<cEnemyBullet>* cGameManager::GetEnemyBulletPointer() {
	return &mEnemyBullet;
}

std::list<cEffect>* cGameManager::GetEffectPointer() {
	return &mEffect;
}

void cGameManager::Initialize() {
	mBulletOutCollider.GetColliderPointer()->resize(1);
	mBulletOutCollider.GetColliderPointer()->at(0).SetRange(GAME_SCREEN_WIDTH, GAME_SCREEN_HEIGHT);
	mBulletOutCollider.SetPosition(GAME_SCREEN_WIDTH / 2.0, GAME_SCREEN_HEIGHT / 2.0);
	mBulletOutCollider.GetColliderPointer()->at(0).SetPosition(mBulletOutCollider.GetPosition());

	for (auto &i : mPlayer) {
		i.Initialize();
	}
	mEnemy.clear();
	mPlayerBullet.clear();
	mEnemyBullet.clear();
	mEffect.clear();
	// 自機
	for (auto &i : mPlayer) {
		i.SetBulletGenerateTarget(&mPlayerBullet);
	}
}

void cGameManager::Finalize() {
	for (auto &i : mPlayer) {
		i.Finalize();
	}
	mEnemy.clear();
	mPlayerBullet.clear();
	mEnemyBullet.clear();
	mEffect.clear();
}

void cGameManager::Update() {
	// 自機弾
	for (auto i = mPlayerBullet.begin(); i != mPlayerBullet.end();) {
		i->Update();
		if (!mBulletOutCollider.GetCollisionFlag(*i)) {
			i->Erase();
		}
		else {
			for (auto &j : mEnemy) {
				if (j.GetCollisionFlag(*i)) {
					j.Damage(i->GetPower());
					i->Erase();
					mEffect.push_back(cEffect(eEffect_Bomb, i->GetPosition()));
					if (mPlayer.at(0).GetPossessFlag()) {
						mPlayer.at(0).AddScoreRate(1);
					}
					mPlayer.at(0).AddScore(10 * mPlayer.at(0).GetScoreRate());
				}
			}
		}
		if (!i->GetActiveFlag()) {
			i = mPlayerBullet.erase(i);
			continue;
		}
		i++;
	}

	// 敵弾
	for (auto i = mEnemyBullet.begin(); i != mEnemyBullet.end();) {
		i->Update();
		if (!mBulletOutCollider.GetCollisionFlag(*i)) {
			i->Erase();
		}
		if (!i->GetActiveFlag()) {
			i = mEnemyBullet.erase(i);
			continue;
		}
		i++;
	}

	// 自機
	for (auto &i : mPlayer) {
		if (i.GetAliveFlag()) {
			i.Update();
		}
	}

	// 敵
	for (auto i = mEnemy.begin(); i != mEnemy.end();) {
		i->Update();
		i->SetBulletGenerateTarget(&mEnemyBullet);
		if (!mBulletOutCollider.GetCollisionFlag(*i)) {
			i->Erase();
		}
		if (!i->GetActiveFlag()) {
			i = mEnemy.erase(i);
			continue;
		}
		i++;
	}

	// 自機衝突判定
	for (auto &i : mPlayer) {
		for (auto &j : mEnemyBullet) {
			if (i.GetCollisionFlag(j) && !i.GetInvincibleFlag()) {
				i.Damage();
			}
		}
		for (auto &j : mEnemy) {
			if (i.GetCollisionFlag(j) && !i.GetInvincibleFlag()) {
				i.Damage();
			}
		}
	}

	// エフェクト
	for (auto i = mEffect.begin(); i != mEffect.end();) {
		i->Update();
		if (!i->GetPlayFlag()) {
			i = mEffect.erase(i);
			continue;
		}
		i++;
	}
}

void cGameManager::Draw() {
	for (auto &i : mPlayer) {
		if (i.GetPossessFlag()) {
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, static_cast<int>(255.0 * 40.0 / 100.0));
			DrawBox(0, 0, GAME_SCREEN_WIDTH, GAME_SCREEN_HEIGHT, GetColor(0x6F, 0xCC, 0xCE), TRUE);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
			break;
		}
	}

	// 敵
	for (auto &i : mEnemy) {
		i.Draw();
	}

	// エフェクト
	for (auto &i : mEffect) {
		i.Draw();
	}

	// 自機弾
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, static_cast<int>(255.0 * 60.0 / 100.0));
	for (auto &i : mPlayerBullet) {
		i.Draw();
	}
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);

	// 自機
	for (auto &i : mPlayer) {
		if (i.GetAliveFlag()) {
			i.Draw();
		}
	}

	// 敵弾
	for (auto &i : mEnemyBullet) {
		i.Draw();
	}
}