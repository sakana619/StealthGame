#include "Map.h"
#include"MapObject.h"

#include<DxLib.h>
#include"MapData.h"
#include"MapObjectModelAssignor.h"
#include"../GameObjectManager.h"
#include"../Chara/Player.h"

Map::Map()
{
}

Map::~Map() = default;

void Map::Init()
{
	//ステージのデータを取得
	auto stageData = MapData::GetStageData();

	for (int z = 0; z < stageData.size(); z++) {
		for (int x = 0; x < stageData[z].size(); x++) {
			//生成するオブジェクトのタイプ
			MapData::ObjectType type = stageData[z][x];

			//マップオブジェクトの生成
			auto obj = std::make_unique<MapObject>(type);

			//初期化
			obj->Init();

			//サイズの調整
			float posX = x * 200;
			float posY = 0;
			float posZ = z * 200;
			//壁なら高さを変える
			if (type == MapData::ObjectType::Wall) {
				posY = 200;
			}
			//座標の設定
			obj->SetPosition(Vector3(posX, posY, posZ));
			//オブジェクトの追加
			m_pMapObjects.push_back(std::move(obj));

		}

	}

}

void Map::Draw()
{

	for (auto& object : m_pMapObjects) {
		object->Draw();
	}

}

void Map::End()
{

	for (auto& object : m_pMapObjects) {
		object->End();
	}
	//モデルの破棄
	MapObjectModelAssignor::GetInstance().DeleteModel();

}

void Map::CheckHitMap(GameObjectManager* pGameObjectMgr)
{

	//空ならリターン
	if (pGameObjectMgr->GetObjcts().empty())return;

	for (const auto& mapObj : m_pMapObjects) {

		for (const auto& mapCollision : mapObj->GetCollisionData()) {

			if (!mapCollision.shape)continue;

			//オブジェクトとマップの当たり判定を調べる
			for (const auto& obj : pGameObjectMgr->GetObjcts()) {

				for (const auto& objCollision : obj->GetCollisionData()) {

					if (!objCollision.shape)continue;

					//衝突の判定
					auto result = objCollision.shape->CheckCollision(*mapCollision.shape);
					//衝突していなかったら処理しない
					if (!result.isHit)continue;
					//衝突結果を渡す
					obj->ResolveCollision(result, objCollision, mapCollision, mapObj->GetCollisionTag());

				}

			}

		}

	}

}

bool Map::IsGoal(const Player* pPlayer)
{

	Vector3 goalPos = { 3000.0f,160.0f,5100.0f };

	if ((goalPos - pPlayer->GetPosition()).GetSqLength() > 500 * 500)return false;

	return true;

}
