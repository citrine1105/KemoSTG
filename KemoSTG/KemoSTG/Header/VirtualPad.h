#pragma once
#include "Include.h"
#include "Pad.h"

enum eButtonAssign {
	eButton_Shot,		// ショット
	eButton_Possess,		// 憑依
	eButton_Bomb,		// ボム
	eButton_FullAuto,	// 連射
	eButton_Pause,		// ポーズ
	eButton_Coin,		// コイン
	eButton_Service,		// サービス
	eButton_TotalNum		// 総要素数
};

enum eDPadAssign {
	eDPad_Up,		// 上
	eDPad_Down,		// 下
	eDPad_Left,		// 左
	eDPad_Right,		// 右
	eDPad_TotalNum	// 総要素数
};

class cVirtualPad : public iInitialization, iActivity {
protected:
	cPad *pPad;		// 入力に使用するパッドのポインタ
	unsigned char mKeyAssign[eButton_TotalNum];				// キーボード配置
	unsigned char mDPadKeyAssign[eButton_TotalNum];			// 方向キー配置
	eDirectInputAssign mDirectInputAssign[eButton_TotalNum];	// DirectInputボタン配置
	eXInputAssign mXInputAssign[eButton_TotalNum];			// XInputボタン配置
	unsigned AUTO_INT mButtonInputState[eButton_TotalNum];	// ボタンが押されているフレーム
	unsigned AUTO_INT mDPadInputState[eDPad_TotalNum];		// 方向キーが押されているフレーム
	int mStickDeadZone;		// スティック・トリガーの入力を無視する範囲
public:
	cVirtualPad();			// デフォルトコンストラクタ
	cVirtualPad(cPad *Pad);	// パッド指定コンストラクタ
	~cVirtualPad();			// デストラクタ

	void SetDefaultAssign(const int Type = 0);	// デフォルト配置に戻す
	void SetJoyPad(cPad *Pad);	// パッドを指定
	void SetButtonAssign(const eButtonAssign Assign, const unsigned char Key);
	void SetButtonAssign(const eButtonAssign Assign, const eDirectInputAssign Button);
	void SetButtonAssign(const eButtonAssign Assign, const eXInputAssign Button);
	void SetDPadAssign(const eDPadAssign Assign, const unsigned char Key);
	cPad* GetJoyPad();			// パッドのポインタを取得
	unsigned AUTO_INT GetInputState(const eButtonAssign Button);	// ボタンの入力状態を取得
	unsigned AUTO_INT GetInputState(const eDPadAssign Button);	// ボタンの入力状態を取得
	void ResetInputState();	// ボタンの入力状態をリセットする

	void Initialize() override;	// 初期化処理
	void Finalize() override;	// 終了処理
	void Update() override;		// 更新
	void Draw() override;		// 描画
};