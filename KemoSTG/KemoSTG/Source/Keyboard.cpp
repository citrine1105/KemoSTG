#include "../Header/Keyboard.h"

cKeyboard::cKeyboard() {
	this->Initialize();
}

cKeyboard::~cKeyboard() {
	this->Finalize();
}

bool cKeyboard::GetKeyPushState(const int Key) {
	return mKeyPushState.at(Key);
}

unsigned AUTO_INT cKeyboard::GetKeyPushTime(const int Key) {
	return mKeyPushTime.at(Key);
}

bool cKeyboard::GetKeyPushStateOnce(const int Key) {
	if (mKeyPushTime.at(Key) == 1) {
		return true;
	}
	return false;
}

void cKeyboard::Initialize() {
	mKeyPushState.fill(0);
	mKeyPushTime.fill(0);
}

void cKeyboard::Finalize() {
	mKeyPushState.fill(0);
	mKeyPushTime.fill(0);
}

void cKeyboard::Update() {
	GetHitKeyStateAll(mKeyPushState.data());
	for (int i = 0; i < mKeyPushState.size(); i++) {
		if (mKeyPushState.at(i) != 0) {
			mKeyPushTime.at(i)++;
		}
		else {
			mKeyPushTime.at(i) = 0;
		}
	}
}

void cKeyboard::Draw() {

}