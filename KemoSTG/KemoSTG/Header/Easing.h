#pragma once
#include <cmath>
#include "Include.h"

enum eEasingFunction {
	eEasingFunction_In,
	eEasingFunction_Out,
	eEasingFunction_InOut
};

enum eEasingType {
	eEasing_Linear,
	eEasing_Sine,
	eEasing_Quad,
	eEasing_Cubic,
	eEasing_Quart,
	eEasing_Quint,
	eEasing_Expo,
	eEasing_Circ,
	eEasing_Back,
	eEasing_Elastic,
	eEasing_Bounce
};

class cEasing {
private:
	cEasing() {}
	cEasing(const cEasing& r) {}
	cEasing& operator=(const cEasing& r) {}
public:
	static cEasing* GetInstance() {
		static cEasing inst;
		return &inst;
	}

	double GetEase(const eEasingFunction EasingFunction, const eEasingType EasingType, double t, double TotalTime, double Max = 1.0, double Min = 0.0);
	double easeIn(const eEasingType EasingType, double t, double TotalTime, double Max = 1.0, double Min = 0.0);
	double easeOut(const eEasingType EasingType, double t, double TotalTime, double Max = 1.0, double Min = 0.0);
	double easeInOut(const eEasingType EasingType, double t, double TotalTime, double Max = 1.0, double Min = 0.0);
};