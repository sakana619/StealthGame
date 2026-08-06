#pragma once

#include"../Utility/Vector3.h"

/// <summary>
/// 衝突判定関連のデータや処理
/// </summary>
namespace Collision {

	/// <summary>
	/// 衝突判定の形状のタイプ
	/// </summary>
	enum class Type {

		AABB,
		Sphere,

	};

	/// <summary>
	/// 衝突判定の結果
	/// </summary>
	struct Result {

		/// <summary>
		/// 衝突したか
		/// </summary>
		bool isHit = false;
		/// <summary>
		/// 衝突した法面
		/// </summary>
		Vector3 normal = Vector3::Zero;
		/// <summary>
		/// めり込み量
		/// </summary>
		float penetration = 0.0f;

	};

	/// <summary>
	/// 衝突判定の基底クラス
	/// </summary>
	class Shape {

	public:

		Shape() :m_centerPos(Vector3::Zero), m_offset(Vector3::Zero) {};
		Shape(const Vector3& offSet) :m_centerPos(Vector3::Zero), m_offset(offSet) {};
		virtual ~Shape() = default;

		Collision::Result CheckCollision(const Shape& other) const;

		const Vector3& GetCenterPos()const { return m_centerPos; }

		/// <summary>
		/// 当たり判定の半分のサイズを取得
		/// </summary>
		/// <returns></returns>
		virtual const Vector3& GetHalfSize()const = 0;

		/// <summary>
		/// 形状を取得
		/// </summary>
		/// <returns></returns>
		virtual Collision::Type GetType()const = 0;

		void SetCenterPos(const Vector3& position) { m_centerPos = position + m_offset; }

		/// <summary>
		/// オフセットを設定
		/// </summary>
		/// <param name="offset"></param>
		void SetOffset(const Vector3& offset) { m_offset = offset; }

		virtual void SetSize(const Vector3& size){}

		virtual void SetSize(float size){}

		virtual void DrawCollisionShape(int color = 0xffffff) = 0;

	protected:

		/// <summary>
		/// 中心の座標
		/// </summary>
		Vector3 m_centerPos;
		/// <summary>
		/// 当たり判定のオフセット
		/// </summary>
		Vector3 m_offset;

	};

	class AABB :public Shape {

	public:

		AABB(const Vector3& offset, const Vector3& size) :Shape(offset), m_halfSize(size * 0.5f) {};
		~AABB()override = default;

		void DrawCollisionShape(int color = 0xffffff)override;

		Type GetType()const override { return Type::AABB; }

		const Vector3& GetHalfSize()const override { return m_halfSize; }

		void SetSize(const Vector3& size)override { m_halfSize = size * 0.5f; }

	private:

		Vector3 m_halfSize;

	};

	class Sphere :public Shape {

	public:

		Sphere(const Vector3& offSet, float radius) :Shape(offSet), m_radius(radius) {};
		~Sphere()override = default;

		void DrawCollisionShape(int color = 0xffffff)override;

		Type GetType()const override { return Type::Sphere; }

		const Vector3& GetHalfSize()const override { return Vector3(m_radius, m_radius, m_radius); }

		void SetSize(float size)override { m_radius = size; }

	private:

		float m_radius;

	};

}
