#pragma once

class iActivity {
public:
	virtual void Update() = 0;	// 更新処理
	virtual void Draw() = 0;		// 描画処理
};