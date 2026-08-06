#include "GameObject.h"
#include"../World/Component/Transform.h"

#include<DxLib.h>
#include<cassert>

GameObject::GameObject():
	m_transform(),
	m_modelHandle()
{
}

void GameObject::Draw()
{

	MV1SetPosition(m_modelHandle, m_transform.position.ToVECTOR());
	MV1SetRotationXYZ(m_modelHandle, m_transform.rotation.ToVECTOR());
	MV1DrawModel(m_modelHandle);

}

void GameObject::End()
{
	MV1DeleteModel(m_modelHandle);
}

void GameObject::DebugDraw()
{
}

void GameObject::AddCollision(std::unique_ptr<Collision::Shape> shape, CollisionType type)
{

	assert(shape && "GameObject::AddCollision : shape null");

	m_collisions.push_back({ std::move(shape),type });

}

void GameObject::SetPosition(const Vector3& position)
{
	m_transform.position = position;
	for (auto& collision : m_collisions) {
		collision.shape->SetCenterPos(m_transform.position);
	}
}
