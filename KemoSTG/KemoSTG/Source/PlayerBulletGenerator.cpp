#include "../Header/PlayerBulletGenerator.h"
#include "../Header/GameScene/GameMain.h"

cPlayerBulletGenerator::cPlayerBulletGenerator() 
	: pTargetContainer(nullptr) {
	mBuffer.clear();
}

cPlayerBulletGenerator::~cPlayerBulletGenerator() {
	mBuffer.clear();
}

void cPlayerBulletGenerator::SetOutputTarget(std::list<cPlayerBullet> *Container) {
	pTargetContainer = Container;
}

void cPlayerBulletGenerator::AddBullet(cPlayerBullet &Bullet) {
	mBuffer.push_back(Bullet);
}

void cPlayerBulletGenerator::Generate() {
	for (auto &i : mBuffer) {
		i.SetPosition(mPosition.GetX(), mPosition.GetY());	// À•WÝ’è(‰ö‚µ‚¢)
		//printfDx(_T("X:%.1f Y:%.1f\nAngle:%.1f\n"), mPosition.GetX(), mPosition.GetY(), i.GetMoveVectorPointer()->GetAngle());
	}
	if (pTargetContainer != nullptr) {
		for (auto &i : mBuffer) {
			pTargetContainer->push_back(i);	// o—Í
			//printfDx(_T("%f %f\n"), i.GetMoveVectorPointer()->GetMagnitude(), i.GetMoveVectorPointer()->GetAngle());
		}
		mBuffer.clear();
	}
}

void cPlayerBulletGenerator::Clear() {
	mBuffer.clear();
}