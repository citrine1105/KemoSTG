#pragma once
#include <fstream>
#include "picojson.h"
#include "Include.h"

class iConfig {
public:
	virtual int Load() = 0;
	virtual int Write() = 0;
	virtual void SetDefault() = 0;
};

enum eScreenRotation {	// 画面の回転状態
	eRotation_Horizontal,
	eRotation_RightRoll,
	eRotation_Reverse,
	eRotation_LeftRoll,

	eRotation_None
};

struct sSystemConfig {
	bool fArcade;
	bool fWindowMode;
	unsigned short mDisplayWidth;
	unsigned short mDisplayHeight;
	eScreenRotation mRotation;
	unsigned char mBGMVolume;
	unsigned char mSEVolume;
};

enum eGameDifficulty {	// ゲーム難易度
	eGameDiff_VeryEasy,	// とても簡単
	eGameDiff_Easy,		// 簡単
	eGameDiff_Normal,	// 普通
	eGameDiff_Hard,		// 難しい
	eGameDiff_VeryHard,	// とても難しい
	eGameDiff_Nightmare,	// 悪夢

	eGameDiff_TotalNum	// 総要素数
};

struct sGameConfig {
	unsigned char mZoomX;
	unsigned char mZoomY;
	short mPositionX;
	short mPositionY;
	unsigned char mLevel;
	unsigned char mLife;
};

class cSystemConfig : public iConfig {
private:
	cSystemConfig() {
		this->SetDefault();
	}
	cSystemConfig(const cSystemConfig &r) {}
	cSystemConfig& operator=(const cSystemConfig &r) {}
	~cSystemConfig() {}
protected:
	sSystemConfig mConfig;
public:
	static cSystemConfig* GetInstance() {
		static cSystemConfig inst;
		return &inst;
	}

	void SetDefault() override;
	const sSystemConfig GetConfig();
	int Load() override;
	int Write() override;
};

class cGameConfig : public iConfig {
private:
	cGameConfig() {
		this->SetDefault();
	}
	cGameConfig(const cGameConfig &r) {}
	cGameConfig& operator=(const cGameConfig &r) {}
	~cGameConfig() {}
protected:
	sGameConfig mConfig;
public:
	static cGameConfig* GetInstance() {
		static cGameConfig inst;
		return &inst;
	}

	void SetDefault() override;
	const sGameConfig GetConfig();
	int Load() override;
	int Write() override;
};