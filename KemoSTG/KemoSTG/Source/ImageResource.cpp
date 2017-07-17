#include "../Header/ImageResource.h"

void cImageResource::CreateHandle(const int Num) {
	if (Num == 1) {
		pHandle = new int;
	}
	else {
		pHandle = new int[Num];
	}
}

cImageResource::cImageResource() : pHandle(nullptr) {
	this->Initialize();
}

cImageResource::cImageResource(const TCHAR *FileName) : pHandle(nullptr) {
	this->Initialize();
	this->SetPath(FileName);
}

cImageResource::cImageResource(const TCHAR *FileName, const int TotalNum, const int NumX, const int NumY, const int SizeX, const int SizeY) : pHandle(nullptr) {
	this->Initialize();
	this->SetPath(FileName);
	this->SetDivisionSize(TotalNum, NumX, NumY, SizeX, SizeY);
}

cImageResource::~cImageResource() {
	this->Finalize();
}

void cImageResource::Load() {
	if (mTotalNum == 1) {
		this->Load(mPath.c_str());
	}
	else {
		this->Load(mPath.c_str(), mTotalNum, mNumX, mNumY, mSizeX, mSizeY);
	}
}

void cImageResource::Load(const TCHAR *FileName) {
	this->Delete();
	mPath = FileName;
	mTotalNum = 1;
	this->CreateHandle(1);
	*pHandle = LoadGraph(FileName);
	//GetGraphSize(*pHandle, &mSizeX, &mSizeY);
}

void cImageResource::Load(const TCHAR *FileName, const int TotalNum, const int NumX, const int NumY, const int SizeX, const int SizeY) {
	this->Delete();
	mPath = FileName;
	mTotalNum = TotalNum;
	mNumX = NumX;
	mNumY = NumY;
	mSizeX = SizeX;
	mSizeY = SizeY;
	this->CreateHandle(TotalNum);
	LoadDivGraph(FileName, TotalNum, NumX, NumY, SizeX, SizeY, pHandle);
}

void cImageResource::Delete() {
	if (pHandle != nullptr) {
		if (mTotalNum == 1) {
			DeleteGraph(*pHandle);
			delete pHandle;
		}
		else {
			for (int i = 0; i < mTotalNum; i++) {
				DeleteGraph(pHandle[i]);
			}
			delete[] pHandle;
		}
		pHandle = nullptr;
	}
}

void cImageResource::SetPath(const TCHAR *Path) {
	mPath = Path;
}

void cImageResource::SetDivisionSize(const int TotalNum, const int NumX, const int NumY, const int SizeX, const int SizeY) {
	mTotalNum = TotalNum;
	mNumX = NumX;
	mNumY = NumY;
	mSizeX = SizeX;
	mSizeY = SizeY;
}

int cImageResource::GetHandle(const int Num) {
	if (pHandle != nullptr && mTotalNum > Num && Num >= 0) {
		return pHandle[Num];
	}
	else {
		return -1;
	}
}

void cImageResource::GetSize(int *SizeX, int *SizeY) {
	int tSizeX, tSizeY;

	GetGraphSize(pHandle[0], &tSizeX, &tSizeY);

	if (SizeX != nullptr) {
		*SizeX = tSizeX;
	}
	if (SizeY != nullptr) {
		*SizeY = tSizeY;
	}
}

int cImageResource::GetSizeX() {
	int tSizeX;
	this->GetSize(&tSizeX, nullptr);
	return tSizeX;
}

int cImageResource::GetSizeY() {
	int tSizeY;
	this->GetSize(nullptr, &tSizeY);
	return tSizeY;
}

void cImageResource::Initialize() {
	mTotalNum = 1;
	this->Delete();
	mPath.clear();
	mNumX = 0;
	mNumY = 0;
	mSizeX = 0;
	mSizeY = 0;
}

void cImageResource::Finalize() {
	this->Delete();
	mPath.clear();
	mTotalNum = 0;
	mNumX = 0;
	mNumY = 0;
	mSizeX = 0;
	mSizeY = 0;
}