#pragma once

class iInitialization {
public:
	virtual void Initialize() = 0;	// 初期化処理
	virtual void Finalize() = 0;		// 終了処理
};