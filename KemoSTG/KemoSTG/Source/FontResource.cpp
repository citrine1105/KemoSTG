#include "../Header/FontResource.h"

cFontResource::cFontResource() {
	this->Initialize();
}

cFontResource::~cFontResource() {
	this->Finalize();
}

void cFontResource::Load() {
	this->Delete();
	if (mPath.empty()) {
		mHandle = CreateFontToHandle(mName.c_str(), mSize, mThickness, mFontType, -1, mEdgeThickness, FALSE);
	}
	else {
		mHandle = LoadFontDataToHandle(mPath.c_str(), mEdgeThickness);
	}
}

void cFontResource::Delete() {
	if (mHandle != NULL) {
		DeleteFontToHandle(mHandle);
	}
	mHandle = NULL;
}

void cFontResource::SetFontName(const TCHAR *Name) {
	mName = Name;
}

void cFontResource::SetPath(const TCHAR *Path) {
	mPath = Path;
}

int cFontResource::GetHandle() {
	return mHandle;
}

unsigned int cFontResource::GetSize() {
	return mSize;
}

void cFontResource::Initialize() {
	this->Delete();
	mName.clear();
	mPath.clear();
	mSize = -1;
	mThickness = -1;
	mEdgeThickness = -1;
	mFontType = DX_FONTTYPE_NORMAL;
}

void cFontResource::Finalize() {
	this->Delete();
	mName.clear();
	mPath.clear();
	mSize = -1;
	mThickness = -1;
	mEdgeThickness = -1;
	mFontType = DX_FONTTYPE_NORMAL;
}