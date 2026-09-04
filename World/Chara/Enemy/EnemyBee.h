#pragma once
#include"EnemyBase.h"
#include<vector>
#include"../Utility/Vector3.h"

class EnemyBee :public EnemyBase
{

public:

	EnemyBee();
	~EnemyBee()override = default;

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

	void Death()override;

private:

	void InitAnimation();

	void UpdatePatrol(float deltaTime)override;

	void UpdateCaution(float deltaTime)override;

	void UpdateCombat(float deltaTime)override;

	void CheckBehind();

	void UpdateForward(Vector3 moveDirection,float forward);

	Vector3 UpdateView();

	/// <summary>
	/// 視界の描画
	/// </summary>
	void DrawView();

private:

	/// <summary>
	/// 発見時の画像ハンドル
	/// </summary>
	static int m_discoveryImageHandle;

};
