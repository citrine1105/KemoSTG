#include "../Header/SoundResourceContainer.h"

cSoundResourceContainer::cSoundResourceContainer() {
	this->Initialize();
}

cSoundResourceContainer::~cSoundResourceContainer() {
	this->Finalize();
}

void cSoundResourceContainer::Load() {
	for (auto &i : mSoundArray) {
		i.Load();
	}
}

void cSoundResourceContainer::Delete() {
	for (auto &i : mSoundArray) {
		i.Delete();
	}
}

void cSoundResourceContainer::SetVolume(const int Volume) {
	for (auto &i : mSoundArray) {
		i.SetVolume(Volume);
	}
}

void cSoundResourceContainer::Resize(const unsigned int Num) {
	mSoundArray.resize(Num);
}

unsigned int cSoundResourceContainer::GetResourceCount() {
	return mSoundArray.size();
}

cSoundResource* cSoundResourceContainer::GetElement(const int Num) {
	return &mSoundArray.at(Num);
}

void cSoundResourceContainer::Initialize() {
	for (auto &i : mSoundArray) {
		i.Delete();
	}
	mSoundArray.clear();
}

void cSoundResourceContainer::Initialize(const unsigned int Num) {
	for (auto &i : mSoundArray) {
		i.Delete();
	}
	mSoundArray.clear();
	this->Resize(Num);
}

void cSoundResourceContainer::Finalize() {
	for (auto &i : mSoundArray) {
		i.Finalize();
	}
	mSoundArray.clear();
}