#include "CharacterBase.h"
#include"../GameObject.h"
#include<memory>
#include<vector>
#include"Animation.h"
#include"AnimationController.h"
#include"../Component/AttackCollision.h"

CharacterBase::CharacterBase():
	m_anim(nullptr),
	m_animData(),
	m_fallSpeed(0),
	m_hp(0),
	m_isDead(false)
{
}

void CharacterBase::Draw()
{
	GameObject::Draw();
}

void CharacterBase::End()
{
	GameObject::End();
}

void CharacterBase::Damage(const AttackInfo& attackInfo, const Vector3& normal)
{
	//ノックバック方向の決定
	m_unresolveKnockback = normal;
	//ノックバックを加算
	m_unresolveKnockback *= attackInfo.knockBack;
	//HPを減らす
	m_hp -= attackInfo.damage;
}
