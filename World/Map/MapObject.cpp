#include "MapObject.h"
#include"../GameObject.h"
#include"MapData.h"

#include<DxLib.h>
#include"MapObjectModelAssignor.h"

MapObject::MapObject(MapData::ObjectType type)
{
	//モデルの取得
	m_modelHandle = MapObjectModelAssignor::GetInstance().GetModel(type);

	//コリジョンタグの設定
	if (type == MapData::ObjectType::Floor) {
		m_collisionTag = CollisionTag::Floor;
	}
	else if (type == MapData::ObjectType::Wall) {
		m_collisionTag = CollisionTag::Wall;
	}

}

void MapObject::Init()
{

	//m_collisions.emplace_back(std::make_unique<Collision::AABB>(Vector3::Zero, Vector3(200, 200, 200)), CollisionType::Body);

	AddCollision(std::make_unique<Collision::AABB>(Vector3::Zero, Vector3(200, 200, 200)), CollisionType::Body);

	for (auto& collision : m_collisions) {
		collision.shape->SetCenterPos(m_transform.position);
	}

}

void MapObject::Update(float deltaTime)
{
}

void MapObject::Draw()
{
	//GameObject::Draw();

	for (auto& collision : m_collisions) {
		collision.shape->DrawCollisionShape(0x008800);
	}

}

void MapObject::ResolveCollision(const Collision::Result result, const CollisionData& myData, const CollisionData& otherData, CollisionTag other)
{
}

void MapObject::SetObjectType(MapData::ObjectType type)
{
	//モデルの取得
	m_modelHandle = MapObjectModelAssignor::GetInstance().GetModel(type);
}
