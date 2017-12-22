#include "../Header/Enemy.h"
#include "../Header/GameManager.h"

cImageResourceContainer gEnemyImageContainer;

cEnemy::cEnemy() : mLife(50), fActive(true), fCollisionEnable(false), mAppearanceTime(24) {
	this->Initialize();
}

cEnemy::cEnemy(sEnemyRegisterData &Data) : cEnemy() {
	this->Initialize(Data);
}

cEnemy::~cEnemy() {
	this->Finalize();
}

void cEnemy::Damage(const int Damage) {
	if (Damage > 0) {
		mLife -= Damage;
		if (mLife <= 0) {
			fCollisionEnable = false;	// 判定を無効にする
			this->Erase();
		}
	}
}

void cEnemy::Erase() {
	fActive = false;
	cGameManager::GetInstance()->GetEffectPointer()->push_back(cEffect(eEffect_BigBomb, mPosition));
}

void cEnemy::SetBulletGenerateTarget(std::list<cEnemyBullet> *Container) {
	for (auto &i : mBulletGenerator) {
		i.SetOutputTarget(Container);	// 弾の出力先を設定
	}
}

int cEnemy::GetLife() {
	return mLife;
}

bool cEnemy::GetActiveFlag() {
	return fActive;
}

bool cEnemy::GetAliveFlag() {
	if (mLife <= 0) {
		return false;
	}
	return true;
}

void cEnemy::Initialize() {
	mCollider.resize(1);
	mCollider.at(0).SetRange(1.0, 1.0);
	// TODO: 出現直後は判定を消したいが、消すとBulletOutColliderとの判定も消えてしまうので
	// 上手く処理するメソッドを作る
	mCollider.at(0).SetCollisionType(eCollision_Rectangle);
	mMotionTimer.Start();
	mAnimeTimer.Start();
	mBulletGenerator.resize(1);
	mBulletGeneratorVector.resize(1);

	sEnemyPolarFormMoveData tMove;
	tMove.mTiming = 120;
	tMove.mAngle = TO_RADIAN(GetRand(359));
	tMove.mMagnitude = 160.0;
	tMove.mMoveTime = 60;
	tMove.mMoveType = eEasing_Sine;
	tMove.mEasingFunction = eEasingFunction_InOut;
	for (int i = 0; i < 10; i++) {
		mPolarFormMoveData.push_back(tMove);
		tMove.mTiming += 120;
		tMove.mAngle = TO_RADIAN(GetRand(359));
	}
}

void cEnemy::Initialize(const sEnemyRegisterData &Data) {
	mPosition.SetPoint(Data.mAppearanceX, Data.mAppearanceY);
	mType = Data.mType;
	this->Initialize();
}

void cEnemy::Finalize() {
	mBulletGenerator.clear();
	mBulletGeneratorVector.clear();
}

void cEnemy::Update() {
	cSprite::Update();
	mAnimeTimer.Update();
	if (!fCollisionEnable) {
		if (mAnimeTimer.GetTime() >= mAppearanceTime) {	// 出現アニメーションが終わったら
			fCollisionEnable = true;	// 判定を有効に
			mAnimeTimer.Reset();		// タイマーをリセット
		}
		else if (!this->GetAliveFlag()) {	// ライフがなくなった場合
			mAnimeTimer.Reset();
		}
	}

	if (fCollisionEnable) {
		mMotionTimer.Update();
		mCollider.at(0).SetRange(32.0, 32.0);
		switch (mType) {
		default:
			for (auto &i : mCollider) {
				i.SetPosition(mPosition);
			}
		}

		// 弾源
		for (auto &i : mBulletGeneratorVector) {
			i.SetStartPoint(mPosition);
		}

		for (int i = 0; i < mBulletGenerator.size(); i++) {
			mBulletGenerator.at(i).SetPosition(mBulletGeneratorVector.at(i).GetEndPoint());	// 座標セット
		}

		for (auto i = mPointMoveData.begin(); i != mPointMoveData.end();) {
			if (mMotionTimer.GetTime() == i->mTiming) {
				this->MoveToPoint(*i);
				i = mPointMoveData.erase(i);
				continue;
			}
			i++;
		}

		for (auto i = mPolarFormMoveData.begin(); i != mPolarFormMoveData.end();) {
			if (mMotionTimer.GetTime() == i->mTiming) {
				this->Move(*i);
				i = mPolarFormMoveData.erase(i);
				continue;
			}
			i++;
		}

		if (mMotionTimer.GetTime() % 40 == 0) {
			for (int i = 0; i < mBulletGenerator.size(); i++) {
				cEnemyBullet tBullet;	// 弾
				cVector2D tMoveVector;	// 弾移動速度
				tMoveVector.SetPolarForm(TO_RADIAN(GetRand(360)), 1.9);
				for (int j = 0; j < 4; j++) {
					tMoveVector.AddAngle(TO_RADIAN(360.0 / 4.0));
					tBullet.Initialize(tMoveVector, eBullet_Normal);
					mBulletGenerator.at(0).AddBullet(tBullet);
				}
			}
			mBulletGenerator.at(0).Generate();
		}
	}
}

