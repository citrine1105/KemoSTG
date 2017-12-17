#include "../Header/Sprite.h"

cSprite::cSprite() {
	this->Initialize();
}

cSprite::~cSprite() {
	this->Finalize();
}

void cSprite::Move() {
	mPosition.AddPosition(mMoveVector.GetElementX(), mMoveVector.GetElementY());
}

void cSprite::Move(const int MoveTime, const eEasingType MoveType, const eEasingFunction EasingFunction) {
	this->MoveToPoint(mMoveVector.GetEndPoint().GetX(), mMoveVector.GetEndPoint().GetY(), MoveTime, MoveType, EasingFunction);
}

void cSprite::Move(sPolarFormMoveData &MoveData) {
	mMoveVector.SetStartPoint(mPosition);
	mMoveVector.SetPolarForm(MoveData.mAngle, MoveData.mMagnitude);
	this->Move(MoveData.mMoveTime, MoveData.mMoveType, MoveData.mEasingFunction);
}

void cSprite::MoveToPoint(const double PositionX, const double PositionY, const int MoveTime, const eEasingType MoveType, const eEasingFunction EasingFunction) {
	this->MoveToPointX(PositionX, MoveTime, MoveType, EasingFunction);
	this->MoveToPointY(PositionY, MoveTime, MoveType, EasingFunction);
}

void cSprite::MoveToPoint(sPointMoveData &MoveData) {
	this->MoveToPoint(MoveData.mTargetPoint.GetX(), MoveData.mTargetPoint.GetY(), MoveData.mMoveTime, MoveData.mMoveType, MoveData.mEasingFunction);
}

void cSprite::MoveToPointX(const double PositionX, const int MoveTime, const eEasingType MoveType, const eEasingFunction EasingFunction) {
	mMoveVectorX.SetStartPoint(mPosition);
	mMoveVectorX.SetEndPoint(PositionX, mPosition.GetY());
	mMoveTimeX = MoveTime > 0 ? MoveTime : 1;
	mMoveTypeX = MoveType;
	mEaseFuncX = EasingFunction;
	mDelayTimerX.Initialize(mMoveTimeX, AUTO_INT_MAX, eCountMode_CountDown);
	mDelayTimerX.Start();
}

void cSprite::MoveToPointX(sPointMoveData &MoveData) {
	this->MoveToPointX(MoveData.mTargetPoint.GetX(), MoveData.mMoveTime, MoveData.mMoveType, MoveData.mEasingFunction);
}

void cSprite::MoveToPointY(const double PositionY, const int MoveTime, const eEasingType MoveType, const eEasingFunction EasingFunction) {
	mMoveVectorY.SetStartPoint(mPosition);
	mMoveVectorY.SetEndPoint(mPosition.GetX(), PositionY);
	mMoveTimeY = MoveTime > 0 ? MoveTime : 1;
	mMoveTypeY = MoveType;
	mEaseFuncY = EasingFunction;
	mDelayTimerY.Initialize(mMoveTimeX, AUTO_INT_MAX, eCountMode_CountDown);
	mDelayTimerY.Start();
}

void cSprite::MoveToPointY(sPointMoveData &MoveData) {
	this->MoveToPointY(MoveData.mTargetPoint.GetY(), MoveData.mMoveTime, MoveData.mMoveType, MoveData.mEasingFunction);
}

void cSprite::AddToPoint(const double PositionX, const double PositionY, const int MoveTime, const eEasingType MoveType, const eEasingFunction EasingFunction) {
	this->MoveToPoint(mPosition.GetX() + PositionX, mPosition.GetY() + PositionY, MoveTime, MoveType, EasingFunction);
}

void cSprite::AddToPointX(const double PositionX, const int MoveTime, const eEasingType MoveType, const eEasingFunction EasingFunction) {
	this->MoveToPointX(mPosition.GetX() + PositionX, MoveTime, MoveType, EasingFunction);
}

