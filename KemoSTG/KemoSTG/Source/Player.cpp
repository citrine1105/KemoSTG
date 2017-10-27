﻿#include "../Header/Player.h"

cPlayer::cPlayer() : cSprite(), fEntry(false), fAlive(false),
	mInvincibleTime(60 * 5, 60 * 5, eCountMode_CountDown), mPossessTime(10.0, 20.0, eCountMode_CountDown),
	pInputPad(nullptr), mLife(3), mBomb(3),
	mScoreRate(1) {
	this->Initialize();
}

cPlayer::~cPlayer() {

}

void cPlayer::SetInputPad(cVirtualPad *Pad) {
	pInputPad = Pad;
}

void cPlayer::SetBulletGenerateTarget(std::list<cPlayerBullet> *Container) {
	for (auto &i : mBulletGenerator) {
		i.SetOutputTarget(Container);	// 弾の出力先を設定
	}
}

bool cPlayer::GetEntryFlag() {
	return fEntry;
}

bool cPlayer::GetAliveFlag() {
	return fAlive;
}

double cPlayer::GetPossessGauge() {
	return static_cast<double>(mPossessTime.GetTime()) / static_cast<double>(mPossessTime.GetMaxTime()) * 100.0;
}

unsigned char cPlayer::GetLife() {
	return mLife;
}

unsigned char cPlayer::GetBomb() {
	return mBomb;
}

unsigned int cPlayer::GetScoreRate() {
	return mScoreRate;
}

const sScoreData cPlayer::GetScore() {
	return mScore;
}

void cPlayer::Initialize() {
	mScore.mName.clear();
	mScore.mScore = 0U;
	mScore.mContinue = 0;
	mScore.mMaxRate = 1U;
	mScore.mCharacter = ePlayer_TotalNum;
	mScore.mType = ePossess_None;
	mBulletGenerator.resize(3);
}

void cPlayer::Update() {
	mInvincibleTime.Update();	// 無敵時間カウント
	mPossessTime.Update();	// 憑依時間カウント
	if (pInputPad->GetInputState(eButton_Possess) == 1) {	// 憑依
		if (mPossessTime.GetActiveFlag()) {
			mPossessTime.Stop();
			mPossessTime.AddTime(-30);
		}
		else {
			mPossessTime.Start();
		}
	}
	mMoveVector.SetElement(0.0, 0.0);

	// テスト
	if (pInputPad->GetInputState(eButton_Coin) > 0) {
		mScore.mScore += (GetRand(29) + 1) * 10;
	}

	// 移動
	if (pInputPad != nullptr) {
		if (pInputPad->GetInputState(eDPad_Up) > 0) {
			mMoveVector.AddElement(0.0, -1.0);
		}
		else if (pInputPad->GetInputState(eDPad_Down) > 0) {
			mMoveVector.AddElement(0.0, 1.0);
		}

		if (pInputPad->GetInputState(eDPad_Left) > 0) {
			mMoveVector.AddElement(-1.0, 0.0);
		}
		else if (pInputPad->GetInputState(eDPad_Right) > 0) {
			mMoveVector.AddElement(1.0, 0.0);
		}
	}

	if (mMoveVector.GetElementX() != 0.0 ||
		mMoveVector.GetElementY() != 0.0) {
		mMoveVector.SetMagnitude(6.6);
		this->Move();
	}

	// 画面外飛び出し
	if (mPosition.GetX() <= 32.0) {
		mPosition.SetPoint(32.0, mPosition.GetY());
	}
	else if (mPosition.GetX() >= GAME_SCREEN_WIDTH - 32.0) {
		mPosition.SetPoint(GAME_SCREEN_WIDTH - 32.0, mPosition.GetY());
	}

	if (mPosition.GetY() <= GAME_SCREEN_HEIGHT / 5.0) {
		mPosition.SetPoint(mPosition.GetX(), GAME_SCREEN_HEIGHT / 5.0);
	}
	else if (mPosition.GetY() >= GAME_SCREEN_HEIGHT - 64.0) {
		mPosition.SetPoint(mPosition.GetX(), GAME_SCREEN_HEIGHT - 64.0);
	}

	// 弾源
	mBulletGenerator.at(0).SetPosition(mPosition.GetX() - 16, mPosition.GetY());
	mBulletGenerator.at(1).SetPosition(mPosition.GetX(), mPosition.GetY());
	mBulletGenerator.at(2).SetPosition(mPosition.GetX() + 16, mPosition.GetY());

	if (pInputPad->GetInputState(eButton_FullAuto) % 4 == 1) {
		for (auto &i : mBulletGenerator) {
			cPlayerBullet tBullet;	// 弾
			cVector2D tMoveVector;	// 弾移動速度
			tMoveVector.SetPolarForm(TO_RADIAN(-90.0), 1.0);
			tBullet.Initialize(tMoveVector, mScore.mCharacter);
			
			i.AddBullet(tBullet);
			i.Generate();
		}
	}
}

void cPlayer::Draw() {
	std::tstring tPer;
	tPer = std::to_tstring(this->GetPossessGauge());
	tPer += _T("%");
	cSprite::Draw();
	DrawStringF(mPosition.GetX(), mPosition.GetY(), tPer.c_str(), GetColor(0xA0, 0xA0, 0x00));
}