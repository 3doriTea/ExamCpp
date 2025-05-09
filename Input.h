#pragma once


namespace Input
{
	//キーボード取得関連
	void KeyStateUpdate();
	bool IsKeyUp(int keyCode);
	bool IsKeyDown(int keyCode);
	/// <summary>
	/// 押されているかどうか
	/// </summary>
	/// <param name="keyCode">DxLibのキーコード</param>
	/// <returns>押された true / false</returns>
	bool IsKeepKeyDown(int keyCode);
}
