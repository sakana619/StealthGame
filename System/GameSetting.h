#pragma once

class GameSetting
{

public:

	GameSetting() = default;
	~GameSetting() = default;

	/// <summary>
	/// ウィンドウの初期設定
	/// </summary>
	void static InitWindow();

	/// <summary>
	/// 3Dの描画設定
	/// </summary>
	void InitDxLib3D();

};

