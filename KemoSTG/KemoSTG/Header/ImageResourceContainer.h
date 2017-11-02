#pragma once
#include "ImageResource.h"

enum eImageIndex {
	eImage_Title,
	eImage_GameLogo,
	eImage_GameTitle,
	eImage_Background,

	eImage_Life,
	eImage_Bomb,
	eImage_ScoreBoard,
	eImage_RateNumber,
	eImage_LifeGauge,
	eImage_CaptionBomb,
	eImage_CaptionTime,
	eImage_SelectTimer,

	eImage_GameBackGround,
	eImage_GameOver,

	eImage_PlayerRin,

	eImage_PlayerBullet,
	eImage_EnemyBullet,

	eImage_RectCollisionRange,
	eImage_EllipseCollisionRange,

	eImage_None
};

class cImageResourceContainer : public iInitialization {
private:
	cImageResourceContainer() {
		this->Initialize();
	}
	cImageResourceContainer(const cImageResourceContainer& r) {}
	cImageResourceContainer& operator=(const cImageResourceContainer& r) {}
	~cImageResourceContainer() {
		this->Finalize();
	}
protected:
	std::vector<cImageResource> mImageArray;
public:
	static cImageResourceContainer* GetInstance() {
		static cImageResourceContainer inst;
		return &inst;
	}

	cImageResource* GetElement(eImageIndex Imdex);

	void Initialize() override;
	void Finalize() override;
};