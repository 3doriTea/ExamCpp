#pragma once


namespace Input
{
	//�L�[�{�[�h�擾�֘A
	void KeyStateUpdate();
	bool IsKeyUp(int keyCode);
	bool IsKeyDown(int keyCode);
	/// <summary>
	/// ������Ă��邩�ǂ���
	/// </summary>
	/// <param name="keyCode">DxLib�̃L�[�R�[�h</param>
	/// <returns>�����ꂽ true / false</returns>
	bool IsKeepKeyDown(int keyCode);
}
