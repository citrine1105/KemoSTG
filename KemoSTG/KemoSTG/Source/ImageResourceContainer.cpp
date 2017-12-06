#include "../Header/ImageResourceContainer.h"

cImageResourceContainer::cImageResourceContainer() {
	this->Initialize();
}

cImageResourceContainer::~cImageResourceContainer() {
	this->Finalize();
}

void cImageResourceContainer::Load() {
	for (auto &i : mImageArray) {
		i.Load();
	}
}

void cImageResourceContainer::Delete() {
	for (auto &i : mImageArray) {
		i.Delete();
	}
}

unsigned int cImageResourceContainer::GetResourceCount() {
	return mImageArray.size();
}

cImageResource* cImageResourceContainer::GetElement(const unsigned int Index) {
	return &mImageArray.at(Index);
}

void cImageResourceContainer::Initialize() {
	mImageArray.clear();
}

void cImageResourceContainer::Initialize(const unsigned int Num) {
	for (auto &i : mImageArray) {
		i.Delete();
	}
	mImageArray.clear();
	mImageArray.resize(Num);
}

void cImageResourceContainer::Finalize() {
	for (auto &i : mImageArray) {
		i.Finalize();
	}
	mImageArray.clear();
}