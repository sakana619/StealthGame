#pragma once
#include"MapData.h"

#include<array>

/// <summary>
/// マップオブジェクトのモデルを取得するクラス
/// </summary>
class MapObjectModelAssignor
{

public:

	static MapObjectModelAssignor& GetInstance();

	/// <summary>
	/// 指定したタイプのモデルを入手
	/// </summary>
	/// <param name="type"></param>
	/// <returns></returns>
	int GetModel(MapData::ObjectType type);

	/// <summary>
	/// モデルの破棄を行う
	/// </summary>
	void DeleteModel();

private:

	/// <summary>
	/// モデルの読み込みを行う
	/// </summary>
	MapObjectModelAssignor();

	// コピー禁止
	MapObjectModelAssignor(const MapObjectModelAssignor&) = delete;
	// コピー代入禁止
	MapObjectModelAssignor& operator=(const MapObjectModelAssignor&) = delete;
	// ムーブ禁止
	MapObjectModelAssignor(MapObjectModelAssignor&&) = delete;
	// ムーブ代入禁止
	MapObjectModelAssignor& operator=(const MapObjectModelAssignor&&) = delete;

private:

	/// <summary>
	/// オブジェクトのモデル配列
	/// </summary>
	std::array<int, static_cast<int>(MapData::ObjectType::Max)>m_objectModels;

	/// <summary>
	/// 地面のテクスチャーリスト
	/// </summary>
	std::vector<int>m_textureList;

};
