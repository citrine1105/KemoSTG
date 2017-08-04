#include "../Header/Point2D.h"

cPoint2D::cPoint2D() : mPointX(0.0), mPointY(0.0) {

}

cPoint2D::~cPoint2D() {

}

void cPoint2D::SetPoint(const double PointX, const double PointY) {
	mPointX = PointX;
	mPointY = PointY;
}

void cPoint2D::GetPoint(double &PointX, double &PointY) {
	PointX = mPointX;
	PointY = mPointY;
}

double cPoint2D::GetX() {
	return mPointX;
}

double cPoint2D::GetY() {
	return mPointY;
}

void cPoint2D::AddPosition(const double PointX, const double PointY) {
	mPointX += PointX;
	mPointY += PointY;
}