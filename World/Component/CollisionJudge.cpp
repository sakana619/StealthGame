#include "CollisionJudge.h"
#include"Collision.h"

#include<DxLib.h>
#include"../../Utility/MyMath.h"

using namespace Collision;

Result CheckAABB(const Collision::Shape& AABB, const Collision::Shape& other);
Result CheckToAABBByAABB(const Collision::Shape& AABB, const Collision::Shape& other);
Result CheckToSphereByAABB(const Collision::Shape& AABB, const Collision::Shape& sphere);

Result CheckSphere(const Collision::Shape& sphere, const Collision::Shape& other);
Result CheckToAABBBySphere(const Collision::Shape& sphere, const Collision::Shape& AABB);
Result CheckToSphereBySphere(const Collision::Shape& sphere, const Collision::Shape& other);

Collision::Result CollisionJudge::CheckCollision(const Collision::Shape& a, const Collision::Shape& b)
{

	switch (a.GetType())
	{
	case Type::AABB:
		return CheckAABB(a, b);
		break;
	case Type::Sphere:
		return CheckSphere(a, b);
		break;

	}

	Result result;
	return result;

}

Result CheckAABB(const Collision::Shape& AABB, const Collision::Shape& other) {

	switch (other.GetType())
	{
	case Type::AABB:
		return CheckToAABBByAABB(AABB, other);
		break;

	case Type::Sphere:
		return CheckToSphereByAABB(AABB, other);
		break;

	}

	Result result;
	return result;

}

Result CheckToAABBByAABB(const Collision::Shape& AABB, const Collision::Shape& other) {

	Result result;

	//AABBの中心座標を取得
	Vector3 centerPos = AABB.GetCenterPos();
	//AABBの半分のサイズを取得
	Vector3 halfSize = AABB.GetHalfSize();

	//AABB端の座標
	Vector3 minPos = centerPos - halfSize;
	Vector3 maxPos = centerPos + halfSize;

	Vector3 otherCenterPos = other.GetCenterPos();
	Vector3 otherHalfSize = other.GetHalfSize();

	//チェックする当たり判定の端の座標
	Vector3 otherMinPos = otherCenterPos - otherHalfSize;
	Vector3 otherMaxPos = otherCenterPos + otherHalfSize;

	//衝突判定
	if (minPos.x > otherMaxPos.x || maxPos.x < otherMinPos.x)return result;
	if (minPos.y > otherMaxPos.y || maxPos.y < otherMinPos.y)return result;
	if (minPos.z > otherMaxPos.z || maxPos.z < otherMinPos.z)return result;

	//ここまで来たら当たっている
	result.isHit = true;

	//各軸の重なり具合を調べる
	float overlapX = MyMath::Min(maxPos.x, otherMaxPos.x) - MyMath::Max(minPos.x, otherMinPos.x);
	float overlapY = MyMath::Min(maxPos.y, otherMaxPos.y) - MyMath::Max(minPos.y, otherMinPos.y);
	float overlapZ = MyMath::Min(maxPos.z, otherMaxPos.z) - MyMath::Max(minPos.z, otherMinPos.z);

	//衝突の法線
	Vector3 dir = centerPos - otherCenterPos;

	//各軸のめり込み量を調べて最小の軸に合わせる
	//X軸が一番小さければ
	if (overlapX <= overlapY && overlapX <= overlapZ) {
		result.penetration = overlapX;
		result.normal = dir.x < 0 ? -Vector3::XAxis : Vector3::XAxis;
	}
	//Y軸が一番小さければ
	else if (overlapY <= overlapZ) {
		result.penetration = overlapY;
		result.normal = dir.y < 0 ? -Vector3::YAxis : Vector3::YAxis;
	}
	//Z軸が一番小さければ
	else {
		result.penetration = overlapZ;
		result.normal = dir.z < 0 ? -Vector3::ZAxis : Vector3::ZAxis;
	}

	return result;

}

