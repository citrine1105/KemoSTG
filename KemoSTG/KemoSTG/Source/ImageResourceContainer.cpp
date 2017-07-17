#include "../Header/ImageResourceContainer.h"

cImageResource* cImageResourceContainer::GetElement(eImageIndex Index) {
	return &mImageArray[Index];
}

void cImageResourceContainer::Initialize() {
	mImageArray.resize(eImageIndex::eImage_None);
}

void cImageResourceContainer::Finalize() {
	//for (int i = 0; i < eImageIndex::eImage_None; i++) {
	//	mImageArray[i].Finalize();
	//}
	for (auto &i : mImageArray) {
		i.Finalize();
	}
	mImageArray.clear();
}