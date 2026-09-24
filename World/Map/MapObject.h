#pragma once
#include"../GameObject.h"

namespace MapData {
	enum class ObjectType;
}

class MapObject :public GameObject
{

public:

	MapObject(MapData::ObjectType type);
	~MapObject()override = default;

	void Init()override;
	void Update(float deltaTime)override;
	void Draw()override;

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

	void SetObjectType(MapData::ObjectType type);

	void SetScale(const Vector3& scale);

private:

	/// <summary>
	/// MapData::ObjectTypeをCollisionTagに変換
	/// </summary>
	/// <param name="type"></param>
	/// <returns></returns>
	CollisionTag ObjectTypeToCollisionTag(MapData::ObjectType type);

};
