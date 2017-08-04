#pragma once
#include "Sprite.h"

class cBullet : public cSprite {
protected:
	bool fActive;
public:
	void Erase();
	bool GetActiveFlag();

	void Initialize() override;
	void Initialize(cPoint2D &Position, cVector2D &MoveVector);
	void Update() override;
};