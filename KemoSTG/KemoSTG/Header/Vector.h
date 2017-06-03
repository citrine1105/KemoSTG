#pragma once
#include <cmath>
#include "Include.h"

class cVector2D : public iActivity {
protected:
	double mStartX;	// 始点X
	double mStartY;	// 始点Y
	double mElementX;	// X成分
	double mElementY;	// Y成分
public:
	cVector2D();		// デフォルトコンストラクタ
	cVector2D(const double StartX, const double StartY);		// 始点指定コンストラクタ

	void SetStartPoint(const double StartX, const double StartY);	// 始点指定
	void SetStartPoint(cVector2D Vector);	// 別ベクトルの終点に始点を置く
	void SetEndPoint(const double EndX, const double EndY);	// 終点指定
	void SetEndPoint(cVector2D Vector);		// 別ベクトルの始点に終点を置く
	void SetElement(const double ElementX, const double ElementY);	// 成分指定
	void SetPolarForm(const double Angle, const double Magnitude);		// 偏角と絶対値指定
	void SetAngle(const double Angle);				// 偏角指定
	void SetMagnitude(const double Magnitude);		// 絶対値指定
	void MoveStartPoint(const double StartX, const double StartY);	// 始点移動
	void AddElement(const double ElementX, const double ElementY);		// 成分加算
	void AddAngle(const double Angle);	// 角度加算
	void AddMagnitude(const double Magnitude);	// 大きさ加算
	void GetStartPoint(double *StartX, double *StartY);	// 始点取得
	void GetEndPoint(double *EndX, double *EndY);	// 終点取得
	void GetElement(double *ElementX, double *ElementY);		// 成分取得
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

//class cVector3D : public cVector2D {
//protected:
//	double mStartZ;	// 始点Z
//	double mElementZ;	// Z成分
//public:
//	cVector3D();		// デフォルトコンストラクタ
//	cVector3D(const double StartX, const double StartY, const double StartZ);	// 始点指定コンストラクタ
//
//	void SetStartPoint(const double StartX, const double StartY, const double StartZ);	// 始点指定
//	void SetVectorElement(const double ElementX, const double ElementY, double ElementZ);	// 成分指定
//	//void SetVectorMagnitude(const double Magnitude);		// 絶対値指定
//	void GetStartPoint(double *StartX, double *StartY, double *StartZ);	// 始点取得
//	void GetVectorElement(double *ElementX, double *ElementY, double *ElementZ);		// 成分取得
//	double GetVectorMagnitude() override;	// ベクトルの絶対値
//	cVector3D GetVectorToTargetPoint(const cVector3D Vector);	// 別ベクトルの始点までのベクトル取得
//	cVector3D GetVectorStartPointToTargetPoint(const cVector3D Vector);	// 始点から別ベクトルの始点までのベクトル取得
//
//	cVector3D operator + (const cVector3D Vector);	// ベクトル加算
//	cVector3D operator - (const cVector3D Vector);	// ベクト減算
//	cVector3D operator * (const double Value);	// ベクトル乗算
//	cVector3D operator / (const double Value);	// ベクトル除算
//	virtual void operator += (cVector3D Vector);
//	virtual void operator -= (cVector3D Vector);
//	virtual void operator *= (const double Value) override;
//	virtual void operator /= (const double Value) override;
//};