void cSprite::AddToPointY(const double PositionY, const int MoveTime, const eEasingType MoveType, const eEasingFunction EasingFunction) {
	this->MoveToPointY(mPosition.GetY() + PositionY, MoveTime, MoveType, EasingFunction);
}

void cSprite::SetPosition(cPoint2D &Point) {
	mPosition = Point;
}

void cSprite::SetPosition(const double PositionX, const double PositionY) {
	mPosition.SetPoint(PositionX, PositionY);
	mMoveVector.SetStartPoint(mPosition.GetX(), mPosition.GetY());
}

void cSprite::SetCollisionRange(const int Num, const double RangeX, const double RangeY, const eCollisionType CollisionType) {
	mCollider.at(Num).SetRange(RangeX, RangeY);
	mCollider.at(Num).SetCollisionType(CollisionType);
}

cPoint2D cSprite::GetPosition() {
	return mPosition;
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

std::vector<cCollider>* cSprite::GetColliderPointer() {
	return &mCollider;
}

cVector2D* cSprite::GetMoveVectorPointer() {
	return &mMoveVector;
}

bool cSprite::GetCollisionFlag(cSprite &Sprite) {
	for (auto &i : mCollider) {
		for (auto &j : *Sprite.GetColliderPointer()) {
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
	mDelayTimerX.Initialize();
	mDelayTimerY.Initialize();
	mEaseFuncX = eEasingFunction_In;
	mEaseFuncY = eEasingFunction_In;
	mMoveTypeX = eEasing_Linear;
	mMoveTypeY = eEasing_Linear;
	mMoveTimeX = 0;
	mMoveTimeY = 0;
	for (auto &i : mCollider) {
		i.SetPosition(mPosition);
	}
}

void cSprite::Finalize() {
	this->SetPosition(0.0, 0.0);
	mCollider.clear();
	mMoveVector.SetPolarForm(0.0, 0.0);
	mDelayTimerX.Finalize();
	mDelayTimerY.Finalize();
	mEaseFuncX = eEasingFunction_In;
	mEaseFuncY = eEasingFunction_In;
	mMoveTypeX = eEasing_Linear;
	mMoveTypeY = eEasing_Linear;
	mMoveTimeX = 0;
	mMoveTimeY = 0;
}

void cSprite::Update() {
	mDelayTimerX.Update();
	mDelayTimerY.Update();
	if (mDelayTimerX.GetTime() > 0) {
		cVector2D tVector = mMoveVectorX;
		tVector *= cEasing::GetInstance()->GetEase(mEaseFuncX, mMoveTypeX, 1.0 - static_cast<double>(mDelayTimerX.GetTime() - 1) / static_cast<double>(mMoveTimeX), 1.0);
		mPosition.SetPoint(tVector.GetEndPoint().GetX(), mPosition.GetY());
	}
	if (mDelayTimerY.GetTime() > 0) {
		cVector2D tVector = mMoveVectorY;
		tVector *= cEasing::GetInstance()->GetEase(mEaseFuncY, mMoveTypeY, 1.0 - static_cast<double>(mDelayTimerY.GetTime() - 1) / static_cast<double>(mMoveTimeY), 1.0);
		mPosition.SetPoint(mPosition.GetX(), tVector.GetEndPoint().GetY());
	}
	//if (mDelayTimer.GetTime() <= 0) {
	//	mDelayTimer.Stop();
	//}
	//mCollisionVector.SetStartPoint(mPosition.GetX(), mPosition.GetY());
}

void cSprite::Draw() {
	DrawCircleAA(mPosition.GetX(), mPosition.GetY(), 20.0, 24, GetColor(0xFF, 0xFF, 0xFF));
	//DrawLine(mPosition.GetX(), mPosition.GetY(), tPositionX, tPositionY, GetColor(0x00, 0x9F, 0x00));
	//mMoveVector.Draw();
}