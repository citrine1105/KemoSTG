#include "../Header/Sprite.h"

cSprite::cSprite() {
	this->Initialize();
}

cSprite::~cSprite() {
	this->Finalize();
}

void cSprite::Move() {
	double tPositionX, tPositionY;
	mMoveVector.GetEndPoint(tPositionX, tPositionY);
	this->MoveToPoint(tPositionX, tPositionY, 1);
}

void cSprite::MoveToPoint(const double PositionX, const double PositionY, const int MoveTime, const eEasingType MoveType, const eEasingFunction EasingFunction) {
	mMoveVector.SetStartPoint(mPositionX, mPositionY);
	mMoveVector.SetEndPoint(PositionX, PositionY);
	mMoveTime = MoveTime > 0 ? MoveTime : 1;
	mMoveType = MoveType;
	mEaseFunc = EasingFunction;
	mDelayTimer.Initialize(mMoveTime, AUTO_INT_MAX, eCountMode_CountDown);
	//mDelayTimer.SetTime(mMoveTime);
	//mDelayTimer.SetCountMode(eCountMode_CountDown);
	mDelayTimer.Start();
}

void cSprite::AddToPoint(const double PositionX, const double PositionY, const int MoveTime, const eEasingType MoveType, const eEasingFunction EasingFunction) {
	this->MoveToPoint(mPositionX + PositionX, mPositionY + PositionY, MoveTime, MoveType, EasingFunction);
}

void cSprite::SetPosition(const double PositionX, const double PositionY) {
	mPositionX = PositionX;
	mPositionY = PositionY;
	mMoveVector.SetStartPoint(mPositionX, mPositionY);
	mCollisionVector.SetStartPoint(mPositionX, mPositionY);
}

void cSprite::SetCollisionRange(const double RangeX, const double RangeY, const eCollisionType CollisionType) {
	mCollisionRangeX = RangeX;
	mCollisionRangeY = RangeY;
	mCollisionType = CollisionType;
}

void cSprite::GetPosition(double &PositionX, double &PositionY) {
	PositionX = mPositionX;
	PositionY = mPositionY;
}

double cSprite::GetPositionX() {
	return mPositionX;
}

double cSprite::GetPositionY() {
	return mPositionY;
}

double cSprite::GetAngleToSprite(cSprite &Sprite) {
	return atan2(Sprite.GetPositionY() - mPositionY, Sprite.GetPositionX() - mPositionX);
}

cVector2D* cSprite::GetMoveVectorPointer() {
	return &mMoveVector;
}

cVector2D* cSprite::GetCollisionVectorPointer() {
	return &mCollisionVector;
}

void cSprite::Initialize() {
	this->SetPosition(0.0, 0.0);
	mCollisionRangeX = 0.0;
	mCollisionRangeY = 0.0;
	mMoveVector.SetPolarForm(0.0, 0.0);
	mCollisionVector.SetPolarForm(0.0, 1.0);
	mDelayTimer.Initialize();
	mEaseFunc = eEasingFunction_In;
	mMoveType = eEasing_Linear;
	mMoveTime = 0;
}

void cSprite::Finalize() {
	this->SetPosition(0.0, 0.0);
	mCollisionRangeX = 0.0;
	mCollisionRangeY = 0.0;
	mMoveVector.SetPolarForm(0.0, 0.0);
	mCollisionVector.SetPolarForm(0.0, 1.0);
	mDelayTimer.Finalize();
	mEaseFunc = eEasingFunction_In;
	mMoveType = eEasing_Linear;
	mMoveTime = 0;
}

void cSprite::Update() {
	mDelayTimer.Update();
	if (mDelayTimer.GetActiveFlag()) {
		cVector2D tVector = mMoveVector;
		tVector *= cEasing::GetInstance()->GetEase(mEaseFunc, mMoveType, 1.0 - static_cast<double>(mDelayTimer.GetTime() - 1) / static_cast<double>(mMoveTime), 1.0);
		mPositionX = tVector.GetEndPointX();
		mPositionY = tVector.GetEndPointY();
	}
	//if (mDelayTimer.GetTime() <= 0) {
	//	mDelayTimer.Stop();
	//}
	mCollisionVector.SetStartPoint(mPositionX, mPositionY);
}

void cSprite::Draw() {
	double tPositionX, tPositionY;
	mCollisionVector.GetEndPoint(tPositionX, tPositionY);
	DrawCircleAA(mPositionX, mPositionY, 20.0, 24, GetColor(0xFF, 0xFF, 0xFF));
	//DrawLine(mPositionX, mPositionY, tPositionX, tPositionY, GetColor(0x00, 0x9F, 0x00));
	//mMoveVector.Draw();
}