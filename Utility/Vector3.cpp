#include "Vector3.h"

#include <DxLib.h>
#include <cassert>
#include <cmath>
#include"../Utility/MyMath.h"

const Vector3 Vector3::Zero{ 0.0f,0.0f,0.0f };
const Vector3 Vector3::XAxis{ 1.0f,0.0f,0.0f };
const Vector3 Vector3::YAxis{ 0.0f,1.0f,0.0f };
const Vector3 Vector3::ZAxis{ 0.0f,0.0f,1.0f };

float Vector3::Dot(const Vector3& a, const Vector3& b)
{

	float dot = a.x * b.x + a.y * b.y + a.z * b.z;

	return dot;

}

const Vector3& Vector3::Lerp(const Vector3& a, const Vector3& b, float t)
{
	t = MyMath::Clamp(t, 0.0f, 1.0f);
	Vector3 result = Vector3::Zero;
	result.x = a.x + (b.x - a.x) * t;
	result.y = a.y + (b.y - a.y) * t;
	result.z = a.z + (b.z - a.z) * t;
	return result;
}

Vector3 Vector3::operator-() const
{
	return Vector3( -x, -y, -z);
}

Vector3 Vector3::operator+(const Vector3& vec) const
{
	return Vector3( x + vec.x, y + vec.y, z + vec.z);
}

Vector3 Vector3::operator-(const Vector3& vec) const
{
	return Vector3( x - vec.x, y - vec.y, z - vec.z);
}

Vector3 Vector3::operator*(float scale) const
{
	return Vector3(x * scale, y * scale, z * scale);
}

Vector3 Vector3::operator/(float scale) const
{

	if (scale == 0) {
		assert(0 && "Vector3:0œŽZ");
		return Vector3();
	}

	return Vector3(x / scale, y / scale, z / scale);
}

Vector3& Vector3::operator+=(const Vector3& vec)
{

	x += vec.x;
	y += vec.y;
	z += vec.z;

	return *this;
}

Vector3& Vector3::operator-=(const Vector3& vec)
{

	x -= vec.x;
	y -= vec.y;
	z -= vec.z;
	return *this;
}

Vector3& Vector3::operator*=(float scale)
{

	x *= scale;
	y *= scale;
	z *= scale;
	return *this;
}

Vector3& Vector3::operator/=(float scale)
{

	if (scale == 0) {
		assert(0 && "Vector3:0œŽZ");
	}

	x /= scale;
	y /= scale;
	z /= scale;
	return *this;
}

bool Vector3::operator==(const Vector3& vec) const
{
	return x == vec.x && y == vec.y && z == vec.z;
}

bool Vector3::operator!=(const Vector3& vec) const
{
	return x != vec.x || y != vec.y || z != vec.z;
}

float Vector3::GetLength() const
{
	float length = sqrt(x * x + y * y + z * z);
	return length;
}

float Vector3::GetSqLength() const
{
	float length = x * x + y * y + z * z;
	return length;
}

Vector3 Vector3::GetNormalize() const
{

	Vector3 res;

	// ƒ[ƒƒxƒNƒgƒ‹‚©ƒ`ƒFƒbƒN
	float size = this->GetSqLength();
	if (size == 0.0f)
	{
		assert(0 && "Vector3:0œŽZ");
		return res;
	}

	size = this->GetLength();

	res.x = x / size;
	res.y = y / size;
	res.z = z / size;

	return res;
}

VECTOR Vector3::ToVECTOR() const
{
	VECTOR vec = VGet(0.0f, 0.0f, 0.0f);

	vec.x = x;
	vec.y = y;
	vec.z = z;

	return vec;
}
