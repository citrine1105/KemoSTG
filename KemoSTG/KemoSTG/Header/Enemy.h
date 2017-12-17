#pragma once
//#include "Sprite.h"
#include "EnemyBulletGenerator.h"

extern cImageResourceContainer gEnemyImageContainer;

enum eEnemyType {
	eEnemy_Zako,

	eEnemy_TotalNum
};

struct sEnemyRegisterData {
public:
	eEnemyType mType;	// �G�̎��
	double mAppearanceX;	// �o���n�_X
	double mAppearanceY;	// �o���n�_Y
	int mMovePattern;	// �����̃p�^�[��
	int mGeneratorPattern;	// �e���p�^�[��
	int mBulletPattern;	// �e���p�^�[��
};

struct sEnemyPointMoveData : public sPointMoveData {
public:
	unsigned int mTiming;
};

struct sEnemyPolarFormMoveData : public sPolarFormMoveData {
public:
	unsigned int mTiming;
};

class cEnemy : public cSprite {
protected:
	bool fActive;
	eEnemyType mType;	// ���
	int mLife;	// �̗�
	int mMotion;	// ����
	cTimer mMotionTimer;	// �o�ߎ���
	cTimer mAnimeTimer;	// �A�j���[�V�����p�^�C�}�[
	std::vector<class cEnemyBulletGenerator> mBulletGenerator;	// �e���ˋ@�\
	std::vector<cVector2D> mBulletGeneratorVector;	// �e���ړ�����p�x�N�g��
	std::list<sEnemyPointMoveData> mPointMoveData;	// �ړ��f�[�^
	std::list<sEnemyPolarFormMoveData> mPolarFormMoveData;	// �ړ��f�[�^
public:
	cEnemy();
	cEnemy(sEnemyRegisterData &Data);
	~cEnemy();

	void Damage(const int Damage);
	void Erase();

	void SetBulletGenerateTarget(std::list<class cEnemyBullet> *Container);	// �e�̏o�͐���w��
	int GetLife();
	bool GetActiveFlag();
	bool GetAliveFlag();
	void Initialize() override;
	void Initialize(const sEnemyRegisterData &Data);
	void Update() override;
	void Draw() override;
};