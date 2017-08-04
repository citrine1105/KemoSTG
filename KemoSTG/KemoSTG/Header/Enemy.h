#pragma once
#include "Sprite.h"

class cEnemy : public cSprite {
protected:
	unsigned int mLife;	// ‘Ì—Í

public:
	void Initialize() override;
	void Update() override;
	void Draw() override;
};