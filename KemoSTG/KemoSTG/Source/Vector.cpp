#include "../Header/Vector.h"

cVector2D::cVector2D() : mStartX(0.0), mStartY(0.0), mComponentX(0.0), mComponentY(0.0) {

}

cVector2D::cVector2D(const double StartX, const double StartY) : mStartX(StartX), mStartY(StartY), mComponentX(0.0), mComponentY(0.0) {

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
	mComponentX = EndX - mStartX;
	mComponentY = EndY - mStartY;
}

void cVector2D::SetEndPoint(cVector2D Vector) {
	double tStartX, tStartY;
	Vector.GetStartPoint(&tStartX, &tStartY);
	this->SetEndPoint(tStartX, tStartY);
}

void cVector2D::SetComponent(const double ComponentX, const double ComponentY) {
	mComponentX = ComponentX;
	mComponentY = ComponentY;
}

void cVector2D::SetPolarForm(const double Angle, const double Magnitude) {
	mComponentX = Magnitude * cos(Angle);
	mComponentY = Magnitude * sin(Angle);
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

void cVector2D::GetComponent(double *ComponentX, double *ComponentY) {
	if (ComponentX != NULL && ComponentX != nullptr) {
		*ComponentX = mComponentX;
	}
	if (ComponentY != NULL && ComponentY != nullptr) {
		*ComponentY = mComponentY;
	}
}

void cVector2D::GetStartPoint(double *StartX, double *StartY) {
	if (StartX != NULL && StartX != nullptr) {
		*StartX = mStartX;
	}
	if (StartY != NULL && StartY != nullptr) {
		*StartY = mStartY;
	}
}

void cVector2D::GetEndPoint(double *EndX, double *EndY) {
	if (EndX != NULL && EndX != nullptr) {
		*EndX = mStartX + mComponentX;
	}
	if (EndY != NULL && EndY != nullptr) {
		*EndY = mStartY + mComponentY;
	}
}

double cVector2D::GetAngle() {
	return atan2(mComponentY, mComponentX);
}

double cVector2D::GetMagnitude() {
	return sqrt(pow(mComponentX, 2) + pow(mComponentY, 2));
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
	double tComponentX, tComponentY;
	cVector2D tResultVector;

	Vector.GetComponent(&tComponentX, &tComponentY);
	tResultVector.SetStartPoint(mStartX, mStartY);
	tResultVector.SetComponent(mComponentX + tComponentX, mComponentY + tComponentY);

	return tResultVector;
}

cVector2D cVector2D::operator - (cVector2D Vector) {
	double tComponentX, tComponentY;
	cVector2D tResultVector;

	Vector.GetComponent(&tComponentX, &tComponentY);
	tResultVector.SetStartPoint(mStartX, mStartY);
	tResultVector.SetComponent(mComponentX - tComponentX, mComponentY - tComponentY);

	return tResultVector;
}

cVector2D cVector2D::operator * (const double Value) {
	cVector2D tResultVector;

	tResultVector.SetStartPoint(mStartX, mStartY);
	tResultVector.SetComponent(mComponentX * Value, mComponentY * Value);

	return tResultVector;
}

cVector2D cVector2D::operator / (const double Value) {
	cVector2D tResultVector;

	tResultVector.SetStartPoint(mStartX, mStartY);
	tResultVector.SetComponent(mComponentX / Value, mComponentY / Value);

	return tResultVector;
}

void cVector2D::operator += (cVector2D Vector) {
	double tComponentX, tComponentY;
	Vector.GetComponent(&tComponentX, &tComponentY);
	mComponentX += tComponentX;
	mComponentY += tComponentY;
}

void cVector2D::operator -= (cVector2D Vector) {
	double tComponentX, tComponentY;
	Vector.GetComponent(&tComponentX, &tComponentY);
	mComponentX -= tComponentX;
	mComponentY -= tComponentY;
}

void cVector2D::operator *= (const double Value) {
	mComponentX *= Value;
	mComponentY *= Value;
}

void cVector2D::operator /= (const double Value) {
	mComponentX /= Value;
	mComponentY /= Value;
}

void cVector2D::Update() {
	
}

void cVector2D::Draw() {
	DrawFormatString(static_cast<int>(mStartX), static_cast<int>(mStartY), GetColor(0xFF, 0xFF, 0x00), _T("(%.1lf, %.1lf)\nθ = %.3lf"), mStartX, mStartY, this->GetAngle());
	DrawFormatString(static_cast<int>(mStartX + mComponentX), static_cast<int>(mStartY), GetColor(0xFF, 0x00, 0x00), _T("x = %.1lf"), mComponentX);
	DrawFormatString(static_cast<int>(mStartX), static_cast<int>(mStartY + mComponentY), GetColor(0x00, 0xFF, 0x00), _T("y = %.1lf"), mComponentY);
	DrawFormatString(static_cast<int>(mStartX + mComponentX), static_cast<int>(mStartY + mComponentY), GetColor(0xFF, 0x7F, 0x00), _T("(%.1lf, %.1lf)"), mStartX + mComponentX, mStartY + mComponentY);
	DrawFormatString(static_cast<int>(mStartX + mComponentX / 2.0), static_cast<int>(mStartY + mComponentY / 2.0), GetColor(0x00, 0xFF, 0xFF), _T("%.1lf"), this->GetMagnitude());
	DrawLineAA(static_cast<float>(mStartX),
		static_cast<float>(mStartY),
		static_cast<float>(mStartX + mComponentX),
		static_cast<float>(mStartY),
		GetColor(0xFF, 0x00, 0x00));
	DrawLineAA(static_cast<float>(mStartX),
		static_cast<float>(mStartY),
		static_cast<float>(mStartX),
		static_cast<float>(mStartY + mComponentY),
		GetColor(0x00, 0xFF, 0x00));
	DrawLineAA(static_cast<float>(mStartX),
		static_cast<float>(mStartY),
		static_cast<float>(mStartX + mComponentX),
		static_cast<float>(mStartY + mComponentY),
		GetColor(0xFF, 0xFF, 0x00));
}

//cVector3D::cVector3D() : mStartZ(0.0), mComponentZ(0.0) {
//	
//}
//
//cVector3D::cVector3D(const double StartX, const double StartY, const double StartZ) : mStartZ(StartZ), mComponentZ(0.0) {
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
//void cVector3D::SetVectorComponent(const double ComponentX, const double ComponentY, const double ComponentZ) {
//	mComponentX = ComponentX;
//	mComponentY = ComponentY;
//	mComponentZ = ComponentZ;
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
//void cVector3D::GetVectorComponent(double *ComponentX, double *ComponentY, double *ComponentZ) {
//	if (ComponentX != NULL && ComponentX != nullptr) {
//		*ComponentX = mComponentX;
//	}
//	if (ComponentY != NULL && ComponentY != nullptr) {
//		*ComponentY = mComponentY;
//	}
//	if (ComponentZ != NULL && ComponentZ != nullptr) {
//		*ComponentZ = mComponentZ;
//	}
//}
//
//double cVector3D::GetVectorMagnitude() {
//	return sqrt(pow(mComponentX, 2) + pow(mComponentY, 2) + pow(mComponentZ, 2));
//}
//
//cVector3D cVector3D::GetVectorToTargetPoint(const cVector3D Vector) {
//
//}
//
//cVector3D cVector3D::GetVectorStartPointToTargetPoint(const cVector3D Vector) {
//
//}