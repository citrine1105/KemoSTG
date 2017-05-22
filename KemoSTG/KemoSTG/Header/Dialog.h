#pragma once
#include "Include.h"
#include "Timer.h"
#include "StringResource.h"

enum eDialogIcon {
	eDialogIcon_Information,		// iマーク
	eDialogIcon_Question,		// ?マーク
	eDialogIcon_Exclamation,		// !マーク
	eDialogIcon_Error,			// ×マーク
	eDialogIcon_Wait,			// 回転
	eDialogIcon_None				// アイコンなし
};

enum eButtonState {
	eButtonState_Off,	// 押されていない
	eButtonState_On,		// 押されている
	eButtonState_Hover,	// 選択されている

	eButtonState_TotalNum	// ボタン状態の総数
};

enum eButtonSelect {
	eButtonSelect_Yes,	// 「はい」が選択された
	eButtonSelect_No,	// 「いいえ」が選択された
	eButtonSelect_None	// 選択されていない
};

class cDialog : public iInitialization, iActivity {
protected:
	cStringResource mMessage;	// メッセージテキスト
	eDialogIcon mIcon;	// アイコン
	bool fActive;		// 有効フラグ

	void ButtonDraw(const cStringResource ) {};	// ボタン描画(仕様未定)
public:
	cDialog();	// デフォルトコンストラクタ
	cDialog(const cStringResource Message);	// メッセージ指定コンストラクタ
	~cDialog();	// デストラクタ

	virtual void Show();		// 表示する
	void Hide();		// 隠す
	virtual void Initialize() override;		// 初期化処理
	virtual void Initialize(const cStringResource Message, const eDialogIcon Icon = eDialogIcon_None);	// 要素を指定して初期化
	virtual void Finalize() override;		// 終了処理
	virtual void Update() override;	// 更新処理
	virtual void Draw() override;	// 描画処理
};	// 通常ダイアログ

class cOKDialog : public cDialog {
protected:
	bool fDecide;	// 決定フラグ
public:
	cOKDialog();		// デフォルトコンストラクタ
	cOKDialog(const cStringResource Message);	// メッセージ指定コンストラクタ
	~cOKDialog();	// デストラクタ

	bool GetDecideFlag();	// ボタンを押したか調べる

	virtual void Initialize() override;	// 初期化処理
	virtual void Finalize() override;	// 終了処理
	virtual void Update() override;	// 更新処理
	virtual void Draw() override;	// 描画処理
};	// OKボタンダイアログ

class cTimerDialog : public cDialog {
protected:
	cTimer mTimer;	// タイマー
public:
	cTimerDialog();		// デフォルトコンストラクタ
	~cTimerDialog();		// デストラクタ

	void SetHideTime(const int Value);			// 隠すまでの時間を設定
	void SetHideTime(const double Second);		// 隠すまでの時間を秒単位で設定

	virtual void Show() override;
	virtual void Initialize() override;	// 初期化処理
	virtual void Finalize() override;	// 終了処理
	virtual void Update() override;	// 更新処理
	virtual void Draw() override;	// 描画処理
};	// 自動消滅ダイアログ

class cYesNoDialog : public cDialog {
protected:
	eButtonSelect mSelect;	// カーソル
	cStringResource mYes;	// はい
	cStringResource mNo;		// いいえ
public:
	cYesNoDialog();		// デフォルトコンストラクタ
	~cYesNoDialog();		// デストラクタ

	virtual void Initialize() override;
	virtual void Finalize() override;
};