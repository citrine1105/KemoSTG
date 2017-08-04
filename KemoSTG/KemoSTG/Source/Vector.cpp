#include "../Header/Vector.h"

cVector2D::cVector2D() : mElementX(0.0), mElementY(0.0) {

}

cVector2D::cVector2D(const double StartX, const double StartY) : mElementX(0.0), mElementY(0.0) {
	mStartPoint.SetPoint(StartX, StartY);
}

void cVector2D::SetStartPoint(const double StartX, const double StartY) {
	mStartPoint.SetPoint(StartX, StartY);
}

void cVector2D::SetStartPoint(cPoint2D &Point) {
	mStartPoint = Point;
}

void cVector2D::SetStartPoint(cVector2D &Vector) {
	this->SetStartPoint(Vector.GetEndPoint());
}

void cVector2D::SetEndPoint(const double EndX, const double EndY) {
	mElementX = EndX - mStartPoint.GetX();
	mElementY = EndY - mStartPoint.GetY();
}

void cVector2D::SetEndPoint(cPoint2D &Point) {
	mElementX = Point.GetX() - mStartPoint.GetX();
	mElementY = Point.GetY() - mStartPoint.GetY();
}

void cVector2D::SetEndPoint(cVector2D &Vector) {
	this->SetEndPoint(Vector.GetEndPoint());
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
	mStartPoint.SetPoint(mStartPoint.GetX() + StartX, mStartPoint.GetY() + StartY);
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

cPoint2D cVector2D::GetStartPoint() {
	return mStartPoint;
}

cPoint2D cVector2D::GetEndPoint() {
	cPoint2D tPoint;

	tPoint = mStartPoint;
	tPoint.AddPosition(mElementX, mElementY);

	return tPoint;
}

void cVector2D::GetElement(double &ElementX, double &ElementY) {
	ElementX = mElementX;
	ElementY = mElementY;
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
	cVector2D tResultVector;

	tResultVector.SetStartPoint(this->GetEndPoint());
	tResultVector.SetEndPoint(Vector.GetStartPoint());

	return tResultVector;
}

cVector2D cVector2D::GetVectorStartPointToEndPoint(cVector2D Vector) {
	cVector2D tResultVector;

	tResultVector.SetStartPoint(this->GetStartPoint());
	tResultVector.SetEndPoint(Vector.GetEndPoint());

	return tResultVector;
}

cVector2D cVector2D::GetVectorEndPointToEndPoint(cVector2D Vector) {
	cVector2D tResultVector;

	tResultVector.SetStartPoint(this->GetEndPoint());
	tResultVector.SetEndPoint(Vector.GetEndPoint());

	return tResultVector;
}

cVector2D cVector2D::operator + (cVector2D Vector) {
	double tElementX, tElementY;
	cVector2D tResultVector;

	Vector.GetElement(tElementX, tElementY);
	tResultVector.SetStartPoint(this->GetStartPoint());
	tResultVector.SetElement(mElementX + tElementX, mElementY + tElementY);

	return tResultVector;
}

cVector2D cVector2D::operator - (cVector2D Vector) {
	double tElementX, tElementY;
	cVector2D tResultVector;

	Vector.GetElement(tElementX, tElementY);
	tResultVector.SetStartPoint(this->GetStartPoint());
	tResultVector.SetElement(mElementX - tElementX, mElementY - tElementY);

	return tResultVector;
}

cVector2D cVector2D::operator * (const double Value) {
	cVector2D tResultVector;

	tResultVector.SetStartPoint(this->GetStartPoint());
	tResultVector.SetElement(mElementX * Value, mElementY * Value);

	return tResultVector;
}

cVector2D cVector2D::operator / (const double Value) {
	cVector2D tResultVector;

	tResultVector.SetStartPoint(this->GetStartPoint());
	tResultVector.SetElement(mElementX / Value, mElementY / Value);

	return tResultVector;
}

void cVector2D::operator += (cVector2D Vector) {
	double tElementX, tElementY;
	Vector.GetElement(tElementX, tElementY);
	mElementX += tElementX;
	mElementY += tElementY;
}

void cVector2D::operator -= (cVector2D Vector) {
	double tElementX, tElementY;
	Vector.GetElement(tElementX, tElementY);
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
	DrawFormatString(static_cast<int>(mStartPoint.GetX()), static_cast<int>(mStartPoint.GetY()), GetColor(0xFF, 0xFF, 0x00), _T("(%.1lf, %.1lf)\nθ = %.3lf"), mStartPoint.GetX(), mStartPoint.GetY(), this->GetAngle());
	DrawFormatString(static_cast<int>(mStartPoint.GetX() + mElementX), static_cast<int>(mStartPoint.GetY()), GetColor(0xFF, 0x00, 0x00), _T("x = %.1lf"), mElementX);
	DrawFormatString(static_cast<int>(mStartPoint.GetX()), static_cast<int>(mStartPoint.GetY() + mElementY), GetColor(0x00, 0xFF, 0x00), _T("y = %.1lf"), mElementY);
	DrawFormatString(static_cast<int>(mStartPoint.GetX() + mElementX), static_cast<int>(mStartPoint.GetY() + mElementY), GetColor(0xFF, 0x7F, 0x00), _T("(%.1lf, %.1lf)"), mStartPoint.GetX() + mElementX, mStartPoint.GetY() + mElementY);
	DrawFormatString(static_cast<int>(mStartPoint.GetX() + mElementX / 2.0), static_cast<int>(mStartPoint.GetY() + mElementY / 2.0), GetColor(0x00, 0xFF, 0xFF), _T("%.1lf"), this->GetMagnitude());
	DrawLineAA(static_cast<float>(mStartPoint.GetX()),
		static_cast<float>(mStartPoint.GetY()),
		static_cast<float>(mStartPoint.GetX() + mElementX),
		static_cast<float>(mStartPoint.GetY()),
		GetColor(0xFF, 0x00, 0x00));
	DrawLineAA(static_cast<float>(mStartPoint.GetX()),
		static_cast<float>(mStartPoint.GetY()),
		static_cast<float>(mStartPoint.GetX()),
		static_cast<float>(mStartPoint.GetY() + mElementY),
		GetColor(0x00, 0xFF, 0x00));
	DrawLineAA(static_cast<float>(mStartPoint.GetX()),
		static_cast<float>(mStartPoint.GetY()),
		static_cast<float>(mStartPoint.GetX() + mElementX),
		static_cast<float>(mStartPoint.GetY() + mElementY),
		GetColor(0xFF, 0xFF, 0x00));
}