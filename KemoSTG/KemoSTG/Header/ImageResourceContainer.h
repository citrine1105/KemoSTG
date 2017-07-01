#pragma once
#include "ImageResource.h"

enum eImageIndex {
	eImage_GameLogo,
	eImage_SelectTimer,

	eImage_None
};

class cImageResourceContainer : public iInitialization {
private:
	cImageResourceContainer() {
		this->Initialize();
	}
	cImageResourceContainer(const cImageResourceContainer& r) {}
	cImageResourceContainer& operator=(const cImageResourceContainer& r) {}
	~cImageResourceContainer() {
		this->Finalize();
	}
protected:
	std::vector<cImageResource> mImageArray;
public:
	static cImageResourceContainer* GetInstance() {
		static cImageResourceContainer inst;
		return &inst;
	}

	cImageResource* GetElement(eImageIndex Imdex);

	void Initialize() override;
	void Finalize() override;
};