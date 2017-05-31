#include "../Header/Easing.h"

double cEasing::easeIn(const eEasingType EasingType, double t, double TotalTime, double Max, double Min) {
	double s = 1.701540198866824;
	double postFix, a, p;

	switch (EasingType)
	{
	case eEasing_Sine:
		return -Max * cos(t / TotalTime * (PI / 2.0)) + Max + Min;
		break;
	case eEasing_Quad:
		return Max * (t /= TotalTime) * t + Min;
		break;
	case eEasing_Cubic:
		return Max * (t /= TotalTime) * pow(t, 2) + Min;
		break;
	case eEasing_Quart:
		return Max * (t /= TotalTime) * pow(t, 3) + Min;
 		break;
	case eEasing_Quint:
		return Max * (t /= TotalTime) * pow(t, 4) + Min;
		break;
	case eEasing_Expo:
		return (t == 0.0) ? Min : Max * pow(2, 10 * (t / TotalTime - 1.0)) + Min;
		break;
	case eEasing_Circ:
		return -Max * (sqrt(1.0 - (t /= TotalTime) * t) - 1.0) + Min;
		break;
	case eEasing_Back:
		postFix = t /= TotalTime;
		return Max * (postFix)* t * ((s + 1.0) * t - s) + Min;
		break;
	case eEasing_Elastic:
		if (t == 0.0) {
			return Min;
		}
		else if ((t /= TotalTime) == 1.0) {
			return Min + Max;
		}
		p = TotalTime * 0.3;
		a = Max;
		s = p / 4.0;
		postFix = a * pow(2, 10 * (t -= 1.0));
		return -(postFix * sin((t * TotalTime - s) * (2 * PI) / p)) + Min;
		break;
	case eEasing_Bounce:
		return Max - this->easeOut(eEasing_Bounce, TotalTime - t, TotalTime, Max, 0.0) + Min;
		break;
	default:
		return Max * t / TotalTime + Min;
		break;
	}
}

double cEasing::easeOut(const eEasingType EasingType, double t, double TotalTime, double Max, double Min) {
	double s = 1.701540198866824;
	double postFix, a, p;

	switch (EasingType)
	{
	case eEasing_Sine:
		return Max * sin(t / TotalTime * (PI / 2.0)) + Min;
		break;
	case eEasing_Quad:
		return -Max * (t /= TotalTime) * (t - 2.0) + Min;
		break;
	case eEasing_Cubic:
		return Max * ((t = t / TotalTime - 1.0) * pow(t, 2) + 1.0) + Min;
		break;
	case eEasing_Quart:
		return -Max * ((t = t / TotalTime - 1.0) * pow(t, 3) - 1.0) + Min;
		break;
	case eEasing_Quint:
		return Max * ((t = t / TotalTime - 1.0) * pow(t, 4) + 1.0) + Min;
		break;
	case eEasing_Expo:
		return (t == TotalTime) ? Min + Max : Max * (-pow(2, -10 * t / TotalTime) + 1.0) + Min;
		break;
	case eEasing_Circ:
		return Max * sqrt(1.0 - (t = t / TotalTime - 1.0) * t) + Min;
		break;
	case eEasing_Back:
		return Max * ((t = t / TotalTime - 1.0) * t * ((s + 1.0) * t + s) + 1.0) + Min;
		break;
	case eEasing_Elastic:
		if (t == 0.0) {
			return Min;
		}
		else if ((t /= TotalTime / 2.0) == 2.0) {
			return Min + Max;
		}
		p = TotalTime * (0.3 * 1.5);
		a = Max;
		s = p / 4.0;
		return a * pow(2, -10 * t)* sin((t * TotalTime - s) * (2.0 * PI) / p) + Max + Min;
		break;
	case eEasing_Bounce:
		if ((t /= TotalTime) < (1.0 / 2.75)) {
			return Max * (7.5625 * pow(t, 2)) + Min;
		}
		else if (t < (2.0 / 2.75)) {
			postFix = t -= (1.5 / 2.75);
			return Max * (7.5625 * postFix * t + 0.75) + Min;
		}
		else if (t < (2.5 / 2.75)) {
			postFix = t -= (2.25 / 2.75) + Min;
			return Max  * (7.5625 * postFix * t + 0.9375) + Min;
		}
		else {
			postFix = t -= (2.5 / 2.75) + Min;
			return Max  * (7.5625 * postFix * t + 0.984375) + Min;
		}
		break;
	default:
		return Max * t / TotalTime + Min;
		break;
	}
}

