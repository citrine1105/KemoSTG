#pragma once
#include "Include.h"

class cSoundResource : public iInitialization {
protected:
	int mHandle;
	int mBufferNum;
	std::tstring mPath;
public:
	cSoundResource();
	cSoundResource(const TCHAR *FileName, const int BufferNum = 3);
	~cSoundResource();

	void Load();
	void Load(const TCHAR *FileName, const int BufferNum = 3);
	void Delete();
	void SetPath(const TCHAR *Path);
	void SetBufferNum(const int BufferNum);
	void SetVolume(const int Volume);
	int GetHandle();

	void Initialize() override;
	void Finalize() override;
};