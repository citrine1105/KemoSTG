#pragma once
#include "Include.h"
#include "Timer.h"
#include <cmath>

class cBezier : public iActivity {
protected:
	cTimer mTimer;
	unsigned short mPascalTriangle[12][12];
	double mComponentX;
	double mComponentY;
public:
	cBezier();
	cBezier(const int Dimension);

	void Reset();
	void SetDimension();
	void GetComponent(double *ComponentX, double *ComponentY);

	void Update() override;
	void Draw() override;
};