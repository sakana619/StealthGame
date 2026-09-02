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
	const char* const kDataPath = ".\\Data\\Enemy\\EnemyPatrolPos.csv";

}

EnemyManager::EnemyManager():
	m_pEnemies()
{
}

void EnemyManager::Init(GameObjectManager* gameObjectMgr)
{

	//データの取得
	std::vector<EnemyData> datas = DataLoader::LoadMasterData<EnemyData>(kDataPath);

	std::vector<AttackInfo> attackInfo = DataLoader::LoadMasterData<AttackInfo>(".\\Data\\AttackInfo.csv");

	//敵の数を取得 IDは0も含まれるので + 1
	int enemyCount = datas.back().ID + 1;

	std::vector<std::vector<Vector3>>patrolPos;
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
		if (i != 0)return;
		EnemyBase* newEnemy = gameObjectMgr->CreateObject<EnemyBee>();
		newEnemy->Init();
		newEnemy->SetPosition(patrolPos[i][0]);
		//巡回座標を設定
		newEnemy->SetPatrolPos(patrolPos[i]);
		//攻撃情報を追加
		newEnemy->GetAttackCollision()->AddCollision<Collision::AABB>(attackInfo[0], Collision::AABB(Vector3::Zero, Vector3(100, 100, 100)));

		m_pEnemies.push_back(std::move(newEnemy));

	}

}

void EnemyManager::End()
{

	for (auto& enemy : m_pEnemies) {
		enemy->End();
	}

}

EnemyBase* EnemyManager::GetNearestEnemy(const Vector3& position)
{

	if (m_pEnemies.empty())return nullptr;

	EnemyBase* nearestEnemy = m_pEnemies[0];
	float nearest = (position - nearestEnemy->GetPosition()).GetSqLength();

	//全ての敵を調べる
	for (auto& enemy : m_pEnemies) {
		if (!enemy->IsActive() || enemy->IsDead())continue;
		Vector3 enemyPos = enemy->GetPosition();
		//距離を求める
		float range = (position - enemyPos).GetSqLength();

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
