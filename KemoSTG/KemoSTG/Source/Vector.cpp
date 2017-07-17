#include "../Header/Vector.h"

cVector2D::cVector2D() : mStartX(0.0), mStartY(0.0), mElementX(0.0), mElementY(0.0) {

}

cVector2D::cVector2D(const double StartX, const double StartY) : mStartX(StartX), mStartY(StartY), mElementX(0.0), mElementY(0.0) {

}

void cVector2D::SetStartPoint(const double StartX, const double StartY) {
	mStartX = StartX;
	mStartY = StartY;
}

void cVector2D::SetStartPoint(cVector2D Vector) {
	double tEndX, tEndY;
	Vector.GetEndPoint(&tEndX, &tEndY);
	this->SetStartPoint(tEndX, tEndY);
}

void cVector2D::SetEndPoint(const double EndX, const double EndY) {
	mElementX = EndX - mStartX;
	mElementY = EndY - mStartY;
}

void cVector2D::SetEndPoint(cVector2D Vector) {
	double tStartX, tStartY;
	Vector.GetStartPoint(&tStartX, &tStartY);
	this->SetEndPoint(tStartX, tStartY);
}

void cVector2D::SetElement(const double ElementX, const double ElementY) {
	mElementX = ElementX;
	mElementY = ElementY;
}

void cVector2D::SetPolarForm(const double Angle, const double Magnitude) {
	mElementX = Magnitude * cos(Angle);
	mElementY = Magnitude * sin(Angle);
}

void cVector2D::SetAngle(const double Angle) {
	double tMagnitude;
	tMagnitude = this->GetMagnitude();
	this->SetPolarForm(Angle, tMagnitude);
}

void cVector2D::SetMagnitude(const double Magnitude) {
	double tAngle;
	tAngle = this->GetAngle();
	this->SetPolarForm(tAngle, Magnitude);
}

void cVector2D::MoveStartPoint(const double StartX, const double StartY) {
	mStartX += StartX;
	mStartY += StartY;
}

void cVector2D::AddElement(const double ElementX, const double ElementY) {
	mElementX += ElementX;
	mElementY += ElementY;
}

void cVector2D::AddAngle(const double Angle) {
	double tMagnitude;
	tMagnitude = this->GetMagnitude();
	this->SetPolarForm(this->GetAngle() + Angle, tMagnitude);
}

void cVector2D::AddMagnitude(const double Magnitude) {
	double tAngle;
	tAngle = this->GetAngle();
	this->SetPolarForm(tAngle, this->GetMagnitude() + Magnitude);
}

void cVector2D::GetStartPoint(double *StartX, double *StartY) {
	if (StartX != NULL && StartX != nullptr) {
		*StartX = mStartX;
	}
	if (StartY != NULL && StartY != nullptr) {
		*StartY = mStartY;
	}
}

double cVector2D::GetStartPointX() {
	return mStartX;
}

double cVector2D::GetStartPointY() {
	return mStartY;
}

void cVector2D::GetEndPoint(double *EndX, double *EndY) {
	if (EndX != NULL && EndX != nullptr) {
		*EndX = mStartX + mElementX;
	}
	if (EndY != NULL && EndY != nullptr) {
		*EndY = mStartY + mElementY;
	}
}

double cVector2D::GetEndPointX() {
	return mStartX + mElementX;
}

double cVector2D::GetEndPointY() {
	return mStartY + mElementY;
}

void cVector2D::GetElement(double *ElementX, double *ElementY) {
	if (ElementX != NULL && ElementX != nullptr) {
		*ElementX = mElementX;
	}
	if (ElementY != NULL && ElementY != nullptr) {
		*ElementY = mElementY;
	}
}

double cVector2D::GetElementX() {
	return mElementX;
}

double cVector2D::GetElementY() {
	return mElementY;
}

double cVector2D::GetAngle() {
	return atan2(mElementY, mElementX);
}

double cVector2D::GetMagnitude() {
	return sqrt(pow(mElementX, 2) + pow(mElementY, 2));
}

cVector2D cVector2D::GetVectorToVector(cVector2D Vector) {
	double tStartX, tStartY;
	double tEndX, tEndY;
	cVector2D tResultVector;

	Vector.GetStartPoint(&tEndX, &tEndY);
	this->GetEndPoint(&tStartX, &tStartY);

	tResultVector.SetStartPoint(tStartX, tStartY);
	tResultVector.SetEndPoint(tEndX, tEndY);

	return tResultVector;
}

cVector2D cVector2D::GetVectorStartPointToEndPoint(cVector2D Vector) {
	double tStartX, tStartY;
	double tEndX, tEndY;
	cVector2D tResultVector;

	Vector.GetStartPoint(&tEndX, &tEndY);
	this->GetStartPoint(&tStartX, &tStartY);

	tResultVector.SetStartPoint(tStartX, tStartY);
	tResultVector.SetEndPoint(tEndX, tEndY);

	return tResultVector;
}

cVector2D cVector2D::GetVectorEndPointToEndPoint(cVector2D Vector) {
	double tStartX, tStartY;
	double tEndX, tEndY;
	cVector2D tResultVector;

	Vector.GetEndPoint(&tEndX, &tEndY);
	this->GetEndPoint(&tStartX, &tStartY);

	tResultVector.SetStartPoint(tStartX, tStartY);
	tResultVector.SetEndPoint(tEndX, tEndY);

	return tResultVector;
}

cVector2D cVector2D::operator + (cVector2D Vector) {
	double tElementX, tElementY;
	cVector2D tResultVector;

	Vector.GetElement(&tElementX, &tElementY);
	tResultVector.SetStartPoint(mStartX, mStartY);
	tResultVector.SetElement(mElementX + tElementX, mElementY + tElementY);

	return tResultVector;
}

