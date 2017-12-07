#pragma once
#include "SoundResource.h"

enum eBGMIndex {
	eBGM_Menu,

	eBGM_TotalNum
};

enum eSEIndex {
	eSE_Shot,

	eSE_TotalNum
};

class cSoundResourceContainer : public iInitialization {
protected:
	std::vector<cSoundResource> mSoundArray;
public:
	cSoundResourceContainer();
	~cSoundResourceContainer();

	void Load();
	void Delete();

	void Resize(const unsigned int Num);
	void SetVolume(const int Volume);
	unsigned int GetResourceCount();
	cSoundResource* GetElement(const int Num);

	void Initialize() override;
	void Initialize(const unsigned int Num);
	void Finalize() override;
};