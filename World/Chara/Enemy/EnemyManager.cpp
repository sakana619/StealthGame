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

	constexpr int kEnemyMaxNum = 1;

}

EnemyManager::EnemyManager():
	m_pEnemies()
{
}

void EnemyManager::Init(GameObjectManager* gameObjectMgr)
{

	const int posX = 500;
	//データの取得
	std::vector<EnemyData> datas = DataLoader::LoadMasterData<EnemyData>(".\\Data\\Enemy\\EnemyPatrolPos.csv");

	//敵の数を取得 IDは0も含まれるので + 1
	int enemyCount = datas[datas.size() - 1].ID + 1;


	for (int i = 0; i < enemyCount; i++) {

		auto newEnemy = gameObjectMgr->CreateObject<EnemyBee>();
		newEnemy->Init();
		Vector3 pos = Vector3(posX * (i + 1), 0, 0);
		//newEnemy->SetPosition(pos);
		newEnemy->SetPosition(Vector3(1000, 100, 100));

		m_pEnemies.push_back(std::move(newEnemy));

	}

}

void EnemyManager::Update(float deltaTime)
{

	for (const auto& enemy : m_pEnemies) {
		if (!enemy->IsActive())continue;
		enemy->Update(deltaTime);
	}

}

void EnemyManager::Draw()
{

	for (auto& enemy : m_pEnemies) {
		if (!enemy->IsActive())continue;
		enemy->Draw();
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
