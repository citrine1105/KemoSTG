#include "../Header/EnemyBullet.h"

void cEnemyBullet::Initialize(cPoint2D &Position, cVector2D &MoveVector, const eBulletType Type) {

}

void cEnemyBullet::Update() {
	if (pTargetPlayer != nullptr) {	// �ڕW�̓G��������
		mMoveVector.SetAngle(this->GetAngleToSprite(*pTargetPlayer));	// �v���C���[��ǔ�����
	}
	cBullet::Update();
}