#include "../Header/SoundResourceContainer.h"

cSoundResourceContainer::cSoundResourceContainer() {
	this->Initialize();
}

cSoundResourceContainer::~cSoundResourceContainer() {
	this->Finalize();
}

void cSoundResourceContainer::Resize(const int Num) {
	mSoundArray.resize(Num);
}

cSoundResource* cSoundResourceContainer::GetElement(const int Num) {
	return &mSoundArray.at(Num);
}

void cSoundResourceContainer::Initialize() {

}

void cSoundResourceContainer::Initialize(const int Num) {
	this->Resize(Num);
}

void cSoundResourceContainer::Finalize() {
	mSoundArray.clear();
}