#pragma once
#include"LoadData.h"
#include"DataConvert.h"
#include"../../World/Chara/Enemy/EnemyData.h"

/// <summary>
/// データの割り振り
/// </summary>
namespace Data {

	template<typename T>
	struct FromData {

		static T Binding(const HeaderData& data) {
			static_assert(sizeof(T) == 0, "Binding定義されていない型");
			return T{};
		}

	};

	template<typename T>
	T Get(const HeaderData& data, const std::string& key) {

		auto it = data.find(key);

		if (it == data.end()) {

			//設定ミス
			assert(0 && "key not found");
			return T{};
		}

		//見つかったらvalueを変換して返す
		return Convert<T>(it->second);

	}

	template<>
	struct FromData<EnemyData> {
		static EnemyData Binding(const HeaderData& data) {

			EnemyData param;

			param.ID = Get<int>(data, "ID");
			param.patrolIndex = Get<int>(data, "patrolIndex");
			param.patrolPos.x = Get<float>(data, "posX");
			param.patrolPos.y = Get<float>(data, "posY");
			param.patrolPos.z = Get<float>(data, "posZ");

			return param;

		}

	};

}
