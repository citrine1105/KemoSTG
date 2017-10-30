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

void cSprite::MoveToPoint(const double PositionX, const double PositionY, const int MoveTime, const eEasingType MoveType, const eEasingFunction EasingFunction) {
	mMoveVector.SetStartPoint(mPosition);
	mMoveVector.SetEndPoint(PositionX, PositionY);
	mMoveTime = MoveTime > 0 ? MoveTime : 1;
	mMoveType = MoveType;
	mEaseFunc = EasingFunction;
	mDelayTimer.Initialize(mMoveTime , AUTO_INT_MAX, eCountMode_CountDown);
	//mDelayTimer.SetTime(mMoveTime);
	//mDelayTimer.SetCountMode(eCountMode_CountDown);
	mDelayTimer.Start();
}

void cSprite::AddToPoint(const double PositionX, const double PositionY, const int MoveTime, const eEasingType MoveType, const eEasingFunction EasingFunction) {
	this->MoveToPoint(mPosition.GetX() + PositionX, mPosition.GetY() + PositionY, MoveTime, MoveType, EasingFunction);
}

void cSprite::SetPosition(cPoint2D &Point) {
	mPosition = Point;
}

void cSprite::SetPosition(const double PositionX, const double PositionY) {
	mPosition.SetPoint(PositionX, PositionY);
	mMoveVector.SetStartPoint(mPosition.GetX(), mPosition.GetY());
	//mCollisionVector.SetStartPoint(mPosition.GetX(), mPosition.GetY());
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
	//mCollisionVector.SetPolarForm(0.0, 1.0);
	mDelayTimer.Initialize();
	mEaseFunc = eEasingFunction_In;
	mMoveType = eEasing_Linear;
	mMoveTime = 0;
}

void cSprite::Finalize() {
	this->SetPosition(0.0, 0.0);
	mCollider.clear();
	mMoveVector.SetPolarForm(0.0, 0.0);
	//mCollisionVector.SetPolarForm(0.0, 1.0);
	mDelayTimer.Finalize();
	mEaseFunc = eEasingFunction_In;
	mMoveType = eEasing_Linear;
	mMoveTime = 0;
}

void cSprite::Update() {
	mDelayTimer.Update();
	if (mDelayTimer.GetTime() > 0) {
		cVector2D tVector = mMoveVector;
		tVector *= cEasing::GetInstance()->GetEase(mEaseFunc, mMoveType, 1.0 - static_cast<double>(mDelayTimer.GetTime() - 1) / static_cast<double>(mMoveTime), 1.0);
		mPosition = tVector.GetEndPoint();
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