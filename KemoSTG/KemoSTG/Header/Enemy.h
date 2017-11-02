#pragma once
//#include "Sprite.h"
#include "EnemyBulletGenerator.h"

class cEnemy : public cSprite {
protected:
	int mLife;	// �̗�
	cTimer mAnimeTimer;	// �A�j���[�V�����p�^�C�}�[
	std::vector<class cEnemyBulletGenerator> mBulletGenerator;	// �e���ˋ@�\
	std::vector<cVector2D> mBulletGeneratorVector;	// �e���ړ�����p�x�N�g��
public:
	cEnemy();
	~cEnemy();

	void Damage(const int Damage);

	void SetBulletGenerateTarget(std::list<class cEnemyBullet> *Container);	// �e�̏o�͐���w��
	int GetLife();
	bool GetAliveFlag();
	void Initialize() override;
	void Update() override;
	void Draw() override;
};