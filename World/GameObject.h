#pragma once
#include"Component/Transform.h"
#include"Component/Collision.h"
#include"Component/AttackCollision.h"
#include<memory>

/// <summary>
/// 全オブジェクトが持つ機能を持ったクラス
/// </summary>
class GameObject
{

public:

	/// <summary>
	/// 衝突判定時に何と当たったか判定をするタグ
	/// </summary>
	enum class CollisionTag {
		Invalid = -1,
		Player,
		Enemy,
		Floor,
		Wall,
	};

	/// <summary>
	/// コリジョンのどれに当たったか
	/// </summary>
	enum class CollisionType {
		Body,
		Foot,
	};

	/// <summary>
	/// 当たり判定に必要なコリジョン情報
	/// </summary>
	struct CollisionData {
		std::unique_ptr<Collision::Shape> shape;
		CollisionType type;
	};

public:

	GameObject();
	virtual ~GameObject() = default;

	/// <summary>
	/// 初期化
	/// </summary>
	virtual void Init() = 0;

	/// <summary>
	/// 更新
	/// </summary>
	virtual void Update(float deltaTime) = 0;

	/// <summary>
	/// 描画
	/// </summary>
	virtual void Draw();

	/// <summary>
	/// 終了処理
	/// </summary>
	virtual void End();

	/// <summary>
	/// デバック描画
	/// </summary>
	virtual void DebugDraw();

	/// <summary>
	/// コリジョン衝突結果の解決
	/// </summary>
	/// <param name="result"></param>
	/// <param name="myData"></param>
	/// <param name="otherData"></param>
	/// <param name="other"></param>
	virtual void ResolveCollision(
		const Collision::Result result,
		const CollisionData& myData,
		const CollisionData& otherData,
		CollisionTag other) = 0;

	/// <summary>
	/// コリジョン追加
	/// </summary>
	/// <param name="shape"></param>
	/// <param name="type"></param>
	void AddCollision(std::unique_ptr<Collision::Shape> shape, CollisionType type);

	/// <summary>
	/// 座標を取得
	/// </summary>
	/// <returns></returns>
	const Vector3& GetPosition()const { return m_transform.position; }

	const std::vector<CollisionData>& GetCollisionData()const { return m_collisions; }

	AttackCollision* GetAttackCollision() { return m_pAttackCollision.get(); }

	/// <summary>
	/// コリジョンタグを取得
	/// </summary>
	/// <returns></returns>
	virtual CollisionTag GetCollisionTag()const { return m_collisionTag; }

	void SetPosition(const Vector3& position);

protected:

	Transform m_transform;

	int m_modelHandle;

	/// <summary>
	/// 自身のコリジョン
	/// </summary>
	std::vector<CollisionData>m_collisions;

	/// <summary>
	/// 攻撃コリジョン
	/// </summary>
	std::unique_ptr<AttackCollision>m_pAttackCollision;

	/// <summary>
	/// 衝突時の判定に使うタグの管理
	/// </summary>
	CollisionTag m_collisionTag;

};
