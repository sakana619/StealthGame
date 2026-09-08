#include "EnemyManager.h"
#include<memory>
#include<vector>
#include"../Enemy/EnemyBase.h"
#include"../Enemy/EnemyBee.h"
#include"../../../Utility/Vector3.h"

#include<DxLib.h>
#include<cassert>
#include"../../GameObjectManager.h"
#include"../Utility/Loader/DataLoader.h"
#include"EnemyData.h"

namespace {

	//敵のデータのファイルパス
	const char* const kPatrolDataPath = ".\\Data\\Enemy\\EnemyPatrolPos.csv";
	//攻撃のデータのファイルパス
	const char* const kAttackInfoDataPath = ".\\Data\\AttackInfo.csv";

}

EnemyManager::EnemyManager():
	m_pEnemies()
{
}

void EnemyManager::Init(GameObjectManager* gameObjectMgr)
{

	//データの取得
	std::vector<EnemyData> datas = DataLoader::LoadMasterData<EnemyData>(kPatrolDataPath);
	AttackInfo attackInfo = DataLoader::LoadMasterData<AttackInfo>(kAttackInfoDataPath)[0];

	//敵の数を取得 IDは0も含まれるので + 1
	int enemyCount = datas.back().ID + 1;
	//メモリの確保
	m_pEnemies.reserve(enemyCount);

	//一時保管変数
	std::vector<std::vector<Vector3>>patrolPos;
	//要素の確保
	patrolPos.reserve(enemyCount);
	patrolPos.resize(enemyCount);

	for (int i = 0; i < datas.size(); i++) {

		for (int j = 0; j < patrolPos.size(); j++) {
			//IDと一致していなければ処理をしない
			if (j != datas[i].ID)continue;
			//巡回座標に追加
			patrolPos[j].emplace_back(datas[i].patrolPos);

		}

	}

	for (int i = 0; i < enemyCount; i++) {

		//GameObjectManagerに追加
		EnemyBase* newEnemy = gameObjectMgr->CreateObject<EnemyBee>();
		newEnemy->Init();
		//最初の巡回の座標に設定
		newEnemy->SetPosition(patrolPos[i][0]);
		//巡回座標を設定
		newEnemy->SetPatrolPos(patrolPos[i]);
		//攻撃情報を追加
		newEnemy->GetAttackCollision()->AddCollision<Collision::AABB>(attackInfo, Collision::AABB(Vector3::Zero, Vector3(100, 100, 100)));
		//配列に追加
		m_pEnemies.push_back(std::move(newEnemy));

	}

}

void EnemyManager::End()
{

	for (auto& enemy : m_pEnemies) {
		if (!enemy)continue;
		enemy->End();
	}

}

EnemyBase* EnemyManager::GetNearestEnemy(const Vector3& position)
{

	if (m_pEnemies.empty())return nullptr;

	EnemyBase* nearestEnemy = nullptr;
	//最初に大きな値を入れる
	float nearest = 16777216;

	//全ての敵を調べる
	for (auto& enemy : m_pEnemies) {
		if (!enemy->IsActive() || enemy->IsDead())continue;
		//距離を求める
		float range = (position - enemy->GetPosition()).GetSqLength();

		//nearestよりrangeの方が大きいならスルー
		if (nearest < range)continue;
		//結果を更新
		nearest = range;
		nearestEnemy = enemy;

	}

	return nearestEnemy;

}

void EnemyManager::SetTargetPos(const Vector3* targetPos)
{

	assert(targetPos && "EnemyManager::SetTargetPos : nullptr");

	for (auto& enemy : m_pEnemies) {
		enemy->SetTargetPos(targetPos);
	}

}
