#pragma once
#pragma once
#include "Include.h"

enum eFontIndex {
	eFont_MainInterfaceFont,		// UI等(ローカライズ)
	eFont_GlobalInterfaceFont,		// UI等(共通)
	eFont_GameFont,		// ゲーム画面
	eFont_GameCaption,	// ゲーム画面のセリフ等
	eFont_TimerFont,		// タイマーフォント
	eFont_MiniTimerFont,		// 小タイマーフォント

	eFont_None	// 総要素数
};

class cFontContainer : public iInitialization {
private:
	cFontContainer() {
		this->Initialize();
	}
	cFontContainer(const cFontContainer& r) {}
	cFontContainer& operator=(const cFontContainer& r) {}
	~cFontContainer() {
		this->Finalize();
	}
protected:
	std::vector<int> mFontArray;
public:
	static cFontContainer* GetInstance() {
		static cFontContainer inst;
		return &inst;
	}

	int GetElement(eFontIndex Index);
	void SetElement(eFontIndex Index, const int Value);

	void Initialize() override;
	void Finalize() override;
};