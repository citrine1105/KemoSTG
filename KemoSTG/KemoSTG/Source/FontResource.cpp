#include "../Header/FontResource.h"

cFontResource::cFontResource() {
	this->Initialize();
}

cFontResource::~cFontResource() {
	this->Finalize();
}

void cFontResource::Load() {
	this->Delete();
	SetFontCacheUsePremulAlphaFlag(fPremulAlpha);
	if (mPath.empty()) {
		mHandle = CreateFontToHandle(mName.c_str(), mSize, mThickness, mFontType, mCharSet, mEdgeThickness, FALSE);
	}
	else {
		mHandle = LoadFontDataToHandle(mPath.c_str(), mEdgeThickness);
	}
	SetFontCacheUsePremulAlphaFlag(FALSE);
}

void cFontResource::Delete() {
	if (mHandle != NULL) {
		DeleteFontToHandle(mHandle);
	}
	mHandle = NULL;
}

void cFontResource::SetProperty(const TCHAR *Name, const int Size, const int Thickness, const int FontType, const int CharSet, const int EdgeThickness, const bool Italic, const bool PremulAlpha) {
	this->SetFontName(Name);
	this->SetSize(Size);
	this->SetThickness(Thickness);
	this->SetFontType(FontType);
	this->SetEdgeThickness(EdgeThickness);
	this->SetCharSet(CharSet);
	this->SetItalicFlag(Italic);
	this->SetPremulAlphaFlag(PremulAlpha);
}

void cFontResource::SetFontName(const TCHAR *Name) {
	mName = Name;
}

void cFontResource::SetPath(const TCHAR *Path) {
	mPath = Path;
}

void cFontResource::SetSize(const int Size) {
	mSize = Size;
}

void cFontResource::SetThickness(const int Thickness) {
	mThickness = Thickness;
}

void cFontResource::SetEdgeThickness(const int EdgeThickness) {
	mEdgeThickness = EdgeThickness;
}

void cFontResource::SetFontType(const int FontType) {
	mFontType = FontType;
}

void cFontResource::SetCharSet(const int CharSet) {
	mCharSet = CharSet;
}

void cFontResource::SetItalicFlag(const bool Italic) {
	fItalic = Italic;
}

void cFontResource::SetPremulAlphaFlag(const bool PremulAlpha) {
	fPremulAlpha = PremulAlpha;
}

int cFontResource::GetHandle() {
	return mHandle;
}

std::tstring cFontResource::GetFontName() {
	std::tstring tFontName;
	tFontName = GetFontNameToHandle(mHandle);
	return tFontName;
}

int cFontResource::GetSize() {
	return GetFontSizeToHandle(mHandle);
}

int cFontResource::GetThickness() {
	int tThickness;
	GetFontStateToHandle(nullptr, nullptr, &tThickness, mHandle);
	return tThickness;
}

int cFontResource::GetEdgeThickness() {
	return GetFontEdgeSizeToHandle(mHandle);
}

int cFontResource::GetFontType() {
	int tFontType;
	GetFontStateToHandle(nullptr, nullptr, nullptr, mHandle, &tFontType);
	return tFontType;
}

int cFontResource::GetCharSet() {
	int tCharSet;
	GetFontStateToHandle(nullptr, nullptr, nullptr, mHandle, nullptr, &tCharSet);
	return tCharSet;
}

bool cFontResource::GetItalicFlag() {
	int tItalic;
	GetFontStateToHandle(nullptr, nullptr, nullptr, mHandle, nullptr, nullptr, nullptr, &tItalic);
	return fItalic;
}

bool cFontResource::GetPremulAlphaFlag() {
	return fPremulAlpha;
}

void cFontResource::Initialize() {
	this->Delete();
	mName.clear();
	mPath.clear();
	mSize = -1;
	mThickness = -1;
	mEdgeThickness = -1;
	mFontType = DX_FONTTYPE_NORMAL;
	mCharSet = DX_CHARSET_DEFAULT;
	fItalic = false;
	fPremulAlpha = false;
}

void cFontResource::Finalize() {
	this->Delete();
	mName.clear();
	mPath.clear();
	mSize = -1;
	mThickness = -1;
	mEdgeThickness = -1;
	mFontType = DX_FONTTYPE_NORMAL;
	mCharSet = DX_CHARSET_DEFAULT;
	fItalic = false;
	fPremulAlpha = false;
}