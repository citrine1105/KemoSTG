#include "../Header/Player.h"

cImageResourceContainer gPlayerImageContainer;
cSoundResource gPossessSound;
cSoundResourceContainer gBombSoundContainer;

cPlayer::cPlayer() : cSprite(), fEntry(false), /*fAlive(false),*/
	mInvincibleTime(60 * 5, 60 * 5, eCountMode_CountDown), mPossessTime(15.0, 30.0, eCountMode_CountDown),
	pInputPad(nullptr), mMoveSpeed(1.0), mLife(cGameConfig::GetInstance()->GetConfig().mLife), mBomb(3),
	mScoreRate(1), mMaxLife(7), mMaxBomb(6) {
	this->Initialize();
}

cPlayer::~cPlayer() {
	
}

void cPlayer::Entry() {
	fEntry = true;
}

void cPlayer::Bomb() {
	if (mBomb > 0) {
		PlaySoundMem(gBombSoundContainer.GetElement(mScore.mCharacter)->GetHandle(), DX_PLAYTYPE_BACK);
		mInvincibleTime.SetSecond(8.0);
		mInvincibleTime.Start();
		mScore.mBomb++;
		mBomb--;
		// TODO: ボム発動処理もここに書く
	}
}

void cPlayer::Damage() {
	++mScore.mDamaged;
	if (mLife > 0) {
		mLife--;
	}
	mPossessTime.Stop();	// 憑依解除
	switch (mScore.mType) {
	case ePossess_Half:
		mScoreRate = static_cast<unsigned int>(ceil(mScoreRate / 2.0));	// スコア倍率を半減
		mBomb = 3 + mScore.mDamaged;	// ボムを回復+補充
		mPossessTime.Reset();	// 憑依時間を初期値に戻す
		break;
	case ePossess_Full:
		mScoreRate = static_cast<unsigned int>(ceil(mScoreRate / 4.0));	// スコア倍率を3/4減
		mBomb = 3;	// ボムを回復
		if (this->GetPossessGauge() <= 50.0) {	// 50%以下の場合
			mPossessTime.Reset();	// 憑依時間を回復
		}
		break;
	default:
		mScoreRate = 999;
		break;
	}
	mInvincibleTime.Reset();
	mInvincibleTime.Start();
}

void cPlayer::Extend() {
	if (mLife < mMaxLife) {	// 最大ライフより少ない場合
		++mLife;	// ライフを増やす
	}
}

void cPlayer::Continue() {
	//mScore.mScore = ++mScore.mContinue >= 9 ? 9 : mScore.mContinue;
	mScore.mContinue++;	// コンティニュー回数加算
	if (mScore.mContinue >= 9) {
		mScore.mScore = 9;	// 9回以上
	}
	else {
		mScore.mScore = mScore.mContinue;	// それ以外
	}
}

void cPlayer::SetInputPad(cVirtualPad *Pad) {
	pInputPad = Pad;
}

void cPlayer::SetBulletGenerateTarget(std::list<cPlayerBullet> *Container) {
	for (auto &i : mBulletGenerator) {
		i.SetOutputTarget(Container);	// 弾の出力先を設定
	}
}

bool cPlayer::GetEntryFlag() {
	return fEntry;
}

bool cPlayer::GetAliveFlag() {
	if (fEntry && mLife > 0) {
		return true;
	}
	return false;
}

double cPlayer::GetPossessGauge() {
	return static_cast<double>(mPossessTime.GetTime()) / static_cast<double>(mPossessTime.GetMaxTime()) * 100.0;
	//return static_cast<double>(mPossessTime.GetTime());
}

unsigned char cPlayer::GetLife() {
	return mLife;
}

unsigned char cPlayer::GetBomb() {
	return mBomb;
}

unsigned int cPlayer::GetScoreRate() {
	return mScoreRate;
}

const sScoreData cPlayer::GetScore() {
	return mScore;
}

