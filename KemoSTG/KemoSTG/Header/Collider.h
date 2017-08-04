#pragma once
#include "Point2D.h"
#include "ImageResourceContainer.h"

enum eCollisionType {
	eCollision_Rectangle,	// 矩形
	eCollision_Ellipse		// 楕円
};

class cCollider {
	cPoint2D mPosition;
	double mRangeX;
	double mRangeY;
	eCollisionType mType;
public:
	cCollider();
	~cCollider();

	void SetPosition(const double PositionX, const double PositionY);
	void SetPosition(cPoint2D &Point);
	void SetRange(const double RangeX, const double RangeY);
	void SetCollisionType(const eCollisionType Type);

	cPoint2D GetPosition();
	void GetRange(double &RangeX, double &RangeY);
	double GetRangeX();
	double GetRangeY();
	bool GetCollision(cCollider &Collider);

	void Draw();
};