Result CheckToSphereByAABB(const Collision::Shape& AABB, const Collision::Shape& sphere) {

	Result result;

	//中心座標を取得
	Vector3 centerPos = AABB.GetCenterPos();
	//半分のサイズを取得
	Vector3 halfSize = AABB.GetHalfSize();

	//AABBの端の座標
	Vector3 minPos = centerPos - halfSize;
	Vector3 maxPos = centerPos + halfSize;

	//球の座標
	Vector3 spherePos = sphere.GetCenterPos();

	//衝突判定
	Vector3 closest = Vector3::Zero;
	closest.x = MyMath::Max(minPos.x, MyMath::Min(spherePos.x, maxPos.x));
	closest.y = MyMath::Max(minPos.y, MyMath::Min(spherePos.y, maxPos.y));
	closest.z = MyMath::Max(minPos.z, MyMath::Min(spherePos.z, maxPos.z));

	//最近接点との距離の2乗
	float distanceSq = (closest - spherePos).GetSqLength();
	//球の半径を取得
	float sphereRadius = sphere.GetHalfSize().x;
	//距離が半径より大きいなら当たっていない
	if (distanceSq > sphereRadius * sphereRadius)return result;

	result.isHit = true;




	return result;

}

Result CheckSphere(const Collision::Shape& sphere, const Collision::Shape& other) {

	switch (other.GetType())
	{
	case Type::AABB:
		return CheckToAABBBySphere(sphere, other);
		break;

	case Type::Sphere:
		return CheckToSphereBySphere(sphere, other);
		break;

	}

	Result result;
	return result;

}

Result CheckToAABBBySphere(const Collision::Shape& sphere, const Collision::Shape& AABB) {

	Result result;

	//中心座標を取得
	Vector3 centerPos = AABB.GetCenterPos();
	//半分のサイズを取得
	Vector3 halfSize = AABB.GetHalfSize();

	//AABBの端の座標
	Vector3 minPos = centerPos - halfSize;
	Vector3 maxPos = centerPos + halfSize;

	//球の座標
	Vector3 spherePos = sphere.GetCenterPos();

	//衝突判定に使う最近接点を取得
	Vector3 closest = Vector3::Zero;
	closest.x = MyMath::Max(minPos.x, MyMath::Min(spherePos.x, maxPos.x));
	closest.y = MyMath::Max(minPos.y, MyMath::Min(spherePos.y, maxPos.y));
	closest.z = MyMath::Max(minPos.z, MyMath::Min(spherePos.z, maxPos.z));

	//DrawSphere3D(closest.ToVECTOR(), 10.0f, 32, 0x000000, 0x000000, TRUE);

	//printfDx("closest.x : %f\n", closest.x);
	//printfDx("closest.y : %f\n", closest.y);
	//printfDx("closest.z : %f\n", closest.z);

	//距離の2乗を取得
	float distanceSq = (closest - spherePos).GetSqLength();
	//球の半径を取得
	float sphereRadius = sphere.GetHalfSize().x;
	//球の半径の二乗と距離の2乗を比較
	if (distanceSq > sphereRadius * sphereRadius)return result;
	//ここまで来たら当たっている
	result.isHit = true;

	//



	DrawSphere3D(closest.ToVECTOR(), 10.0f, 32, 0xff0000, 0xff0000, TRUE);


	return result;

}


Result CheckToSphereBySphere(const Collision::Shape& sphere, const Collision::Shape& other) {

	Result result;

	//距離
	Vector3 dif = sphere.GetCenterPos() - other.GetCenterPos();
	//半径の合計
	float sumRadius = sphere.GetHalfSize().x + other.GetHalfSize().x;
	//距離の差が半径の合計より大きいなら当たっていない
	if (dif.GetSqLength() > sumRadius * sumRadius)return result;

	result.isHit = true;

	return result;

}
