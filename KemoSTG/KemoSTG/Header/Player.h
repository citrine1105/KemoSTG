#pragma once
//#include "Sprite.h"
#include "PlayerBulletGenerator.h"
#include "VirtualPad.h"
#include "Scene/Game.h"

enum ePlayerCharacter {
	ePlayer_Rin,	// 神谷倫
	ePlayer_Kakeru,	// 風巻翔
	ePlayer_3rd,	// 3人目

	ePlayer_TotalNum
};

enum ePossessType {
	ePossess_Half,	// 半憑依
	ePossess_Full,	// 全憑依

	ePossess_None
};

struct sScoreData {
	std::tstring mName;
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

extern cImageResourceContainer gPlayerImageContainer;

class cPlayer : public cSprite {
protected:
	bool fEntry;		// エントリーフラグ
	//bool fAlive;		// 生存フラグ
	bool fSlowMove;		// 低速移動フラグ
	cTimer mInvincibleTime;	// 無敵時間
	cTimer mPossessTime;		// 残り憑依時間
	cVirtualPad *pInputPad;	// 入力処理用パッド
	double mMoveSpeed;		// 移動速度
	unsigned char mLife;		// 体力
	unsigned char mBomb;		// ボム
	unsigned int mScoreRate;	// スコア倍率
	sScoreData mScore;		// スコア
	cTimer mAnimeTimer;	// アニメーション用タイマー
	std::vector<class cPlayerBulletGenerator> mBulletGenerator;	// 弾発射機構
	std::vector<cVector2D> mBulletGeneratorVector;	// 弾源移動制御用ベクトル

	int Sound;	// ショット音(削除して)
public:
	cPlayer();
	~cPlayer();

	void Entry();	// エントリー
	void Bomb();	// ボム使用処理
	void Damage();	// ダメージ処理
	void Continue();	// コンティニュー処理

	void SetInputPad(cVirtualPad *Pad);
	void SetBulletGenerateTarget(std::list<class cPlayerBullet> *Container);	// 弾の出力先を指定
	bool GetEntryFlag();
	bool GetAliveFlag();
	double GetPossessGauge();
	unsigned char GetLife();
	unsigned char GetBomb();
	unsigned int GetScoreRate();
	const sScoreData GetScore();
	bool GetPossessFlag();
	bool GetInvincibleFlag();
	void AddScore(const unsigned int Score);
	void AddScoreRate(const unsigned int ScoreRate);

	void Initialize() override;
	void Update() override;
	void Draw() override;
};