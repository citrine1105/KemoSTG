#pragma once
#include "Sprite.h"

enum eEffectType {
	eEffect_RateNum,	// レート
	eEffect_Bomb,	// 爆発

	eEffect_TotalNum	// 総要素数
};

extern cImageResourceContainer gEffectImageContainer;

class cEffect : public cSprite {
protected:
	eEffectType mType;	// エフェクト種類
	cTimer mAnimeTimer;

	const std::array<unsigned int, eEffect_TotalNum> mEffectTime{ { 28, 8 } };	// 各エフェクト再生時間
public:
	cEffect();	// デフォルトコンストラクタ
	cEffect(const eEffectType Type, cPoint2D &Position);	// エフェクト指定コンストラクタ
	~cEffect();	// デストラクタ

	bool GetPlayFlag();

	void Initialize() override;
	void Initialize(const eEffectType Type, cPoint2D &Position);
	void Finalize() override;
	void Update() override;
	void Draw() override;
};