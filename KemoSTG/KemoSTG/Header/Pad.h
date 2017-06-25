#pragma once
#include "Include.h"

enum eDirectInputAssign {
	eDirectInputAssign_Button1,
	eDirectInputAssign_Button2,
	eDirectInputAssign_Button3,
	eDirectInputAssign_Button4,
	eDirectInputAssign_Button5,
	eDirectInputAssign_Button6,
	eDirectInputAssign_Button7,
	eDirectInputAssign_Button8,
	eDirectInputAssign_Button9,
	eDirectInputAssign_Button10,
	eDirectInputAssign_Button11,
	eDirectInputAssign_Button12,
	eDirectInputAssign_Button13,
	eDirectInputAssign_Button14,
	eDirectInputAssign_Button15,
	eDirectInputAssign_Button16,
	eDirectInputAssign_Button17,
	eDirectInputAssign_Button18,
	eDirectInputAssign_Button19,
	eDirectInputAssign_Button20,
	eDirectInputAssign_Button21,
	eDirectInputAssign_Button22,
	eDirectInputAssign_Button23,
	eDirectInputAssign_Button24,
	eDirectInputAssign_Button25,
	eDirectInputAssign_Button26,
	eDirectInputAssign_Button27,
	eDirectInputAssign_Button28,
	eDirectInputAssign_Button29,
	eDirectInputAssign_Button30,
	eDirectInputAssign_Button31,
	eDirectInputAssign_Button32,
	eDirectInputAssign_X,
	eDirectInputAssign_Y,
	eDirectInputAssign_Z,
	eDirectInputAssign_Rx,
	eDirectInputAssign_Ry,
	eDirectInputAssign_Rz,
	eDirectInputAssign_POV1,
	eDirectInputAssign_POV2,
	eDirectInputAssign_POV3,
	eDirectInputAssign_POV4,
	eDirectInputAssign_Slider1,
	eDirectInputAssign_Slider2,
	eDirectInputAssign_TotalNum
};

enum eXInputAssign {
	eXInputAssign_LeftX,
	eXInputAssign_LeftY,
	eXInputAssign_RightX,
	eXInputAssign_RightY,
	eXInputAssign_LT,
	eXInputAssign_RT,
	eXInputAssign_DPadUp,
	eXInputAssign_DPadDown,
	eXInputAssign_DPadLeft,
	eXInputAssign_DPadRight,
	eXInputAssign_Start,
	eXInputAssign_Back,
	eXInputAssign_LeftStickButton,
	eXInputAssign_RightStickButton,
	eXInputAssign_LB,
	eXInputAssign_RB,
	eXInputAssign_A,
	eXInputAssign_B,
	eXInputAssign_X,
	eXInputAssign_Y,
	eXInputAssign_TotalNum
};

class cPad : public iInitialization, iActivity {
protected:
	int mPadNumber;
	bool fXInput;
	std::tstring mInstanceName;
	std::tstring mProductName;
	DINPUT_JOYSTATE mDirectInputState;
	XINPUT_STATE mXInputState;
public:
	cPad();
	cPad(const int PadNum);
	~cPad();

	void SetJoyPadNum(const int PadNum);	// パッドの番号を指定する
	int GetJoyPadNum();		// パッドの番号を取得
	bool GetActiveFlag();	// パッドが接続されているか確認
	std::tstring GetJoyPadInstanceName();	// パッドのインスタンス名を取得
	std::tstring GetJoyPadProductName();		// パッドの製品名を取得
	bool GetXInputFlag();	// XInput対応か調べる
	int GetJoyPadInputState(eDirectInputAssign Assign);	// DirectInputの入力状態を取得
	int GetJoyPadInputState(eXInputAssign Assign);		// XInputの入力状態を取得
	void ResetInputState();	// 入力状態をクリアする

	void Initialize() override;	// 初期化処理
	void Finalize() override;	// 終了処理
	void Update() override;		// 更新
	void Draw() override;		// 描画
};