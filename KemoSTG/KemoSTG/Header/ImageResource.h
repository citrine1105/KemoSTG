#pragma once
#include "Include.h"

class cImageResource : public iInitialization {
protected:
	int mHandle;
	std::tstring mPath;
public:
	cImageResource();
	cImageResource(const TCHAR *FileName);
	~cImageResource();

	void Load();
	void Load(const TCHAR *FileName);
	void Delete();
	void SetPath(const TCHAR *Path);
	int GetHandle();

	void Initialize() override;
	void Finalize() override;
};