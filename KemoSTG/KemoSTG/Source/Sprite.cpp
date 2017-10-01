#include "../Header/Sprite.h"

cSprite::cSprite() {
	this->Initialize();
}

cSprite::~cSprite() {
	this->Finalize();
}

void cSprite::Move() {
	mPosition.AddPosition(mMoveVector.GetEndPoint().GetX(), mMoveVector.GetEndPoint().GetY());
}

void cSprite::MoveToPoint(const double PositionX, const double PositionY, const int MoveTime, const eEasingType MoveType, const eEasingFunction EasingFunction) {
	this->MoveToPointX(PositionX, MoveTime, MoveType, EasingFunction);
	this->MoveToPointY(PositionY, MoveTime, MoveType, EasingFunction);
}

void cSprite::MoveToPointX(const double PositionX, const int MoveTime, const eEasingType MoveType, const eEasingFunction EasingFunction) {
	mMoveVectorX.SetStartPoint(mPosition);
	mMoveVectorX.SetEndPoint(PositionX, mPosition.GetY());
	mMoveTime = MoveTime > 0 ? MoveTime : 1;
	mMoveType = MoveType;
	mEaseFunc = EasingFunction;
	mDelayTimerX.Initialize(mMoveTime , AUTO_INT_MAX, eCountMode_CountDown);
	mDelayTimerX.Start();
}

void cSprite::MoveToPointY(const double PositionY, const int MoveTime, const eEasingType MoveType, const eEasingFunction EasingFunction) {
	mMoveVectorY.SetStartPoint(mPosition);
	mMoveVectorY.SetEndPoint(mPosition.GetX(), PositionY);
	mMoveTime = MoveTime > 0 ? MoveTime : 1;
	mMoveType = MoveType;
	mEaseFunc = EasingFunction;
	mDelayTimerY.Initialize(mMoveTime , AUTO_INT_MAX, eCountMode_CountDown);
	mDelayTimerY.Start();
}

void cSprite::AddToPoint(const double PositionX, const double PositionY, const int MoveTime, const eEasingType MoveType, const eEasingFunction EasingFunction) {
	// this->MoveToPoint(mPosition.GetX() + PositionX, mPosition.GetY() + PositionY, MoveTime, MoveType, EasingFunction);
	this->AddToPointX(PositionX, MoveTime, MoveType, EasingFunction);
	this->AddToPointY(PositionY, MoveTime, MoveType, EasingFunction);
}

void cSprite::AddToPointX(const double PositionX, const int MoveTime, const eEasingType MoveType, const eEasingFunction EasingFunction) {
	this->MoveToPoint(mPosition.GetX() + PositionX, mPosition.GetY(), MoveTime, MoveType, EasingFunction);
}

void cSprite::AddToPointY(const double PositionY, const int MoveTime, const eEasingType MoveType, const eEasingFunction EasingFunction) {
	this->MoveToPoint(mPosition.GetX(), mPosition.GetY() + PositionY, MoveTime, MoveType, EasingFunction);
}

void cSprite::SetPosition(const double PositionX, const double PositionY) {
	mPosition.SetPoint(PositionX, PositionY);
	mMoveVector.SetStartPoint(mPosition.GetX(), mPosition.GetY());
	mMoveVectorX.SetStartPoint(mPosition.GetX(), mPosition.GetY());
	mMoveVectorY.SetStartPoint(mPosition.GetX(), mPosition.GetY());
	//mCollisionVector.SetStartPoint(mPosition.GetX(), mPosition.GetY());
}

void cSprite::SetPositionX(const double PositionX) {
	mPosition.SetPoint(PositionX, mPosition.GetY());
	mMoveVector.SetStartPoint(mPosition.GetX(), mPosition.GetY());
	mMoveVectorX.SetStartPoint(mPosition.GetX(), mPosition.GetY());
	mMoveVectorY.SetStartPoint(mPosition.GetX(), mPosition.GetY());
	//mCollisionVector.SetStartPoint(mPosition.GetX(), mPosition.GetY());
}

