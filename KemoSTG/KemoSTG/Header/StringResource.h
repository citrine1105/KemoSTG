#pragma once
#include <string>
#include <tchar.h>
#include "Macro.h"
#include "Initialization.h"
#include <Windows.h>

enum eLanguage {
	eLanguage_Japanese,	// 日本語
	eLanguage_English,	// 英語

	eLanguage_TotalNum	// 言語の総数
};

class cStringResource : public iInitialization {
protected:
	std::tstring mString[eLanguage_TotalNum];	// 文字列本体
public:
	cStringResource();	// デフォルトコンストラクタ
	~cStringResource();	// デストラクタ
	void SetString(const eLanguage Language, const TCHAR *String);	// 文字列を設定
	std::tstring* GetString();	// 文字列を取得
	std::tstring* GetString(const eLanguage Language);	// 任意の言語の文字列を取得

	void Initialize() override;	// 初期化処理
	void Finalize() override;	// 終了処理
};