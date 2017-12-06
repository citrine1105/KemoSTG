#pragma once
#include "ImageResource.h"

enum eImageIndex {
	eImage_Title,
	eImage_TitleLogo,
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
	eImage_Enemy,

	eImage_PlayerBullet,
	eImage_EnemyBullet,

	eImage_RectCollisionRange,
	eImage_EllipseCollisionRange,

	eImage_None
};

class cImageResourceContainer : public iInitialization {
protected:
	std::vector<cImageResource> mImageArray;
public:
	cImageResourceContainer();
	~cImageResourceContainer();

	void Load();
	void Delete();

	unsigned int GetResourceCount();
	cImageResource* GetElement(const unsigned int Index);

	void Initialize() override;
	void Initialize(const unsigned int Num);
	void Finalize() override;
};