#pragma once
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
	cVector2D mMoveVectorX;		// X軸移動処理用ベクトル
	cVector2D mMoveVectorY;		// Y軸移動処理用ベクトル
	cTimer mDelayTimerX;	// X軸移動処理用タイマー
	cTimer mDelayTimerY;	// Y軸移動処理用タイマー
	eEasingFunction mEaseFuncX;	// X軸移動関数
	eEasingFunction mEaseFuncY;	// Y軸移動関数
	eEasingType mMoveTypeX;		// X軸移動タイプ
	eEasingType mMoveTypeY;		// Y軸移動タイプ
	int mMoveTimeX;	// X軸移動にかかる時間(f)
	int mMoveTimeY;	// Y軸移動にかかる時間(f)
public:
	cSprite();	// デフォルトコンストラクタ
	~cSprite();	// デストラクタ

	void Move();		// ベクトルに準じて移動
	void MoveToPoint(const double PositionX, const double PositionY, const int MoveTime, const eEasingType MoveType = eEasing_Linear, const eEasingFunction EasingFunction = eEasingFunction_Out);	// 指定の場所に移動
	void MoveToPointX(const double PositionX, const int MoveTime, const eEasingType MoveType = eEasing_Linear, const eEasingFunction EasingFunction = eEasingFunction_Out);	// 指定の場所に移動
	void MoveToPointY(const double PositionY, const int MoveTime, const eEasingType MoveType = eEasing_Linear, const eEasingFunction EasingFunction = eEasingFunction_Out);	// 指定の場所に移動
	void AddToPoint(const double PositionX, const double PositionY, const int MoveTime, const eEasingType MoveType = eEasing_Linear, const eEasingFunction EasingFunction = eEasingFunction_Out);
	void AddToPointX(const double PositionX, const int MoveTime, const eEasingType MoveType = eEasing_Linear, const eEasingFunction EasingFunction = eEasingFunction_Out);
	void AddToPointY(const double PositionY, const int MoveTime, const eEasingType MoveType = eEasing_Linear, const eEasingFunction EasingFunction = eEasingFunction_Out);
	void SetPosition(cPoint2D &Point);	// 座標を指定
	void SetPosition(const double PositionX, const double PositionY);	// 座標を指定(数値指定版)
	void SetCollisionRange(const int Num, const double RangeX, const double RangeY, const eCollisionType CollisionType = eCollision_Rectangle);		// 衝突判定の大きさを設定
	cPoint2D GetPosition();	// 座標を取得
	double GetPositionX();	// X座標を取得
	double GetPositionY();	// Y座標を取得
	double GetAngleToSprite(cSprite &Sprite);
	std::vector<cCollider>* GetColliderPointer();
	cVector2D* GetMoveVectorPointer();	// 移動用ベクトルのアドレスを取得
	bool GetCollisionFlag(cSprite &Sprite);	// 他のスプライトと衝突したか調べる

	virtual void Initialize() override;
	virtual void Finalize() override;
	virtual void Update() override;
	virtual void Draw() override;
};