bool cPlayer::GetPossessFlag() {
	return mPossessTime.GetActiveFlag();
}

bool cPlayer::GetInvincibleFlag() {
	if (mInvincibleTime.GetTime() > 0) {
		return true;
	}
	return false;
}

void cPlayer::AddScore(const unsigned int Score) {
	if (Score > 0) {
		mScore.mScore += Score;
	}
}

void cPlayer::AddScoreRate(const unsigned int ScoreRate) {
	if (ScoreRate > 0) {
		mScoreRate += ScoreRate;
	}
	if (mScoreRate > mScore.mMaxRate) {
		mScore.mMaxRate = mScoreRate;
	}
}

void cPlayer::Initialize() {
	mCollider.resize(1);
	mCollider.at(0).SetCollisionType(eCollision_Ellipse);
	mCollider.at(0).SetRange(1.0, 1.0);
	mScore.mName.clear();
	mMoveSpeed = 7.2;	// TODO: キャラごとに速度を変えるようにする
	mLife = cGameConfig::GetInstance()->GetConfig().mLife;
	mBomb = 3;
	mScoreRate = 1U;
	mScore.mScore = 0U;
	mScore.mBomb = 0;
	mScore.mDamaged = 0;
	mScore.mContinue = 0;
	mScore.mMaxRate = 1U;
	mScore.mCharacter = ePlayer_Rin;
	mScore.mType = ePossess_Half;
	mPosition.SetPoint(GAME_SCREEN_WIDTH / 2.0, GAME_SCREEN_HEIGHT * 4.0 / 5.0);	// 初期位置
	mInvincibleTime.Start();
	mAnimeTimer.Initialize(0, 15 * 3 - 1, eCountMode_CountUp, true);
	mAnimeTimer.Start();
	mBulletGenerator.resize(4);
	mBulletGeneratorVector.resize(4);
	for (auto &i : mBulletGeneratorVector) {
		i.SetMagnitude(1.0);
	}
	mBulletGeneratorVector.at(0).SetAngle(TO_RADIAN(0.0));
	mBulletGeneratorVector.at(1).SetAngle(TO_RADIAN(90.0));
	mBulletGeneratorVector.at(2).SetAngle(TO_RADIAN(180.0));
	mBulletGeneratorVector.at(3).SetAngle(TO_RADIAN(270.0));
}

