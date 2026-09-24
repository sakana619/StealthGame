#pragma once
#include"../../Utility/Vector3.h"

/// <summary>
/// ゴールのデータ
/// </summary>
struct GoalData
{
	/// <summary>
	/// ゴールの座標
	/// </summary>
	Vector3 position;
	/// <summary>
	/// ゴールの大きさ
	/// </summary>
	Vector3 scale;
	/// <summary>
	/// 当たり判定のサイズ
	/// </summary>
	Vector3 collisionSize;

};
