#include "EnemyBase.h"
#include"../../GameObject.h"

#include<math.h>
#include"../Player.h"
#include"../../../Utility/Vector3.h"

EnemyBase::EnemyBase() :
	m_isActive(true),
	m_state(EnemyBase::State::Patrol),
	m_moveSpeed(0),
	m_visibleDistance(0),
	m_visibleRadAngle(0),
	m_nextPatrolIndex(0),
	m_isBack(false),
	m_pTargetPos(nullptr)
{
	//タグの設定
	m_collisionTag = CollisionTag::Enemy;
}

void EnemyBase::Draw()
{
	GameObject::Draw();
}

void EnemyBase::End()
{
	GameObject::End();
}

void EnemyBase::Damage(const AttackInfo& attackInfo, const Vector3& normal)
{
	//damageが0以下ならリターン
	if (attackInfo.damage < 0)return;
	//規定のダメージ処理
	CharacterBase::Damage(attackInfo, normal);
	//HPが0以下になったら
	if (m_hp < 0) {
		//死亡処理
		m_hp = 0;
		m_isDead = true;
		Death();
	}

}

bool EnemyBase::IsArrivedNextPos(const Vector3& nextPos, float moveAmount)
{
	return (nextPos - m_transform.position).GetSqLength() < moveAmount * moveAmount;
}

bool EnemyBase::CheckInViewRange(float rangeSq)
{
	//視界の距離の外にいたらfalse
	if (rangeSq > m_visibleDistance * m_visibleDistance)return false;
	//視界の距離の中なのでtrue
	return true;
}

bool EnemyBase::CheckInViewRadAngle()
{

	Vector3 targetPos = *m_pTargetPos;
	Vector3 myPos = m_transform.position;

	//Y座標を考慮しない
	targetPos.y = 0;
	myPos.y = 0;

	//ターゲットへの方向ベクトルを求める
	Vector3 toTarget = targetPos - myPos;
	toTarget = toTarget.GetNormalize();
	//ターゲットの方向と自身の正面方向から角度の一致度を求める
	float dot = Vector3::Dot(toTarget, m_forward);

	//視界の角度の外ならfalse
	if (dot < cosf(m_visibleRadAngle))return false;
	//視界の角度のなのでtrue
	return true;

}