cVector2D cVector2D::operator - (cVector2D Vector) {
	double tElementX, tElementY;
	cVector2D tResultVector;

	Vector.GetElement(&tElementX, &tElementY);
	tResultVector.SetStartPoint(mStartX, mStartY);
	tResultVector.SetElement(mElementX - tElementX, mElementY - tElementY);

	return tResultVector;
}

cVector2D cVector2D::operator * (const double Value) {
	cVector2D tResultVector;

	tResultVector.SetStartPoint(mStartX, mStartY);
	tResultVector.SetElement(mElementX * Value, mElementY * Value);

	return tResultVector;
}

cVector2D cVector2D::operator / (const double Value) {
	cVector2D tResultVector;

	tResultVector.SetStartPoint(mStartX, mStartY);
	tResultVector.SetElement(mElementX / Value, mElementY / Value);

	return tResultVector;
}

void cVector2D::operator += (cVector2D Vector) {
	double tElementX, tElementY;
	Vector.GetElement(&tElementX, &tElementY);
	mElementX += tElementX;
	mElementY += tElementY;
}

void cVector2D::operator -= (cVector2D Vector) {
	double tElementX, tElementY;
	Vector.GetElement(&tElementX, &tElementY);
	mElementX -= tElementX;
	mElementY -= tElementY;
}

void cVector2D::operator *= (const double Value) {
	mElementX *= Value;
	mElementY *= Value;
}

void cVector2D::operator /= (const double Value) {
	mElementX /= Value;
	mElementY /= Value;
}

void cVector2D::Update() {
	
}

void cVector2D::Draw() {
	DrawFormatString(static_cast<int>(mStartX), static_cast<int>(mStartY), GetColor(0xFF, 0xFF, 0x00), _T("(%.1lf, %.1lf)\nθ = %.3lf"), mStartX, mStartY, this->GetAngle());
	DrawFormatString(static_cast<int>(mStartX + mElementX), static_cast<int>(mStartY), GetColor(0xFF, 0x00, 0x00), _T("x = %.1lf"), mElementX);
	DrawFormatString(static_cast<int>(mStartX), static_cast<int>(mStartY + mElementY), GetColor(0x00, 0xFF, 0x00), _T("y = %.1lf"), mElementY);
	DrawFormatString(static_cast<int>(mStartX + mElementX), static_cast<int>(mStartY + mElementY), GetColor(0xFF, 0x7F, 0x00), _T("(%.1lf, %.1lf)"), mStartX + mElementX, mStartY + mElementY);
	DrawFormatString(static_cast<int>(mStartX + mElementX / 2.0), static_cast<int>(mStartY + mElementY / 2.0), GetColor(0x00, 0xFF, 0xFF), _T("%.1lf"), this->GetMagnitude());
	DrawLineAA(static_cast<float>(mStartX),
		static_cast<float>(mStartY),
		static_cast<float>(mStartX + mElementX),
		static_cast<float>(mStartY),
		GetColor(0xFF, 0x00, 0x00));
	DrawLineAA(static_cast<float>(mStartX),
		static_cast<float>(mStartY),
		static_cast<float>(mStartX),
		static_cast<float>(mStartY + mElementY),
		GetColor(0x00, 0xFF, 0x00));
	DrawLineAA(static_cast<float>(mStartX),
		static_cast<float>(mStartY),
		static_cast<float>(mStartX + mElementX),
		static_cast<float>(mStartY + mElementY),
		GetColor(0xFF, 0xFF, 0x00));
}

//cVector3D::cVector3D() : mStartZ(0.0), mElementZ(0.0) {
//	
//}
//
//cVector3D::cVector3D(const double StartX, const double StartY, const double StartZ) : mStartZ(StartZ), mElementZ(0.0) {
//	mStartX = StartX;
//	mStartY = StartY;
//}
//
//void cVector3D::SetStartPoint(const double StartX, const double StartY, const double StartZ) {
//	mStartX = StartX;
//	mStartY = StartY;
//	mStartZ = StartZ;
//}
//
//void cVector3D::SetVectorElement(const double ElementX, const double ElementY, const double ElementZ) {
//	mElementX = ElementX;
//	mElementY = ElementY;
//	mElementZ = ElementZ;
//}
//
//void cVector3D::GetStartPoint(double *StartX, double *StartY, double *StartZ) {
//	if (StartX != NULL && StartX != nullptr) {
//		*StartX = mStartX;
//	}
//	if (StartY != NULL && StartY != nullptr) {
//		*StartY = mStartY;
//	}
//	if (StartZ != NULL && StartZ != nullptr) {
//		*StartZ = mStartZ;
//	}
//}
//
//void cVector3D::GetVectorElement(double *ElementX, double *ElementY, double *ElementZ) {
//	if (ElementX != NULL && ElementX != nullptr) {
//		*ElementX = mElementX;
//	}
//	if (ElementY != NULL && ElementY != nullptr) {
//		*ElementY = mElementY;
//	}
//	if (ElementZ != NULL && ElementZ != nullptr) {
//		*ElementZ = mElementZ;
//	}
//}
//
//double cVector3D::GetVectorMagnitude() {
//	return sqrt(pow(mElementX, 2) + pow(mElementY, 2) + pow(mElementZ, 2));
//}
//
//cVector3D cVector3D::GetVectorToTargetPoint(const cVector3D Vector) {
//
//}
//
//cVector3D cVector3D::GetVectorStartPointToTargetPoint(const cVector3D Vector) {
//
//}