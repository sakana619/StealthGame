#pragma once
#include"../Utility/Vector3.h"

/// <summary>
/// 敵の巡回に関するデータ
/// </summary>
struct EnemyData
{

	/// <summary>
	/// 敵のID
	/// </summary>
	int ID;

	/// <summary>
	/// 巡回座標の番号
	/// </summary>
	int patrolIndex;

	/// <summary>
	/// 巡回する座標
	/// </summary>
	Vector3 patrolPos;

};
