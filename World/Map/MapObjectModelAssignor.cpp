#include "MapObjectModelAssignor.h"
#include"MapData.h"
#include<array>

#include<DxLib.h>
#include<cassert>

namespace {

	const char* const kModelPath[static_cast<int>(MapData::ObjectType::Max)]{

		".\\Resource\\Object\\MapObject.mv1",
		".\\Resource\\Object\\MapObject.mv1",
	};

}

MapObjectModelAssignor::MapObjectModelAssignor() :
	m_objectModels()
{
	m_objectModels.fill(-1);

	for (int i = 0; i < m_objectModels.size(); i++) {
		//読み込み
		int model = MV1LoadModel(kModelPath[i]);

		//読み込みが失敗していたら警告
		assert(model != -1 && "MapObjectModelAssignor::MapObjectModelAssignor fail to load model");

		//サイズを設定
		VECTOR scale = MapData::kSize::scale.ToVECTOR();
		MV1SetScale(model, scale);

		m_objectModels[i] = model;

	}

}

MapObjectModelAssignor& MapObjectModelAssignor::GetInstance()
{
	static MapObjectModelAssignor instance;
	return instance;
}

int MapObjectModelAssignor::GetModel(MapData::ObjectType type)
{
	//返すモデル
	int model = m_objectModels[static_cast<int>(type)];

	//読み込みが失敗していたら警告
	assert(model != -1 && "MapObjectModelAssignor::GetModel fail to load model");

	return model;
}

void MapObjectModelAssignor::DeleteModel()
{
	//すべてのモデルを破棄
	for (auto& model : m_objectModels) {
		//モデルの破棄
		MV1DeleteModel(model);
	}

	m_objectModels.fill(-1);

}
