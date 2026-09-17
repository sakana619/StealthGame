#pragma once

/// <summary>
/// 入力管理
/// </summary>
namespace Input
{

	void Update();

	/// <summary>
	/// 押さているか取得
	/// </summary>
	/// <param name="key"></param>
	/// <returns>指定のキーを取得している間true</returns>
	bool IsDown(int key);
	/// <summary>
	/// 押した瞬間を取得
	/// </summary>
	/// <param name="key"></param>
	/// <returns>指定のキーを押した瞬間ならtrue</returns>
	bool IsPressed(int key);
	/// <summary>
	/// 離した瞬間を取得
	/// </summary>
	/// <param name="key"></param>
	/// <returns>指定のキーを離した瞬間ならtrue</returns>
	bool IsReleased(int key);
	/// <summary>
	/// 長押ししているか取得
	/// </summary>
	/// <param name="key"></param>
	/// <returns>指定のキーを10フレーム押していたらtrue</returns>
	bool IsHold(int key);

};
