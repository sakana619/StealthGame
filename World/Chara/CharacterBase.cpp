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
	m_fallSpeed(0)
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
