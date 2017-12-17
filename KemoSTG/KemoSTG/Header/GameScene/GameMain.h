#pragma once
#include "../GameBaseScene.h"
#include "../Player.h"
#include "../Enemy.h"
#include "../PlayerBullet.h"
#include "../EnemyBullet.h"
#include "../SelectTimer.h"

extern cImageResourceContainer gGameUIImageContainer;
extern cSoundResource gGameBGM;

enum eGameUIIndex {
	eGameUI_Life,
	eGameUI_Bomb,
	eGameUI_ScoreBoard,
	eGameUI_RateNumber,
	eGameUI_LifeGauge,
	eGameUI_WordBackground,
	eGameUI_CaptionBomb,
	eGameUI_CaptionTime,
	eGameUI_GameOver,

	eGameUI_TotalNum
};

class cMainGameScene : public cGameBaseScene {
protected:
	cTimer mTimer;			// 経過時間
	cTimer mDelayTimer;		// 処理落ちタイマー
	cTimer mBombAnimeTimer;	// 残りボムのアニメーション用
	cSprite mBackground;	// 背景
	cSprite mFade;			// フェードアウト用
	cSelectTimer mBossTimer;	// ボス戦残り時間

	cSprite mBulletOutCollider;	// 弾画面外判定用

	std::array<cImageResource, 3> mCharacterImage;	// 立ち絵

	std::array<cPlayer, 2> mPlayer;	// 自機
	std::list<cEnemy> mEnemy;	// 敵
	std::list<cPlayerBullet> mPlayerBullet;	// 自機弾
	std::list<cEnemyBullet> mEnemyBullet;	// 敵弾
public:
	cMainGameScene(iSceneChanger<eGameScene> *Changer);
	~cMainGameScene();

	void Initialize() override;
	void Finalize() override;
	void Update() override;
	void Draw() override;
};