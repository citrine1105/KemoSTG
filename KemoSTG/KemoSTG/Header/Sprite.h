﻿#pragma once
#include "Include.h"
#include "Vector.h"
#include "Timer.h"
#include "Easing.h"
#include "Collider.h"

class cSprite : public iInitialization, iActivity {
protected:
	cPoint2D mPosition;	// 座標
	std::vector<cCollider> mCollider;	// 接触判定
	cVector2D mMoveVector;		// 移動処理用ベクトル
	cVector2D mMoveVectorX;
	cVector2D mMoveVectorY;
	//cVector2D mCollisionVector;	// 衝突判定用ベクトル
	cTimer mDelayTimerX;	// 移動処理用タイマー
	cTimer mDelayTimerY;
	eEasingFunction mEaseFunc;	// 移動関数
	eEasingType mMoveType;		// 移動タイプ
	int mMoveTime;	// 移動にかかる時間(f)
public:
	cSprite();	// デフォルトコンストラクタ
	~cSprite();	// デストラクタ

	void Move();		// ベクトルに準じて移動
	void MoveToPoint(const double PositionX, const double PositionY, const int MoveTime, const eEasingType MoveType = eEasing_Linear, const eEasingFunction EasingFunction = eEasingFunction_Out);	// 指定の場所に移動
	void MoveToPointX(const double PositionX, const int MoveTime, const eEasingType MoveType = eEasing_Linear, const eEasingFunction EasingFunction = eEasingFunction_Out);
	void MoveToPointY(const double PositionY, const int MoveTime, const eEasingType MoveType = eEasing_Linear, const eEasingFunction EasingFunction = eEasingFunction_Out);
	void AddToPoint(const double PositionX, const double PositionY, const int MoveTime, const eEasingType MoveType = eEasing_Linear, const eEasingFunction EasingFunction = eEasingFunction_Out);
	void AddToPointX(const double PositionX, const int MoveTime, const eEasingType MoveType = eEasing_Linear, const eEasingFunction EasingFunction = eEasingFunction_Out);
	void AddToPointY(const double PositionY, const int MoveTime, const eEasingType MoveType = eEasing_Linear, const eEasingFunction EasingFunction = eEasingFunction_Out);
	void SetPosition(const double PositionX, const double PositionY);	// 座標を指定
	void SetPositionX(const double PositionX);	// 座標を指定
	void SetPositionY(const double PositionY);	// 座標を指定
	void SetCollisionRange(const int Num, const double RangeX, const double RangeY, const eCollisionType CollisionType = eCollision_Rectangle);		// 衝突判定の大きさを設定
	void GetPosition(double &PositionX, double &PositionY);	// 座標を取得
	double GetPositionX();	// 座標取得
	double GetPositionY();
	double GetAngleToSprite(cSprite &Sprite);
	std::vector<cCollider> GetCollider();
	cVector2D* GetMoveVectorPointer();	// 移動用ベクトルのアドレスを取得
	//cVector2D* GetCollisionVectorPointer();	// 衝突判定用ベクトルのアドレスを取得
	bool GetCollisionFlag(cSprite &Sprite);	// 他のスプライトと衝突したか調べる

	virtual void Initialize() override;
	virtual void Finalize() override;
	virtual void Update() override;
	virtual void Draw() override;
};