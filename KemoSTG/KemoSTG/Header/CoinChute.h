#pragma once
#include "Include.h"
#include <cmath>
#define MAX_CREDIT 9U	// 最大クレジット数

class cCoinChute : public iInitialization {
protected:
	unsigned int mCoin;	// 投入されたコイン数
	unsigned int mCredit;	// 所持しているクレジット数
	int mNeedCoinToCredit;	// 1クレジットに必要なコイン数
public:
	cCoinChute();	// デフォルトコンストラクタ
	cCoinChute(const int NeedCoinToCredit);	// コイン数指定コンストラクタ
	~cCoinChute();	// デストラクタ

	void SetNeedCoinTo1Credit(const int Coin);	// 1クレジットに必要なコイン数を設定する
	void UseCredit();	// クレジットを消費する
	void AddCoin();		// コインを投入する
	bool GetFreePlayFlag();	// フリープレイ設定か調べる
	unsigned int GetCoin();	// 現在のコイン数を取得する
	unsigned int GetCredit();	// 現在のクレジット数を取得する
	unsigned int GetNeedStartCoin();	// ゲーム開始に必要なコイン数を取得
	int GetNeedCoinTo1Credit(); // 1クレジットに必要なコイン数を取得する

	void Initialize() override;	// 初期化処理
	void Finalize() override;	// 終了処理
};