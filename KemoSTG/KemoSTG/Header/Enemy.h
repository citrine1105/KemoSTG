#pragma once
//#include "Sprite.h"
#include "EnemyBulletGenerator.h"

class cEnemy : public cSprite {
protected:
	unsigned int mLife;	// �̗�
	cTimer mAnimeTimer;	// �A�j���[�V�����p�^�C�}�[
	std::vector<class cEnemyBulletGenerator> mBulletGenerator;	// �e���ˋ@�\
	std::vector<cVector2D> mBulletGeneratorVector;	// �e���ړ�����p�x�N�g��
public:
	cEnemy();
	~cEnemy();

	void SetBulletGenerateTarget(std::list<class cEnemyBullet> *Container);	// �e�̏o�͐���w��
	unsigned int GetLife();
	void Initialize() override;
	void Update() override;
	void Draw() override;
};