void cSprite::SetPositionY(const double PositionY) {
	mPosition.SetPoint(mPosition.GetX(), PositionY);
	mMoveVector.SetStartPoint(mPosition.GetX(), mPosition.GetY());
	mMoveVectorX.SetStartPoint(mPosition.GetX(), mPosition.GetY());
	mMoveVectorY.SetStartPoint(mPosition.GetX(), mPosition.GetY());
	//mCollisionVector.SetStartPoint(mPosition.GetX(), mPosition.GetY());
}

void cSprite::SetCollisionRange(const int Num, const double RangeX, const double RangeY, const eCollisionType CollisionType) {
	mCollider.at(Num).SetRange(RangeX, RangeY);
	mCollider.at(Num).SetCollisionType(CollisionType);
}

void cSprite::GetPosition(double &PositionX, double &PositionY) {
	PositionX = mPosition.GetX();
	PositionY = mPosition.GetY();
}

double cSprite::GetPositionX() {
	return mPosition.GetX();
}

double cSprite::GetPositionY() {
	return mPosition.GetY();
}

double cSprite::GetAngleToSprite(cSprite &Sprite) {
	return atan2(Sprite.GetPositionY() - mPosition.GetY(), Sprite.GetPositionX() - mPosition.GetX());
}

std::vector<cCollider> cSprite::GetCollider() {
	return mCollider;
}

cVector2D* cSprite::GetMoveVectorPointer() {
	return &mMoveVector;
}

//cVector2D* cSprite::GetCollisionVectorPointer() {
//	return &mCollisionVector;
//}

bool cSprite::GetCollisionFlag(cSprite &Sprite) {
	for (auto &i : mCollider) {
		for (auto &j : Sprite.GetCollider()) {
			if (i.GetCollision(j)) {
				return true;
			}
		}
	}
	return false;
}

void cSprite::Initialize() {
	this->SetPosition(0.0, 0.0);
	mCollider.clear();
	mMoveVector.SetPolarForm(0.0, 0.0);
	mMoveVectorX.SetPolarForm(0.0, 0.0);
	mMoveVectorY.SetPolarForm(0.0, 0.0);
	//mCollisionVector.SetPolarForm(0.0, 1.0);
	mDelayTimerX.Initialize();
	mDelayTimerY.Initialize();
	mEaseFunc = eEasingFunction_In;
	mMoveType = eEasing_Linear;
	mMoveTime = 0;
}

void cSprite::Finalize() {
	this->SetPosition(0.0, 0.0);
	mCollider.clear();
	mMoveVector.SetPolarForm(0.0, 0.0);
	mMoveVectorX.SetPolarForm(0.0, 0.0);
	mMoveVectorY.SetPolarForm(0.0, 0.0);
	//mCollisionVector.SetPolarForm(0.0, 1.0);
	mDelayTimerX.Finalize();
	mDelayTimerY.Finalize();
	mEaseFunc = eEasingFunction_In;
	mMoveType = eEasing_Linear;
	mMoveTime = 0;
}

void cSprite::Update() {
	mDelayTimerX.Update();
	mDelayTimerY.Update();

	if (mDelayTimerX.GetTime() > 0) {
		cVector2D tVector = mMoveVectorX;
		tVector *= cEasing::GetInstance()->GetEase(mEaseFunc, mMoveType, 1.0 - static_cast<double>(mDelayTimerX.GetTime() - 1) / static_cast<double>(mMoveTime), 1.0);
		mPosition = tVector.GetEndPoint();
	}

	if (mDelayTimerY.GetTime() > 0) {
		cVector2D tVector = mMoveVectorY;
		tVector *= cEasing::GetInstance()->GetEase(mEaseFunc, mMoveType, 1.0 - static_cast<double>(mDelayTimerY.GetTime() - 1) / static_cast<double>(mMoveTime), 1.0);
		mPosition = tVector.GetEndPoint();
	}
	//mCollisionVector.SetStartPoint(mPosition.GetX(), mPosition.GetY());
}

void cSprite::Draw() {
	DrawCircleAA(mPosition.GetX(), mPosition.GetY(), 20.0, 24, GetColor(0xFF, 0xFF, 0xFF));
	//DrawLine(mPosition.GetX(), mPosition.GetY(), tPositionX, tPositionY, GetColor(0x00, 0x9F, 0x00));
	//mMoveVector.Draw();
}