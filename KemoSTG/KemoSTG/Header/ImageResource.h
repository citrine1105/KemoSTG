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

	void CreateHandle(const int Num);
public:
	cImageResource();
	cImageResource(const TCHAR *FileName);
	cImageResource(const TCHAR *FileName, const int TotalNum, const int NumX, const int NumY, const int SizeX, const int SizeY);
	~cImageResource();

	void Load();
	void Load(const TCHAR *FileName);
	void Load(const TCHAR *FileName, const int TotalNum, const int NumX, const int NumY, const int SizeX, const int SizeY);
	void Delete();
	void SetPath(const TCHAR *Path);
	void SetDivisionSize(const int TotalNum, const int NumX, const int NumY, const int SizeX, const int SizeY);
	int GetHandle(const int Num = 0);
	void GetSize(int *SizeX, int *SizeY);
	int GetSizeX();
	int GetSizeY();

	void Initialize() override;
	void Finalize() override;
};