#pragma once
#include "ImageResource.h"

class cImageResourceContainer : public iInitialization {
protected:
	std::vector<cImageResource> mImageArray;
public:
	cImageResourceContainer();
	~cImageResourceContainer();

	void Load();
	void Delete();

	void Resize(const unsigned int Num);
	unsigned int GetResourceCount();
	cImageResource* GetElement(const unsigned int Index);

	void Initialize() override;
	void Initialize(const unsigned int Num);
	void Finalize() override;
};