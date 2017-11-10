#pragma once
#include "Include.h"

class cKeyboard : public iInitialization, iActivity {
private:
	cKeyboard();
	cKeyboard(const cKeyboard& r) {};
	cKeyboard& operator=(const cKeyboard& r) {}
	~cKeyboard();
protected:
	std::array<char, 256> mKeyPushState;
	std::array<unsigned AUTO_INT, 256> mKeyPushTime;
public:
	static cKeyboard* GetInstance() {
		static cKeyboard inst;
		return &inst;
	}

	bool GetKeyPushState(const int Key);
	unsigned AUTO_INT GetKeyPushTime(const int Key);
	bool GetKeyPushStateOnce(const int Key);

	void Initialize() override;
	void Finalize() override;
	void Update() override;
	void Draw() override;
};