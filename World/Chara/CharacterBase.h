#pragma once
#include"../GameObject.h"

#include<memory>
#include<vector>
#include"Animation.h"
#include"AnimationController.h"
#include"../Component/AttackCollision.h"

class CharacterBase :public GameObject
{

public:

	CharacterBase();
	~CharacterBase()override = default;

	virtual void Init()override = 0;
	virtual void Update(float deltaTime)override = 0;
	virtual void Draw()override;
	virtual void End()override;

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

	/// <summary>
	/// ダメージ処理
	/// </summary>
	/// <param name="attackInfo">攻撃情報</param>
	/// <param name="normal">攻撃のヒットした法線</param>
	virtual void Damage(const AttackInfo& attackInfo, const Vector3& normal)override;

	bool IsDead()const { return m_isDead; }

protected:
	/// <summary>
	/// アニメーションのコントローラー
	/// </summary>
	std::unique_ptr<AnimationController> m_anim;
	/// <summary>
	/// 再生するアニメーションのデータ
	/// </summary>
	std::vector<Animation::AnimationData>m_animData;
	/// <summary>
	/// 落下速度
	/// </summary>
	float m_fallSpeed;

	/// <summary>
	/// ノックバック量
	/// </summary>
	Vector3 m_unresolveKnockback;

	/// <summary>
	/// 体力
	/// </summary>
	int m_hp;

	/// <summary>
	/// 死亡しているか
	/// </summary>
	bool m_isDead;

};
