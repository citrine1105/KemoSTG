#include "../Header/Collider.h"

cCollider::cCollider() {

}

cCollider::~cCollider() {

}

void cCollider::SetPosition(const double PositionX, const double PositionY) {
	mPosition.SetPoint(PositionX, PositionY);
}

void cCollider::SetPosition(cPoint2D &Point) {
	mPosition = Point;
}

void cCollider::SetRange(const double RangeX, const double RangeY) {
	mRangeX = RangeX;
	mRangeY = RangeY;
}

void cCollider::SetCollisionType(const eCollisionType Type) {
	mType = Type;
}

cPoint2D cCollider::GetPosition() {
	return mPosition;
}

void cCollider::GetRange(double &RangeX, double &RangeY) {
	RangeX = mRangeX;
	RangeY = mRangeY;
}

double cCollider::GetRangeX() {
	return mRangeX;
}

double cCollider::GetRangeY() {
	return mRangeY;
}

bool cCollider::GetCollision(cCollider &Collider) {
	return false;	// ì‚ê
}

void cCollider::Draw() {
	switch (mType) {
	case eCollision_Rectangle:
		DrawRotaGraph(mPosition.GetX(), mPosition.GetY(), 1.0, 0.0,
			cImageResourceContainer::GetInstance()->GetElement(eImage_RectCollisionRange)->GetHandle(), TRUE);
		break;
	case eCollision_Ellipse:
		DrawRotaGraph(mPosition.GetX(), mPosition.GetY(), 1.0, 0.0,
			cImageResourceContainer::GetInstance()->GetElement(eImage_EllipseCollisionRange)->GetHandle(), TRUE);
		break;
	default:
		DrawRotaGraph(mPosition.GetX(), mPosition.GetY(), 1.0, 0.0,
			cImageResourceContainer::GetInstance()->GetElement(eImage_None)->GetHandle(), TRUE);
		break;
	}
}