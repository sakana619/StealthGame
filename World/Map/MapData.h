#pragma once
#include"../../Utility/Vector3.h"
#include<vector>

/// <summary>
/// マップのデータ
/// </summary>
namespace MapData
{

	struct kSize {

		static const Vector3 scale;
		static const Vector3 offSetPos;

	};

	/// <summary>
	/// マップオブジェクトのタイプ
	/// </summary>
	enum class ObjectType {
		Invalid = -1,	//無効値

		Floor,			//床
		Wall,			//壁

		Max,			//最大数
	};

	/// <summary>
	/// ステージのオブジェクトのタイプを取得
	/// </summary>
	/// <returns></returns>
	std::vector<std::vector<ObjectType>> GetStageData();

};
