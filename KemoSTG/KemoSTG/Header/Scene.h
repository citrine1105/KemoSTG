﻿#pragma once
#include "Include.h"

enum eScene {

};

class cScene : public iInitialization, iActivity {
public:
	virtual void Initialize() override;
	virtual void Finalize() override;
	virtual void Update() override;
	virtual void Draw() override;
};