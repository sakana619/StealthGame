#pragma once
#include"CharacterBase.h"

class Camera;
class EnemyManager;
class EnemyBase;
class UIBillboard;

class Player :public CharacterBase
{

public:

	Player();
	Player(Camera* pCamera);
	~Player()override = default;

	void Init()override;
	void Update(float deltaTime)override;
	void Draw()override;
	void End()override;

	/// <summary>
	/// 衝突結果の解決を行う
	/// </summary>
	/// <param name="result"></param>
	/// <param name="myData"></param>
	/// <param name="otherData"></param>
	/// <param name="other"></param>
	void ResolveCollision(
		const Collision::Result result,
		const CollisionData& myData,
		const CollisionData& otherData,
		CollisionTag other)override;

	void Damage(const AttackInfo& attackInfo, const Vector3& normal)override;

	void SetEnemyManager(EnemyManager* pEnemyManager);

	void SetCanAttackUI(UIBillboard* pUIBillboard) { m_pCanAttackUI = pUIBillboard; }

private:

	/// <summary>
	/// アニメーションの初期化
	/// </summary>
	void InitAnimation();

	Vector3 GetInputVectorRotedByCamera();

	void UpdateAnimation(float deltaTime);

	void Move();

	/// <summary>
	/// 攻撃可能な敵を取得する (一番近い敵)
	/// </summary>
	/// <returns>見つからなかったらnullptr</returns>
	EnemyBase* SearchCanAttackEnemy();

	void Dodge();

private:

	enum class State {

		Idle,
		Run,
		Jump,
		Attack,
		Dead,

	};

	State m_state;

	bool m_isDodging;

	Camera* m_pCamera;

	EnemyManager* m_pEnemyManager;

	UIBillboard* m_pCanAttackUI;

};
