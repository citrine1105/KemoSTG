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
public:
	cFontResource();
	~cFontResource();

	void Load();
	void Delete();

	void SetFontName(const TCHAR *Name);
	void SetPath(const TCHAR *Path);
	int GetHandle();
	unsigned int GetSize();

	void Initialize() override;
	void Finalize() override;
};