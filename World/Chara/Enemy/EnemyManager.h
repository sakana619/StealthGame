#pragma once
#include<memory>
#include<vector>

class EnemyBase;

struct Vector3;
class GameObjectManager;

class EnemyManager
{

public:

	EnemyManager();
	~EnemyManager() = default;

	void Init(GameObjectManager* gameObjectMgr);
	void End();

	/// <summary>
	/// 引数の座標から一番近い敵を取得
	/// </summary>
	/// <param name="Position"></param>
	/// <returns>全ての敵が非アクティブならnullptrを返す</returns>
	EnemyBase* GetNearestEnemy(const Vector3& position);

	void SetTargetPos(const Vector3* targetPos);

private:

	/// <summary>
	/// 敵の配列
	/// </summary>
	std::vector<EnemyBase*> m_pEnemies;

};
