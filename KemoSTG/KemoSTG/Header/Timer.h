#pragma once
#include "Include.h"

enum eCountMode {
	eCountMode_CountUp,		// カウントアップ
	eCountMode_CountDown		// カウントダウン
};	// カウント方法

class cTimer : public iInitialization, iActivity {
protected:
	AUTO_INT mTime;	// 数値
	AUTO_INT mDefaultTime;	// デフォルト時の数値
	AUTO_INT mMaxTime;
	eCountMode mCountMode;	// カウント方法
	bool fActive;	// カウント有効フラグ
	bool fLoop;	// 繰り返しカウントフラグ
public:
	cTimer();	// デフォルトコンストラクタ
	//cTimer(const AUTO_INT Time);	// 値指定コンストラクタ
	//cTimer(const double Second);		// 秒指定コンストラクタ
	//cTimer(const AUTO_INT Time, const eCountMode CountMode);	// 値とカウントモード指定コンストラクタ
	//cTimer(const double Second, const eCountMode CountMode);		// 秒とカウントモード指定コンストラクタ
	cTimer(const AUTO_INT Time, const AUTO_INT MaxTime = AUTO_INT_MAX, const eCountMode CountMode = eCountMode_CountUp, const bool Loop = false);
	cTimer(const double Second, const double MaxSecond = AUTO_INT_MAX * REFRESH_RATE, const eCountMode CountMode = eCountMode_CountUp, const bool Loop = false);
	~cTimer();	// デストラクタ

	void SetTime(const AUTO_INT Time);	// 値を設定
	void SetSecond(const double Second);	// 値を秒単位で設定
	void SetDefaultTime(const AUTO_INT Time);	// 初期値を設定
	void SetDefaultSecond(const double Second);	// 初期値を秒単位で設定
	void SetMaxTime(const AUTO_INT MaxTime);	// 上限値を設定
	void SetMaxSecond(const double MaxSecond);	// 上限値を秒単位で設定
	void SetCountMode(const eCountMode Mode);	// カウント方法を指定
	void SetLoopFlag(const bool Flag);	// 繰り返しカウントの有無を設定
	void AddTime(const AUTO_INT Time);	// 値を加算
	void AddSecond(const double Second);	// 値を秒単位で加算
	AUTO_INT GetTime();	// 値を取得
	double GetSecond();		// 秒単位の値を取得
	AUTO_INT GetMaxTime();	// 最大値を取得
	double GetMaxSecond();	// 最大値を秒単位で取得
	eCountMode GetCountMode();	// カウント方法を取得
	bool GetActiveFlag();	// 有効フラグの取得

	void operator=(const AUTO_INT Time);	// 値を設定
	void operator=(const double Time);	// 値を秒単位で設定
	void operator+=(const AUTO_INT Time);	// 値を加算
	void operator+=(const double Time);	// 値を秒単位で加算
	void operator-=(const AUTO_INT Time);	// 値を減算
	void operator-=(const double Time);	// 値を秒単位で減算

	void Start();	// カウント開始
	void Stop();	// カウント停止
	void Reset();	// 値をデフォルト値に戻す
	virtual void Initialize() override;	// 初期化処理
	void Initialize(const AUTO_INT Time, const AUTO_INT MaxTime = AUTO_INT_MAX, const eCountMode CountMode = eCountMode_CountUp, const bool Loop = false);
	void Initialize(const double Second, const double MaxSecond = AUTO_INT_MAX * REFRESH_RATE, const eCountMode CountMode = eCountMode_CountUp, const bool Loop = false);
	virtual void Finalize() override;	// 終了処理
	virtual void Update() override;	// 更新処理
	virtual void Draw() override;	// 描画処理(ここでは未定義)
};