#include "../Header/FontContainer.h"

cFontContainer::cFontContainer() {
	this->Initialize();
}

cFontContainer::~cFontContainer() {
	this->Finalize();
}

cFontResource* cFontContainer::GetElement(const int Index) {
	return &mFontArray.at(Index);
}

void cFontContainer::Resize(const unsigned int Num) {
	mFontArray.resize(Num);
}

void cFontContainer::Load() {
	for (auto &i : mFontArray) {
		i.Load();
	}
}

void cFontContainer::Delete() {
	for (auto &i : mFontArray) {
		i.Delete();
	}
}

void cFontContainer::Initialize() {
	for (auto &i : mFontArray) {
		i.Delete();
	}
	mFontArray.clear();
}

void cFontContainer::Initialize(const unsigned int Num) {
	this->Initialize();
	mFontArray.resize(Num);
}

void cFontContainer::Finalize() {
	for (auto &i : mFontArray) {
		i.Delete();
	}
	mFontArray.clear();
}