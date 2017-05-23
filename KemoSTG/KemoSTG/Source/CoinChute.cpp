#include "../Header/CoinChute.h"

cCoinChute::cCoinChute() {
	this->Initialize();
}

cCoinChute::cCoinChute(const int Coin) {
	this->Initialize();
	this->SetNeedCoinTo1Credit(Coin);
}

cCoinChute::~cCoinChute() {
	this->Finalize();
}

void cCoinChute::SetNeedCoinTo1Credit(const int Coin) {
	if (Coin >= 10) {
		mNeedCoinToCredit = 9;
	}
	else if (Coin <= -10) {
		mNeedCoinToCredit = -9;
	}
	else {
		mNeedCoinToCredit = Coin;
	}
}

void cCoinChute::UseCredit() {
	if (mCredit > 0U) {
		--mCredit;
	}
}

void cCoinChute::AddCoin() {
	if (!this->GetFreePlayFlag() && mCredit < MAX_CREDIT) {
		++mCoin;
		if (mNeedCoinToCredit > 0 && mCoin >= static_cast<unsigned int>(mNeedCoinToCredit)) {
			++mCredit;
			mCoin -= mNeedCoinToCredit;
		}
		else if (mNeedCoinToCredit < 0) {
			mCredit += abs(mNeedCoinToCredit);
			--mCoin;
		}
	}
	if (mCredit > MAX_CREDIT) {
		mCredit = MAX_CREDIT;
	}
}

bool cCoinChute::GetFreePlayFlag() {
	return mNeedCoinToCredit == 0 ? true : false;
}

unsigned int cCoinChute::GetCoin() {
	return mCoin;
}

unsigned int cCoinChute::GetCredit() {
	return mCredit;
}

unsigned int cCoinChute::GetNeedStartCoin() {
	if (!this->GetFreePlayFlag() && mCredit <= 0U) {
		if (mNeedCoinToCredit >= 2) {
			return static_cast<unsigned int>(mNeedCoinToCredit) - mCoin;
		}
		else {
			return 1U;
		}
	}
	return 0U;
}

int cCoinChute::GetNeedCoinTo1Credit() {
	return mNeedCoinToCredit;
}

void cCoinChute::Initialize() {
	mCoin = 0U;
	mCredit = 0U;
	mNeedCoinToCredit = 1;
}

void cCoinChute::Finalize() {
	mCoin = 0U;
	mCredit = 0U;
	mNeedCoinToCredit = 0;
}