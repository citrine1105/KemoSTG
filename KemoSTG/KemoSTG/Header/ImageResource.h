#pragma once
#include "Include.h"

class cImageResource : public iInitialization {
protected:
	int *pHandle;
	std::tstring mPath;
	int mTotalNum;
	int mNumX;
	int mNumY;
	int mSizeX;
	int mSizeY;
	bool fPremulAlpha;

	void CreateHandle(const int Num);
public:
	cImageResource();
	cImageResource(const TCHAR *FileName);
	cImageResource(const TCHAR *FileName, const int TotalNum, const int NumX, const int NumY, const int SizeX, const int SizeY, const bool PremulAlpha = false);
	~cImageResource();

	void Load();
	void Load(const TCHAR *FileName);
	void Load(const TCHAR *FileName, const int TotalNum, const int NumX, const int NumY, const int SizeX, const int SizeY, const bool PremulAlpha = false);
	void Delete();
	void SetPath(const TCHAR *Path);
	void SetDivisionSize(const int TotalNum, const int NumX, const int NumY, const int SizeX, const int SizeY);
	void SetPremulAlphaFlag(const bool PremulAlpha);
	int GetHandle(const int Num = 0);
	int GetHandleNum();
	void GetSize(int &SizeX, int &SizeY);
	int GetSizeX();
	int GetSizeY();
	bool GetPremulAlphaFlag();

	void Initialize() override;
	void Finalize() override;
};