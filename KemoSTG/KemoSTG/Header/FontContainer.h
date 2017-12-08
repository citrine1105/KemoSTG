#pragma once
#pragma once
#include "FontResource.h"

class cFontContainer : public iInitialization {
protected:
	std::vector<cFontResource> mFontArray;
public:
	cFontContainer();
	~cFontContainer();

	cFontResource* GetElement(const int Index);

	void Resize(const unsigned int Num);
	void Load();
	void Delete();

	void Initialize() override;
	void Initialize(const unsigned int Num);
	void Finalize() override;
};