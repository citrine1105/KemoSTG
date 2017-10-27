#pragma once
#include "Sprite.h"
#include "PlayerBulletGenerator.h"
#include "VirtualPad.h"
#include "Scene/Game.h"

enum ePlayerCharacter {
	ePlayer_Rin,
	ePlayer_Boy,

	ePlayer_TotalNum
};

enum ePossessType {
	ePossess_Half,	// 半憑依
	ePossess_Full,	// 全憑依

	ePossess_None
};

struct sScoreData {
	std::string mName;
	unsigned int mScore;
	unsigned char mContinue;
	unsigned int mMaxRate;
	ePlayerCharacter mCharacter;
	ePossessType mType;
	bool operator<(sScoreData &Score) const {
		if (mScore == Score.mScore) {
			if (mMaxRate == Score.mMaxRate) {
				return mContinue > Score.mContinue;
			}
			else {
				return mMaxRate < Score.mMaxRate;
			}
		}
		else {
			return mScore < Score.mScore;
		}
	}
};

class cPlayer : public cSprite {
protected:
	bool fEntry;		// エントリーフラグ
	bool fAlive;		// 生存フラグ
	cTimer mInvincibleTime;	// 無敵時間
	cTimer mPossessTime;		// 残り憑依時間
	cVirtualPad *pInputPad;	// 入力処理用パッド
	unsigned char mLife;		// 体力
	unsigned char mBomb;		// ボム
	unsigned int mScoreRate;	// スコア倍率
	sScoreData mScore;		// スコア
	std::list<cPlayerBulletGenerator> mBulletGenerator;	// 弾発射機構
public:
	cPlayer();
	~cPlayer();

	void SetInputPad(cVirtualPad *Pad);
	bool GetEntryFlag();
	bool GetAliveFlag();
	double GetPossessGauge();
	unsigned char GetLife();
	unsigned char GetBomb();
	unsigned int GetScoreRate();
	const sScoreData GetScore();

	void Initialize() override;
	void Update() override;
	void Draw() override;
};