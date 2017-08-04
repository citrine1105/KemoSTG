#pragma once

class cPoint2D {
protected:
	double mPointX;
	double mPointY;
public:
	cPoint2D();
	~cPoint2D();

	void SetPoint(const double PointX, const double PointY);
	void GetPoint(double &PointX, double &PointY);
	double GetX();
	double GetY();
	void AddPosition(const double PointX, const double PointY);
};