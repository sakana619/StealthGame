#include "GameObjectManager.h"

#include"GameObject.h"

GameObjectManager::GameObjectManager()
{
}

GameObjectManager::~GameObjectManager()
{
}

void GameObjectManager::Update(float deltaTime)
{
	//すべてのオブジェクトの更新
	for (auto& obj : m_pObjects) {
		obj->Update(deltaTime);
	}

}

void GameObjectManager::Draw()
{
	//すべてのオブジェクトの描画
	for (auto& obj : m_pObjects) {
		obj->Draw();
	}

}

void GameObjectManager::End()
{
	//すべてのオブジェクトの終了
	for (auto& obj : m_pObjects) {
		obj->End();
	}

	m_pObjects.clear();

}

void GameObjectManager::CheckCollision()
{

	size_t objCount = m_pObjects.size();

	for (size_t i = 0; i < objCount; i++) {
		//調べるオブジェクトのA
		GameObject* objA = m_pObjects[i].get();
		//調べるオブジェクトのAのコリジョン
		const auto& collisionAData = objA->GetCollisionData();

		for (size_t j = i + 1; j < objCount; j++) {
			//調べるオブジェクトのB
			GameObject* objB = m_pObjects[j].get();
			//調べるオブジェクトのBのコリジョン
			const auto& collisionBData = objB->GetCollisionData();

			for (const auto& collisionA : collisionAData) {

				//Shapeがなければ処理しない
				if (!collisionA.shape)continue;

				for (const auto& collisionB : collisionBData) {
					//Shapeがなければ処理しない
					if (!collisionB.shape)continue;

					//衝突判定
					Collision::Result result = collisionA.shape->CheckCollision(*collisionB.shape);

					//当たっていなければ処理しない
					if (!result.isHit)continue;
					//衝突結果を渡す
					objA->ResolveCollision(result, collisionA, collisionB, objB->GetCollisionTag());

					//衝突結果を反転して渡す
					result.normal = -result.normal;
					objB->ResolveCollision(result, collisionB, collisionA, objA->GetCollisionTag());
					
				}

			}

		}

	}

}

void GameObjectManager::CheckAttackCollision()
{

	size_t objCount = m_pObjects.size();

	for (size_t i = 0; i < objCount; i++) {
		//攻撃者を取得
		GameObject* attacker = m_pObjects[i].get();
		//攻撃者の攻撃コリジョンを取得
		const auto& attackCollisionDatas = attacker->GetAttackCollision()->GetCollisionDatas();

		for (size_t j = i + 1; j < objCount; j++) {
			//ターゲットを取得
			GameObject* target = m_pObjects[j].get();
			//タグが同じなら処理しない
			if (attacker->GetCollisionTag() == target->GetCollisionTag())continue;
			//ターゲットのコリジョンを取得
			const auto& targetCollisionData = target->GetCollisionData();

			for (const auto& attackCollision : attackCollisionDatas) {
				//存在しなければ処理しない
				if (!attackCollision.GetIsExist())continue;

				for (const auto& targetCollision : targetCollisionData) {

					if (!targetCollision.shape)continue;

					Collision::Result result = targetCollision.shape->CheckCollision(*attackCollision.GetCollision());
					//当たっていなければ処理しない
					if (!result.isHit)continue;

					//ダメージを与える
					target->Damage(attackCollision.GetAttackInfo(), result.normal);

					printfDx("HIT\n");
					printfDx("HIT\n");
					printfDx("HIT\n");
					printfDx("HIT\n");
					printfDx("HIT\n");

				}

			}

		}

	}

}
