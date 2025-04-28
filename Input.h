#pragma once


namespace Input
{
	//キーボード取得関連
	void KeyStateUpdate();
	bool IsKeyUp(int keyCode);
	bool IsKeyDown(int keyCode);
	int IsKeepKeyDown(int keyCode);
}