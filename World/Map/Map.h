#pragma once
#include<memory>
#include<vector>

class MapObject;
class GameObjectManager;

/// <summary>
/// マップオブジェクト管理クラス
/// </summary>
class Map
{

public:

	Map();
	~Map();

	/// <summary>
	/// マップオブジェクトの生成を行う
	/// </summary>
	void Init();

	void Draw();
	void End();

	/// <summary>
	/// マップと
	/// </summary>
	/// <param name="pGameObjectMgr"></param>
	void CheckHitMap(GameObjectManager* pGameObjectMgr);

private:

	/// <summary>
	/// 管理するマップオブジェクト
	/// </summary>
	std::vector<std::unique_ptr<MapObject>>m_pMapObjects;
	//std::vector<MapObject*>m_pMapObjects;

};
