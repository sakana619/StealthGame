#include "Collision.h"
#include"../Utility/Vector3.h"

#include<DxLib.h>
#include"CollisionJudge.h"
#include"../../Utility/MyMath.h"

Collision::Result Collision::Shape::CheckCollision(const Shape& other) const
{
	return CollisionJudge::CheckCollision(*this, other);
}

void Collision::AABB::DrawCollisionShape(int color)
{

	//自分の端の座標
	Vector3 minPos = m_centerPos - m_halfSize;
	Vector3 maxPos = m_centerPos + m_halfSize;

	VECTOR vartex[8];

	vartex[0] = minPos.ToVECTOR();
	vartex[1] = { maxPos.x,minPos.y,minPos.z };
	vartex[2] = { maxPos.x,minPos.y,maxPos.z };
	vartex[3] = { minPos.x,minPos.y,maxPos.z };

	vartex[4] = { minPos.x,maxPos.y,minPos.z };
	vartex[5] = { maxPos.x,maxPos.y,minPos.z };
	vartex[6] = maxPos.ToVECTOR();
	vartex[7] = { minPos.x,maxPos.y,maxPos.z };

	DrawLine3D(vartex[0], vartex[1], color);
	DrawLine3D(vartex[1], vartex[2], color);
	DrawLine3D(vartex[2], vartex[3], color);
	DrawLine3D(vartex[3], vartex[0], color);

	DrawLine3D(vartex[4], vartex[5], color);
	DrawLine3D(vartex[5], vartex[6], color);
	DrawLine3D(vartex[6], vartex[7], color);
	DrawLine3D(vartex[7], vartex[4], color);

	DrawLine3D(vartex[0], vartex[4], color);
	DrawLine3D(vartex[1], vartex[5], color);
	DrawLine3D(vartex[2], vartex[6], color);
	DrawLine3D(vartex[3], vartex[7], color);

}

void Collision::Sphere::DrawCollisionShape(int color)
{
	DrawSphere3D(m_centerPos.ToVECTOR(), m_radius, 5, color, color, false);
}