double cEasing::easeInOut(const eEasingType EasingType, double t, double TotalTime, double Max, double Min) {
	double s = 1.701540198866824;
	double postFix, a, p;

	switch (EasingType)
	{
	case eEasing_Sine:
		return -Max / 2.0 * (cos(PI * t / TotalTime) - 1.0) + Min;
		break;
	case eEasing_Quad:
		if ((t /= TotalTime / 2.0) < 1.0) {
			return ((Max / 2.0) * pow(t, 2)) + Min;
		}
		return -Max / 2.0 * (((t - 2.0) * (--t)) - 1.0) + Min;
		break;
	case eEasing_Cubic:
		if ((t /= TotalTime / 2.0) < 1.0) {
			return Max / 2.0 * pow(t, 3) + Min;
		}
		return Max / 2.0 * ((t -= 2.0) * pow(t, 2) + 2.0) + Min;
		break;
	case eEasing_Quart:
		if ((t /= TotalTime / 2.0) < 1.0) {
			return Max / 2.0 * pow(t, 4) + Min;
		}
		return -Max / 2.0 * ((t -= 2.0) * pow(t, 3) - 2.0) + Min;
		break;
	case eEasing_Quint:
		if ((t /= TotalTime / 2.0) < 1.0) {
			return Max / 2.0 * pow(t, 5) + Min;
		}
		return Max / 2.0 * ((t -= 2.0) * pow(t, 4) + 2.0) + Min;
		break;
	case eEasing_Expo:
		if (t == 0) {
			return Min;
		}
		else if (t == TotalTime) {
			return Min + Max;
		}
		else if ((t /= TotalTime / 2.0) < 1.0) {
			return Max / 2.0 * pow(2, 10 * (t - 1.0)) + Min;
		}
		return Max / 2.0 * (-pow(2, -10 * --t) + 2.0) + Min;
		break;
	case eEasing_Circ:
		if ((t /= TotalTime / 2.0) < 1.0) {
			return -Max / 2.0 * (sqrt(1.0 - pow(t, 2)) - 1.0) + Min;
		}
		return Max / 2.0 * (sqrt(1.0 - t * (t -= 2.0)) + 1.0) + Min;
		break;
	case eEasing_Back:
		if ((t /= TotalTime / 2.0) < 1.0) {
			return Max / 2.0 * (pow(t, 2) * (((s *= 1.525) + 1.0) * t - s)) + Min;
		}
		postFix = t -= 2.0;
		return Max / 2.0 * ((postFix)* t * (((s *= 1.525) + 1.0) * t + s) + 2.0) + Min;
		break;
	case eEasing_Elastic:
		if (t == 0.0) {
			return Min;
		}
		else if ((t /= TotalTime / 2.0) == 2.0) {
			return Min + Max;
		}
		p = TotalTime * (0.3 * 1.5);
		a = Max;
		s = p / 4.0;
		if (t < 1.0) {
			postFix = a * pow(2, 10 * (t -= 1.0));
			return -0.5 * (postFix * sin((t * TotalTime - s) * (2.0 * PI) / p)) + Min;
		}
		postFix = a * pow(2, -10 * (t -= 1.0));
		return postFix * sin((t * TotalTime - s) * (2.0 * PI) / p) * 0.5 + Max + Min;
		break;
	case eEasing_Bounce:
		if (t < TotalTime / 2.0) {
			return this->easeIn(eEasing_Bounce, t * 2.0, TotalTime, Max, 0.0) * 0.5 + Min;
		}
		else {
			return this->easeOut(eEasing_Bounce, t * 2.0 - TotalTime, TotalTime, Max, 0.0) * 0.5 + Max * 0.5 + Min;
		}
		break;
	default:
		return Max * t / TotalTime + Min;
		break;
	}
}