#include "../Header/Player.h"

cPlayer::cPlayer() : cSprite(), fEntry(false), fAlive(false),
	mInvincibleTime(60 * 5, 60 * 5, eCountMode_CountDown), mPossessTime(15.0, 30.0, eCountMode_CountDown),
	pInputPad(nullptr), mMoveSpeed(1.0), mLife(3), mBomb(3),
	mScoreRate(1) {
	this->Initialize();
}

cPlayer::~cPlayer() {

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
	return fAlive;
}

double cPlayer::GetPossessGauge() {
	return static_cast<double>(mPossessTime.GetTime()) / static_cast<double>(mPossessTime.GetMaxTime()) * 100.0;
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

void cPlayer::Initialize() {
	mScore.mName.clear();
	mMoveSpeed = 7.2;	// TODO: キャラごとに速度を変えるようにする
	mScore.mScore = 0U;
	mScore.mContinue = 0;
	mScore.mMaxRate = 1U;
	mScore.mCharacter = ePlayer_TotalNum;
	mScore.mType = ePossess_None;
	mPosition.SetPoint(GAME_SCREEN_WIDTH / 2.0, GAME_SCREEN_HEIGHT * 4.0 / 5.0);	// 初期位置
	mAnimeTimer.Initialize(0, 15 * 3 - 1, eCountMode_CountUp, true);
	mAnimeTimer.Start();
	mBulletGenerator.resize(4);
	mBulletGeneratorVector.resize(4);
	for (auto &i : mBulletGeneratorVector) {
		i.SetMagnitude(48.0);
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

	if (pInputPad->GetInputState(eButton_Possess) == 1) {	// 憑依
		if (mPossessTime.GetActiveFlag()) {
			mPossessTime.Stop();
			mPossessTime.AddTime(-30);
		}
		else {
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
	else if (mPosition.GetY() >= GAME_SCREEN_HEIGHT - 64.0) {
		mPosition.SetPoint(mPosition.GetX(), GAME_SCREEN_HEIGHT - 64.0);
	}

	// 弾源
	for (auto &i : mBulletGeneratorVector) {
		i.SetStartPoint(mPosition);
		i.AddAngle(TO_RADIAN(3.6));
	}

	for (int i = 0; i < mBulletGenerator.size(); i++) {
		mBulletGenerator.at(i).SetPosition(mBulletGeneratorVector.at(i).GetEndPoint());	// 座標セット
	}

	if ((pInputPad->GetInputState(eButton_Shot) < 4 * 3 && pInputPad->GetInputState(eButton_Shot) % 4 == 1) || pInputPad->GetInputState(eButton_FullAuto) % 4 == 1) {
		//for (auto &i : mBulletGenerator) {
		//	cPlayerBullet tBullet;	// 弾
		//	cVector2D tMoveVector;	// 弾移動速度
		//	tMoveVector.SetPolarForm(TO_RADIAN(-90.0), 20.0);
		//	tBullet.Initialize(tMoveVector, mScore.mCharacter);
		//	
		//	i.AddBullet(tBullet);
		//	i.Generate();
		//}
		for (int i = 0; i < mBulletGenerator.size(); i++) {
			cPlayerBullet tBullet;	// 弾
			cVector2D tMoveVector;	// 弾移動速度
			tMoveVector.SetPolarForm(TO_RADIAN(-90.0), 23.5);
			tBullet.Initialize(tMoveVector, mScore.mCharacter);
										
			mBulletGenerator.at(i).AddBullet(tBullet);
			mBulletGenerator.at(i).Generate();
		}
	}
}

void cPlayer::Draw() {
	DrawRotaGraph(mPosition.GetX(), mPosition.GetY(), 1.0, 0.0, cImageResourceContainer::GetInstance()->GetElement(eImage_PlayerRin)->GetHandle(mAnimeTimer.GetTime() / 15), TRUE);
#ifdef _DEBUG
	for (auto &i : mBulletGenerator) {
		DrawCircle(i.GetPositionX(), i.GetPositionY(), 3, GetColor(0xFF, 0xFF, 0xFF));
	}
#endif
}