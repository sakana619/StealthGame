#include "MapObject.h"
#include"../GameObject.h"
#include"MapData.h"

#include<DxLib.h>
#include"MapObjectModelAssignor.h"

namespace {
	//コリジョンのオフセット
	constexpr Vector3 kCollisionOffSet = { 69.0f, 50.0f, 79.0f };
	//コリジョンのサイズ
	constexpr Vector3 kCollisionSize = { 200.0f, 200.0f, 200.0f };

}

MapObject::MapObject(MapData::ObjectType type)
{
	//モデルの取得
	m_modelHandle = MapObjectModelAssignor::GetInstance().GetModel(type);

	//コリジョンタグの設定
	m_collisionTag = ObjectTypeToCollisionTag(type);

}

void MapObject::Init()
{

	AddCollision(std::make_unique<Collision::AABB>(kCollisionOffSet, kCollisionSize), CollisionType::Body);

	for (auto& collision : m_collisions) {
		collision.shape->SetCenterPos(m_transform.position);
	}

}

void MapObject::Update(float deltaTime)
{
}

void MapObject::Draw()
{
	GameObject::Draw();

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

void MapObject::SetScale(const Vector3& scale)
{
	//スケールの変更
	MV1SetScale(m_modelHandle, scale.ToVECTOR());
}

GameObject::CollisionTag MapObject::ObjectTypeToCollisionTag(MapData::ObjectType type)
{

	CollisionTag tag = CollisionTag::Invalid;

	//タグの変更
	if (type == MapData::ObjectType::Floor) {
		tag = CollisionTag::Floor;
	}
	else if (type == MapData::ObjectType::Wall) {
		tag = CollisionTag::Wall;
	}
	else if (type == MapData::ObjectType::Goal) {
		tag = CollisionTag::Goal;
	}

	return tag;

}
