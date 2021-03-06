﻿#pragma once
#include "Include.h"
#include "Keyboard.h"
#include "Pad.h"

enum eButtonAssign {
	eButton_Shot,		// ショット
	eButton_Possess,	// 憑依
	eButton_Bomb,		// ボム
	eButton_FullAuto,	// 連射
	eButton_Pause,		// ポーズ
	eButton_Coin,		// コイン
	eButton_Service,	// サービス

	eButton_Decide,		// 決定
	eButton_Cancel,		// キャンセル

	eButton_TotalNum	// 総要素数
};

enum eDPadAssign {
	eDPad_Up,		// 上
	eDPad_Down,		// 下
	eDPad_Left,		// 左
	eDPad_Right,	// 右
	eDPad_TotalNum	// 総要素数
};

struct sVirtualPadInputState {
public:
	sVirtualPadInputState();
	std::array<bool, eButton_TotalNum> mButton;
	std::array<bool, eDPad_TotalNum> mDPad;
};

class cVirtualPad : public iInitialization, iActivity {
protected:
	cPad *pPad;		// 入力に使用するパッドのポインタ
	sVirtualPadInputState mButtonState;	// ボタン押下状態
	std::array<unsigned char, eButton_TotalNum> mKeyAssign;				// キーボード配置
	std::array<unsigned char, eButton_TotalNum> mDPadKeyAssign;			// 方向キー配置
	std::array<eDirectInputAssign, eButton_TotalNum> mDirectInputAssign;	// DirectInputボタン配置
	std::array<eXInputAssign, eButton_TotalNum> mXInputAssign;			// XInputボタン配置
	std::array<unsigned AUTO_INT, eButton_TotalNum> mButtonInputState;	// ボタンが押されているフレーム
	std::array<unsigned AUTO_INT, eButton_TotalNum> mDPadInputState;		// 方向キーが押されているフレーム
	int mStickDeadZone;		// スティック・トリガーの入力を無視する範囲
	bool fVibration;		// 振動機能フラグ
public:
	cVirtualPad();			// デフォルトコンストラクタ
	cVirtualPad(cPad *Pad);	// パッド指定コンストラクタ
	~cVirtualPad();			// デストラクタ

	void SetDefaultAssign(const int Type = 0);	// デフォルト配置に戻す
	void SetJoyPad(cPad *Pad);	// パッドを指定
	void SetKeyAssign(const eButtonAssign Assign, const unsigned char Key);	// キー配置設定
	void SetKeyAssign(const eDPadAssign Assign, const unsigned char Key);	// 十字キー配置設定
	void SetButtonAssign(const eButtonAssign Assign, const eDirectInputAssign Button);	// DirectInputボタン配置設定
	void SetButtonAssign(const eButtonAssign Assign, const eXInputAssign Button);		// XInputボタン配置設定
	void SetVibrationFlag(const bool Flag);		// 振動機能設定
	void SetButtonState(const sVirtualPadInputState &State);	// ボタンの入力状態を指定(リプレイ再生用)
	cPad* GetJoyPad();			// パッドのポインタを取得
	unsigned AUTO_INT GetInputState(const eButtonAssign Button);	// ボタンの入力状態を取得
	unsigned AUTO_INT GetInputState(const eDPadAssign Button);	// 十字ボタンの入力状態を取得
	unsigned char GetKeyAssign(const eButtonAssign Assign);	// キー配置を取得
	unsigned char GetKeyAssign(const eDPadAssign Assign);	// 十字キー配置を取得
	eDirectInputAssign GetDirectInputAssign(const eButtonAssign Assign);	// DirectInputボタン配置を取得
	eXInputAssign GetXInputAssign(const eButtonAssign Assign);			// XInputボタン配置を取得
	bool GetVibrationFlag();		// 振動機能設定取得
	const sVirtualPadInputState GetButtonState();	// ボタンの押下状態をまとめて取得
	void StartVibration(const int Power, const int Time);	// 振動を開始する
	void StopVibration();	// 振動を止める
	void ResetInputState();	// ボタンの入力状態をリセットする

	void Initialize() override;	// 初期化処理
	void Finalize() override;	// 終了処理
	void Update() override;		// 更新
	void Draw() override;		// 描画
};