#include "../Header/StringResource.h"

cStringResource::cStringResource() {
	this->Initialize();
}

cStringResource::~cStringResource() {
	this->Finalize();
}

void cStringResource::SetString(eLanguage Language, const TCHAR *String) {
	mString[Language] = String;
}

std::tstring* cStringResource::GetString() {
	switch (GetUserDefaultUILanguage()) {
	case MAKELANGID(LANG_JAPANESE, SUBLANG_JAPANESE_JAPAN):
		return &mString[eLanguage_Japanese];	// 日本語の場合
		break;
	case MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US):
		return &mString[eLanguage_English];		// 英語の場合
		break;
	default:
		return &mString[eLanguage_English];		// それ以外の言語
		break;
	}	// 条件分岐は設定に依存するように変更してください
}

std::tstring* cStringResource::GetString(eLanguage Language) {
	return &mString[Language];	// 任意の言語
}

void cStringResource::Initialize() {
	for (int i = 0; i < static_cast<int>(eLanguage_TotalNum); i++) {
		mString[i].clear();
	}
}

void cStringResource::Finalize() {
	for (int i = 0; i < static_cast<int>(eLanguage_TotalNum); i++) {
		mString[i].clear();
	}
}