void cPlayer::Update() {
	mInvincibleTime.Update();	// 無敵時間カウント
	mPossessTime.Update();	// 憑依時間カウント
	mAnimeTimer.Update();

	// 憑依
	if (pInputPad->GetInputState(eButton_Possess) == 1) {
		if (mPossessTime.GetActiveFlag()) {
			PlaySoundMem(gPossessSound.GetHandle(), DX_PLAYTYPE_BACK);
			mPossessTime.Stop();
			mPossessTime.AddTime(-30);
			if (mPossessTime.GetTime() < 0) {
				mPossessTime.SetTime(0);
			}
		}
		else if (mPossessTime.GetTime() > 0) {
			PlaySoundMem(gPossessSound.GetHandle(), DX_PLAYTYPE_BACK);
			mPossessTime.Start();
		}
	}

	if (pInputPad->GetInputState(eButton_Shot) > 30 ||
		(pInputPad->GetInputState(eButton_Shot) > 0 && pInputPad->GetInputState(eButton_FullAuto) > 0)) {
		fSlowMove = true;	// レーザー攻撃(低速移動)に切り替え
	}
	else {
		fSlowMove = false;	// ショット攻撃(高速移動)に切り替え
	}
	mMoveVector.SetElement(0.0, 0.0);

	// 移動
	if (pInputPad != nullptr) {
		if (pInputPad->GetInputState(eDPad_Up) > 0) {
			mMoveVector.AddElement(0.0, -1.0);
		}
		else if (pInputPad->GetInputState(eDPad_Down) > 0) {
			mMoveVector.AddElement(0.0, 1.0);
		}

		if (pInputPad->GetInputState(eDPad_Left) > 0) {
			mMoveVector.AddElement(-1.0, 0.0);
		}
		else if (pInputPad->GetInputState(eDPad_Right) > 0) {
			mMoveVector.AddElement(1.0, 0.0);
		}
	}

	if (mMoveVector.GetElementX() != 0.0 ||
		mMoveVector.GetElementY() != 0.0) {
		if (fSlowMove) {
			mMoveVector.SetMagnitude(mMoveSpeed / 2.0);	// 半分の移動速度
		}
		else {
			mMoveVector.SetMagnitude(mMoveSpeed);	// 通常の移動速度
		}
		this->Move();	// 移動
	}

	// 画面外飛び出し
	if (mPosition.GetX() <= 32.0) {
		mPosition.SetPoint(32.0, mPosition.GetY());
	}
	else if (mPosition.GetX() >= GAME_SCREEN_WIDTH - 32.0) {
		mPosition.SetPoint(GAME_SCREEN_WIDTH - 32.0, mPosition.GetY());
	}

	if (mPosition.GetY() <= GAME_SCREEN_HEIGHT / 5.0) {
		mPosition.SetPoint(mPosition.GetX(), GAME_SCREEN_HEIGHT / 5.0);
	}
	else if (mPosition.GetY() >= GAME_SCREEN_HEIGHT - 48.0) {
		mPosition.SetPoint(mPosition.GetX(), GAME_SCREEN_HEIGHT - 48.0);
	}

	// 弾源
	for (auto &i : mBulletGeneratorVector) {
		i.SetMagnitude(fSlowMove ? 48.0 : 72.0);
		i.SetStartPoint(mPosition);
		i.AddAngle(TO_RADIAN(3.6));
	}

	for (int i = 0; i < mBulletGenerator.size(); i++) {
		mBulletGenerator.at(i).SetPosition(mBulletGeneratorVector.at(i).GetEndPoint());	// 座標セット
	}

	if ((pInputPad->GetInputState(eButton_Shot) < 4 * 3 && pInputPad->GetInputState(eButton_Shot) % 4 == 1) || pInputPad->GetInputState(eButton_FullAuto) % 4 == 1) {
		for (int i = 0; i < mBulletGenerator.size(); i++) {
			cPlayerBullet tBullet;	// 弾
			cVector2D tMoveVector;	// 弾移動速度
			tMoveVector.SetPolarForm(TO_RADIAN(-90.0), 23.5);
			tBullet.Initialize(tMoveVector, mScore.mCharacter);
										
			mBulletGenerator.at(i).AddBullet(tBullet);
			mBulletGenerator.at(i).Generate();

			PlaySoundMem(gPlayerShotSoundContainer.GetElement(ePlayer_Rin)->GetHandle(), DX_PLAYTYPE_BACK);
		}
	}

	if (pInputPad->GetInputState(eButton_Bomb) == 1) {
		this->Bomb();
	}

	for (auto &i : mCollider) {
		i.SetPosition(mPosition);
	}
	cSprite::Update();
}

void cPlayer::Draw() {
	if ((mInvincibleTime.GetTime() > 0 && mInvincibleTime.GetTime() % 4 < 2)
		|| mInvincibleTime.GetTime() <= 0) {
		DrawRotaGraphF(mPosition.GetX(), mPosition.GetY(), 1.0, 0.0, gPlayerImageContainer.GetElement(mScore.mCharacter)->GetHandle(), TRUE);
	}
#ifdef _DEBUG
	for (auto &i : mBulletGenerator) {
		DrawCircle(i.GetPositionX(), i.GetPositionY(), 3, GetColor(0xFF, 0xFF, 0xFF));
	}
	for (auto &i : mCollider) {
		i.Draw();
	}
#endif
	//DrawCircleAA(mCollider.at(0).GetPosition().GetX(), mCollider.at(0).GetPosition().GetY(), 1, 8, GetColor(0xFF, 0xFF, 0xFF));
}