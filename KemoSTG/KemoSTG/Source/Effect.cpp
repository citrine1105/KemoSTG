#include "../Header/Effect.h"
#include "../Header/GameManager.h"
#include "../Header/SelectTimer.h"

cImageResourceContainer gEffectImageContainer;

cEffect::cEffect() {
	this->Initialize();
}

cEffect::cEffect(const eEffectType Type, cPoint2D &Position) {
	this->Initialize(Type, Position);
}

cEffect::~cEffect() {
	this->Finalize();
}

bool cEffect::GetPlayFlag() {
	return mAnimeTimer.GetActiveFlag();
}

void cEffect::Initialize() {
	mAnimeTimer.Start();
}

void cEffect::Initialize(const eEffectType Type, cPoint2D &Position) {
	this->Initialize();
	mType = Type;
	mPosition = Position;
}

void cEffect::Finalize() {
	mAnimeTimer.Finalize();
}

void cEffect::Update() {
	cSprite::Update();
	switch (mType) {
	case eEffect_RateNum:
		if (mAnimeTimer.GetTime() == 0) {
			sPolarFormMoveData tMoveData;
			tMoveData.mAngle = TO_RADIAN(-70.0);
			tMoveData.mMagnitude = 96.0;
			tMoveData.mMoveTime = mEffectTime.at(mType);
			tMoveData.mMoveType = eEasing_Circ;
			tMoveData.mEasingFunction = eEasingFunction_In;
			this->Move(tMoveData);
		}
		break;
	default:
		break;
	}
	mAnimeTimer.Update();
	if (mAnimeTimer.GetTime() >= mEffectTime.at(mType)) {
		mAnimeTimer.Stop();
	}
}

void cEffect::Draw() {
	std::tstring tRate;
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, static_cast<int>(255.0 * 70.0 / 100.0));
	switch (mType) {
	case eEffect_RateNum:
		tRate = std::to_tstring(cGameManager::GetInstance()->GetPlayerPointer()->at(0).GetScoreRate());
		DrawStringFToHandle(mPosition.GetX(), mPosition.GetY(), tRate.c_str(), GetColor(0xFF, 0xFF, 0xFF), gTimerFontContainer.GetElement(eTimerFont_Big)->GetHandle());
		break;
	case eEffect_BigBomb:
		if (gEffectImageContainer.GetElement(eEffect_Bomb)->GetHandleNum() > 0) {
			DrawRotaGraph2F(mPosition.GetX(), mPosition.GetY(), gEffectImageContainer.GetElement(eEffect_Bomb)->GetSizeX() / 2, gEffectImageContainer.GetElement(eEffect_Bomb)->GetSizeY() / 2, 2.0, 0.0, gEffectImageContainer.GetElement(eEffect_Bomb)->GetHandle(static_cast<int>(static_cast<double>(mAnimeTimer.GetTime()) / static_cast<double>(gEffectImageContainer.GetElement(eEffect_Bomb)->GetHandleNum()))), TRUE);
		}
		break;
	default:
		if (gEffectImageContainer.GetElement(mType)->GetHandleNum() > 0) {
			DrawGraphF(mPosition.GetX() - gEffectImageContainer.GetElement(mType)->GetSizeX() / 2, mPosition.GetY() - gEffectImageContainer.GetElement(mType)->GetSizeY() / 2, gEffectImageContainer.GetElement(mType)->GetHandle(static_cast<int>(static_cast<double>(mAnimeTimer.GetTime()) / static_cast<double>(gEffectImageContainer.GetElement(mType)->GetHandleNum()))), TRUE);
		}
		break;
	}
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
}