#include "../Header/ImageResourceContainer.h"

cImageResource* cImageResourceContainer::GetElement(eImageIndex Index) {
	return &mImageArray[Index];
}

void cImageResourceContainer::Initialize() {
	mImageArray.resize(eImageIndex::eImage_None);
}

void cImageResourceContainer::Finalize() {
	for (auto &i : mImageArray) {
		i.Finalize();
	}
	mImageArray.clear();
}