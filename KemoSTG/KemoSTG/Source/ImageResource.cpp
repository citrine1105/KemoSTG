#include "../Header/ImageResource.h"

cImageResource::cImageResource() {
	this->Initialize();
}

cImageResource::cImageResource(const TCHAR *FileName) {
	this->Initialize();
	this->SetPath(FileName);
}

cImageResource::~cImageResource() {
	this->Finalize();
}

void cImageResource::Load() {
	this->Load(mPath.c_str());
}

void cImageResource::Load(const TCHAR *FileName) {
	this->Delete();
	mPath = FileName;
	mHandle = LoadGraph(FileName);
}

void cImageResource::Delete() {
	DeleteGraph(mHandle);
	mHandle = NULL;
}

void cImageResource::SetPath(const TCHAR *Path) {
	mPath = Path;
}

int cImageResource::GetHandle() {
	return mHandle;
}

void cImageResource::Initialize() {
	this->Delete();
	mPath.clear();
}

void cImageResource::Finalize() {
	this->Delete();
	mPath.clear();
}