void cEnemy::Draw() {
	//if (mAnimeTimer.GetTime() < mAppearanceTime) {
	//	DrawRotaGraph3F(mPosition.GetX(), mPosition.GetY(), gEnemyImageContainer.GetElement(mType)->GetSizeX() / 2.0, gEnemyImageContainer.GetElement(mType)->GetSizeY() / 2.0, mAnimeTimer.GetTime() / static_cast<double>(mAppearanceTime), 1.0 + (mAppearanceTime - mAnimeTimer.GetTime()) / static_cast<double>(mAppearanceTime) * 2.0, 0.0, gEnemyImageContainer.GetElement(mType)->GetHandle(), TRUE);
	//}
	//else {
	//	DrawRotaGraphF(mPosition.GetX(), mPosition.GetY(), 1.0, 0.0, gEnemyImageContainer.GetElement(mType)->GetHandle(), TRUE);
	//}
	if (fCollisionEnable) {
		DrawRotaGraphF(mPosition.GetX(), mPosition.GetY(), 1.0, 0.0, gEnemyImageContainer.GetElement(mType)->GetHandle(), TRUE);
	}
	else {
		if (mAnimeTimer.GetTime() < mAppearanceTime) {
			DrawRotaGraph3F(mPosition.GetX(), mPosition.GetY(), gEnemyImageContainer.GetElement(mType)->GetSizeX() / 2.0, gEnemyImageContainer.GetElement(mType)->GetSizeY() / 2.0, mAnimeTimer.GetTime() / static_cast<double>(mAppearanceTime), 1.0 + (mAppearanceTime - mAnimeTimer.GetTime()) / static_cast<double>(mAppearanceTime) * 2.0, 0.0, gEnemyImageContainer.GetElement(mType)->GetHandle(), TRUE);
		}
		else if (!this->GetAliveFlag()) {
			DrawRotaGraph3F(mPosition.GetX(), mPosition.GetY(), gEnemyImageContainer.GetElement(mType)->GetSizeX() / 2.0, gEnemyImageContainer.GetElement(mType)->GetSizeY() / 2.0, 1.0 + (mAppearanceTime - mAnimeTimer.GetTime()) / static_cast<double>(mAppearanceTime) * 2.0, mAnimeTimer.GetTime() / static_cast<double>(mAppearanceTime), 0.0, gEnemyImageContainer.GetElement(mType)->GetHandle(), TRUE);
		}
	}
#ifdef _DEBUG
	std::tstring tHP;
	tHP = _T("HP: ");
	tHP += std::to_tstring(mLife);
	DrawStringFToHandle(mPosition.GetX() - GetDrawStringWidthToHandle(tHP.c_str(), tHP.size(), gGameFontContainer.GetElement(eGameFont_Interface)->GetHandle()) / 2, mPosition.GetY() + mCollider.at(0).GetRangeY(), tHP.c_str(), GetColor(0xFF, 0xFF, 0xFF), gGameFontContainer.GetElement(eGameFont_Interface)->GetHandle());
	for (auto &i : mCollider) {
		i.Draw();
	}
#endif
}