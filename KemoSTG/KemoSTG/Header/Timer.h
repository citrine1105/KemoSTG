#pragma once
#include "Include.h"

enum eCountMode {
	eCountMode_CountUp,		// カウントアップ
	eCountMode_CountDown		// カウントダウン
};	// カウント方法

class cTimer : public iInitialization, iActivity {
protected:
	AUTO_INT mValue;	// 数値
	AUTO_INT mDefaultValue;	// デフォルト時の数値
	eCountMode mCountMode;	// カウント方法
	bool fActive;	// カウント有効フラグ
	//bool fLoopCount;	// 繰り返しカウントフラグ
public:
	cTimer();	// デフォルトコンストラクタ
	cTimer(const AUTO_INT Value);	// 値指定コンストラクタ
	cTimer(const double Second);		// 秒指定コンストラクタ
	cTimer(const AUTO_INT Value, const eCountMode CountMode);	// 値とカウントモード指定コンストラクタ
	cTimer(const double Second, const eCountMode CountMode);		// 秒とカウントモード指定コンストラクタ
	~cTimer();	// デストラクタ

	void SetValue(const AUTO_INT Value);	// 値を設定
	void SetSecond(const double Second);	// 値を秒単位で設定
	void SetDefaultValue(const AUTO_INT Value);	// 初期値を設定
	void SetDefaultSecond(const double Second);	// 初期値を秒単位で設定
	void SetCountMode(const eCountMode Mode);	// カウント方法を指定
	//void SetLoopCountFlag(const bool Flag);	// 繰り返しカウントの有無を設定
	void AddValue(const AUTO_INT Value);	// 値を加算
	void AddSecond(const double Second);	// 値を秒単位で加算
	AUTO_INT GetValue();	// 値を取得
	double GetSecond();		// 秒単位の値を取得
	eCountMode GetCountMode();	// カウント方法を取得

	void operator = (const AUTO_INT Value);	// 値を設定
	void operator = (const double Value);	// 値を秒単位で設定
	void operator += (const AUTO_INT Value);	// 値を加算
	void operator += (const double Value);	// 値を秒単位で加算
	void operator -= (const AUTO_INT Value);	// 値を減算
	void operator -= (const double Value);	// 値を秒単位で減算

	void Start();	// カウント開始
	void Stop();	// カウント停止
	void Reset();	// 値をデフォルト値に戻す
	void Initialize() override;	// 初期化処理
	void Finalize() override;	// 終了処理
	void Update() override;	// 更新処理
	virtual void Draw() override;	// 描画処理(ここでは未定義)
};