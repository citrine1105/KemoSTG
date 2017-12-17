#pragma once
#include "Sprite.h"

class cBullet : public cSprite {
protected:
	bool fActive;
public:
	cBullet();
	~cBullet();

	void Erase();
	bool GetActiveFlag();

	void Initialize() override;
	void Initialize(cVector2D &MoveVector);
	virtual void Update() override;
};