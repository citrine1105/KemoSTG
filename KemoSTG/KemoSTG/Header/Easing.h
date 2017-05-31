#pragma once
#include <cmath>
#include "Include.h"

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
public:
	double easeIn(const eEasingType EasingType, double t, double TotalTime, double Max = 1.0, double Min = 0.0);
	double easeOut(const eEasingType EasingType, double t, double TotalTime, double Max = 1.0, double Min = 0.0);
	double easeInOut(const eEasingType EasingType, double t, double TotalTime, double Max = 1.0, double Min = 0.0);
};