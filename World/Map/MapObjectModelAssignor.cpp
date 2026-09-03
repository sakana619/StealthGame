#include "MapObjectModelAssignor.h"
#include"MapData.h"
#include<array>

#include<DxLib.h>
#include<cassert>

namespace {
	//モデルのファイルパス
	const char* const kModelPath[static_cast<int>(MapData::ObjectType::Max)]{

		".\\Resource\\Object\\MapObject.mv1",
		".\\Resource\\Object\\MapObject.mv1",
	};
	//テクスチャーの数
	constexpr int kTextureCount = 3;
	//テクスチャーのファイルパス
	const char* const kTexturePath[kTextureCount]{
		".\\Resource\\Texture\\Dirt_01.png",
		".\\Resource\\Texture\\grass.png",
		".\\Resource\\Texture\\rocky_terrain_02_diff_4k.jpg",
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

	for (int i = 0; i < kTextureCount; i++) {
		//読み込み
		int texture = LoadGraph(kTexturePath[i]);
		//失敗していたら警告
		assert(texture != -1 && "MapObjectModelAssignor::MapObjectModelAssignor fail to load texture");
		//テクスチャーのリストに追加
		m_textureList.push_back(texture);

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
	int model = MV1DuplicateModel(m_objectModels[static_cast<int>(type)]);

	//読み込みが失敗していたら警告
	assert(model != -1 && "MapObjectModelAssignor::GetModel fail to load model");

	//サイズを設定
	VECTOR scale = MapData::kSize::scale.ToVECTOR();
	MV1SetScale(model, scale);

	//モデルのテクスチャーの数取得
	int textureNum = MV1GetTextureNum(model);
	//テクスチャーをランダムに取得
	int rand = GetRand(kTextureCount - 1);
	//テクスチャーを取得
	int texture = m_textureList[rand];

	for (int i = 0; i < textureNum; i++) {
		//テクスチャーのセット
		MV1SetTextureGraphHandle(model, i, texture, false);
	}

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

	//すべてのテクスチャーを破棄
	for (auto& texture : m_textureList) {
		//テクスチャーの破棄
		DeleteGraph(texture);
		texture = -1;
	}

}
