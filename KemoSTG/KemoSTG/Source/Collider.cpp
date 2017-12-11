#include "../Header/Collider.h"

cImageResourceContainer gColliderDebugImageContainer;

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
	// åXÇ´ÇÃÇ»Ç¢ãÈå`ìØémÇÃîªíËÇæÇØé¿ëï
	struct tsPoint {
		double Top;
		double Bottom;
		double Left;
		double Right;
	};

	std::array<tsPoint, 2> tPoint;
	double tPosX, tPosY, tRangeX, tRangeY;
	tPosX = Collider.GetPosition().GetX();
	tPosY = Collider.GetPosition().GetY();
	tRangeX = Collider.GetRangeX();
	tRangeY = Collider.GetRangeY();

	if (mRangeX <= 0.0 ||
		mRangeY <= 0.0 ||
		tRangeX <= 0.0 ||
		tRangeY <= 0.0) {
		return false;
	}

	tPoint.at(0).Top = mPosition.GetY() - mRangeY / 2.0;
	tPoint.at(0).Bottom = mPosition.GetY() + mRangeY / 2.0;
	tPoint.at(0).Left = mPosition.GetX() - mRangeX / 2.0;
	tPoint.at(0).Right = mPosition.GetX() + mRangeX / 2.0;

	tPoint.at(1).Top = tPosY - tRangeY / 2.0;
	tPoint.at(1).Bottom = tPosY + tRangeY / 2.0;
	tPoint.at(1).Left = tPosX - tRangeX / 2.0;
	tPoint.at(1).Right = tPosX + tRangeX / 2.0;

	if ((tPoint.at(0).Top <= tPoint.at(1).Bottom && tPoint.at(0).Bottom >= tPoint.at(1).Top) &&
		(tPoint.at(0).Left <= tPoint.at(1).Right && tPoint.at(0).Right >= tPoint.at(1).Left)) {
		return true;
	}
	else {
		return false;
	}
	return false;	// çÏÇÍ
}

void cCollider::Draw() {
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, static_cast<int>(40.0 * 255.0 / 100.0));
	DrawRotaGraph3F(mPosition.GetX(), mPosition.GetY(), 16.0, 16.0, mRangeX / 32.0, mRangeY / 32.0,
		0.0, gColliderDebugImageContainer.GetElement(eCollision_Rectangle)->GetHandle(), TRUE);
	switch (mType) {
	case eCollision_Rectangle:

		break;
	case eCollision_Ellipse:
		//DrawRotaGraph(mPosition.GetX(), mPosition.GetY(), 1.0, 0.0,
		//	cImageResourceContainer::GetInstance()->GetElement(eImage_EllipseCollisionRange)->GetHandle(), TRUE);
		break;
	default:
		//DrawRotaGraph(mPosition.GetX(), mPosition.GetY(), 1.0, 0.0,
		//	cImageResourceContainer::GetInstance()->GetElement(eImage_None)->GetHandle(), TRUE);
		break;
	}
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
}