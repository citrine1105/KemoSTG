#pragma once
#include <cmath>
#include "Include.h"
#include "Point2D.h"

class cVector2D : public iActivity {
protected:
	cPoint2D mStartPoint;
	double mElementX;	// X成分
	double mElementY;	// Y成分
public:
	cVector2D();		// デフォルトコンストラクタ
	cVector2D(const double StartX, const double StartY);		// 始点指定コンストラクタ

	void SetStartPoint(const double StartX, const double StartY);	// 始点指定
	void SetStartPoint(cPoint2D &Point);
	void SetStartPoint(cVector2D &Vector);	// 別ベクトルの終点に始点を置く
	void SetEndPoint(const double EndX, const double EndY);	// 終点指定
	void SetEndPoint(cPoint2D &Point);
	void SetEndPoint(cVector2D &Vector);		// 別ベクトルの始点に終点を置く
	void SetElement(const double ElementX, const double ElementY);	// 成分指定
	void SetPolarForm(const double Angle, const double Magnitude);		// 偏角と絶対値指定
	void SetAngle(const double Angle);				// 偏角指定
	void SetMagnitude(const double Magnitude);		// 絶対値指定
	void MoveStartPoint(const double StartX, const double StartY);	// 始点移動
	void AddElement(const double ElementX, const double ElementY);		// 成分加算
	void AddAngle(const double Angle);	// 角度加算
	void AddMagnitude(const double Magnitude);	// 大きさ加算
	cPoint2D GetStartPoint();	// 始点取得
	cPoint2D GetEndPoint();	// 終点取得
	void GetElement(double &ElementX, double &ElementY);		// 成分取得
	double GetElementX();
	double GetElementY();
	double GetAngle();		// ベクトルの偏角
	virtual double GetMagnitude();		// ベクトルの絶対値
	cVector2D GetVectorToVector(cVector2D Vector);	// 別ベクトルの始点までのベクトル取得
	cVector2D GetVectorStartPointToEndPoint(cVector2D Vector);	// 始点から別ベクトルの始点までのベクトル取得
	cVector2D GetVectorEndPointToEndPoint(cVector2D Vector);	// 始点から別ベクトルの始点までのベクトル取得

	cVector2D operator + (cVector2D Vector);		// ベクトル加算
	cVector2D operator - (cVector2D Vector);		// ベクトル減算
	cVector2D operator * (const double Value);	// ベクトル乗算
	cVector2D operator / (const double Value);	// ベクトル除算
	virtual void operator += (cVector2D Vector);
	virtual void operator -= (cVector2D Vector);
	virtual void operator *= (const double Value);
	virtual void operator /= (const double Value);

	virtual void Update() override;
	virtual void Draw() override;
};