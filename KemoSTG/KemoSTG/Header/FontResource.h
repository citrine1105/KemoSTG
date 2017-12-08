#pragma once
#include "Include.h"

class cFontResource : public iInitialization {
protected:
	int mHandle;	// ハンドル実体
	std::tstring mName;	// フォント名
	std::tstring mPath;	// フォントファイルパス(優先)
	int mSize;		// フォントサイズ
	int mThickness;	// 太さ
	int mEdgeThickness;	// 縁取り太さ
	int mFontType;	// フォント種類
	int mCharSet;	// 文字セット
	bool fItalic;	// 斜体フラグ
public:
	cFontResource();
	~cFontResource();

	void Load();
	void Delete();

	void SetProperty(const TCHAR *Name, const int Size = -1, const int Thickness = -1, const int FontType = DX_FONTTYPE_NORMAL, const int CharSet = DX_CHARSET_DEFAULT, const int EdgeThickness = -1, const bool Italic = false);
	void SetFontName(const TCHAR *Name);
	void SetPath(const TCHAR *Path);
	void SetSize(const int Size);
	void SetThickness(const int Thickness);
	void SetEdgeThickness(const int Thickness);
	void SetFontType(const int FontType);
	void SetCharSet(const int CharSet);
	void SetItalicFlag(const bool Italic);
	int GetHandle();
	std::tstring GetFontName();
	int GetSize();
	int GetThickness();
	int GetEdgeThickness();
	int GetFontType();
	int GetCharSet();
	bool GetItalicFlag();

	void Initialize() override;
	void Finalize() override;
};