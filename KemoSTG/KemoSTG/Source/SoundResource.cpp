#include "../Header/SoundResource.h"

cSoundResource::cSoundResource() {
	this->Initialize();
}

cSoundResource::cSoundResource(const TCHAR *FileName, const int BufferNum) {
	this->Initialize();
	this->SetPath(FileName);
}

cSoundResource::~cSoundResource() {
	this->Finalize();
}

void cSoundResource::Load() {
	mHandle = LoadSoundMem(mPath.c_str(), mBufferNum);
}

void cSoundResource::Load(const TCHAR *FileName, const int BufferNum) {
	mPath = FileName;
	mHandle = LoadSoundMem(mPath.c_str(), BufferNum);
}

void cSoundResource::Delete() {
	DeleteSoundMem(mHandle);
	mHandle = NULL;
}

void cSoundResource::SetPath(const TCHAR *Path) {
	mPath = Path;
}

void cSoundResource::SetBufferNum(const int BufferNum) {
	mBufferNum = BufferNum;
}

void cSoundResource::SetVolume(const int Volume) {
	ChangeVolumeSoundMem(Volume, mHandle);
}

int cSoundResource::GetHandle() {
	return mHandle;
}

void cSoundResource::Initialize() {
	this->Delete();
	this->SetBufferNum(3);
	mPath.clear();
}

void cSoundResource::Finalize() {
	this->Delete();
	this->SetBufferNum(0);
	mPath.clear();
}