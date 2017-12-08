#include "../Header/StringResource.h"

cStringResource::cStringResource() {
	this->Initialize();
}

cStringResource::~cStringResource() {
	this->Finalize();
}

void cStringResource::SetString(const eLanguage Language, const TCHAR *String) {
	mString.at(Language) = String;
}

std::tstring* cStringResource::GetString() {
	switch (GetUserDefaultUILanguage()) {
	case MAKELANGID(LANG_JAPANESE, SUBLANG_JAPANESE_JAPAN):
		return &mString.at(eLanguage_Japanese);	// 日本語の場合
		break;
	case MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US):
		return &mString.at(eLanguage_English);		// 英語の場合
		break;
	default:
		return &mString.at(eLanguage_English);		// それ以外の言語
		break;
	}	// 条件分岐は設定に依存するように変更してください
}

std::tstring* cStringResource::GetString(const eLanguage Language) {
	return &mString.at(Language);	// 任意の言語
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