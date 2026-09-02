#pragma once
#include"../CharacterBase.h"

#include<vector>
#include"../../../Utility/Vector3.h"
#include"../Animation.h"

class EnemyBase :public CharacterBase
{

public:

	EnemyBase();
	virtual ~EnemyBase()override = default;

	virtual void Init()override = 0;

	virtual void Update(float deltaTime)override = 0;

	virtual void Draw()override;

	virtual void End()override;

	void Damage(const AttackInfo& attackInfo, const Vector3& normal)override;

	/// <summary>
	/// 衝突結果の解決を行う
	/// </summary>
	/// <param name="result"></param>
	/// <param name="myData"></param>
	/// <param name="otherData"></param>
	/// <param name="other"></param>
	virtual void ResolveCollision(
		const Collision::Result result,
		const CollisionData& myData,
		const CollisionData& otherData,
		CollisionTag other)override = 0;

	virtual void Death() {}

	bool IsActive()const { return m_isActive; }

	/// <summary>
	/// 正面方向のベクトルを取得
	/// </summary>
	/// <returns></returns>
	const Vector3& GetForward()const { return m_forward; }

	void SetIsActive(bool active) { m_isActive = active; }

	/// <summary>
	/// 巡回の地点の座標を設定する
	/// </summary>
	/// <param name="patrolPosition"></param>
	void SetPatrolPos(const std::vector<Vector3>& patrolPosition) { m_patrolPositions = patrolPosition; }

	void SetTargetPos(const Vector3* targetPos) { m_pTargetPos = targetPos; }

protected:

	virtual void UpdatePatrol(float deltaTime) = 0;

	virtual void UpdateCaution(float deltaTime) = 0;

	virtual void UpdateCombat(float deltaTime) = 0;

	/// <summary>
	/// 次の座標に着いたか判定
	/// </summary>
	/// <param name="nextPos"></param>
	/// <returns></returns>
	bool IsArrivedNextPos(const Vector3& nextPos, float moveAmount);

	/// <summary>
	/// 見える距離か判定
	/// </summary>
	/// <param name="rangeSq"></param>
	/// <returns></returns>
	bool CheckInViewRange(float rangeSq);

	/// <summary>
	/// 見える角度か判定
	/// </summary>
	/// <returns></returns>
	bool CheckInViewRadAngle();

protected:

	bool m_isActive;

	/// <summary>
	/// 敵キャラクターの状態
	/// </summary>
	enum class State {
		Patrol,
		Caution,
		Combat,

	};

	/// <summary>
	/// 状態
	/// </summary>
	State m_state;

	/// <summary>
	/// 前方向のベクトルを取得する
	/// </summary>
	Vector3 m_forward;

	/// <summary>
	/// 移動速度
	/// </summary>
	float m_moveSpeed;

	/// <summary>
	/// 見える距離
	/// </summary>
	float m_visibleDistance;

	/// <summary>
	/// 見える角度
	/// </summary>
	float m_visibleRadAngle;

	/// <summary>
	/// 巡回する座標
	/// </summary>
	std::vector<Vector3> m_patrolPositions;

	size_t m_nextPatrolIndex;

	bool m_isBack;

	const Vector3* m_pTargetPos;

};
