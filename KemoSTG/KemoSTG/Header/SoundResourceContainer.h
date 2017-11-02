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

	void Resize(const int Num);
	cSoundResource* GetElement(const int Num);

	void Initialize() override;
	void Initialize(const int Num);
	void Finalize() override;
};

static cSoundResourceContainer gBGMContainer;
static cSoundResourceContainer gSEContainer;