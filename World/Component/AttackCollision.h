#pragma once

#include"Collision.h"
#include"../../Utility/Vector3.h"
#include"AttackInfo.h"
#include<memory>
#include<vector>
#include<type_traits>

class AttackCollision
{

private:

	/// <summary>
	/// 攻撃のコリジョンデータ
	/// </summary>
	class AttackData {

	public:

		AttackData() = default;
		AttackData(const AttackInfo& attackInfo,std::unique_ptr<Collision::Shape> collision);
		~AttackData() = default;

		AttackData(AttackData&&)noexcept = default;
		AttackData& operator=(AttackData&&)noexcept = default;

		AttackData(const AttackData&) = delete;
		AttackData& operator=(const AttackData&) = delete;

		void Update(float deltaTime);
		void DrawCollision();

		/// <summary>
		/// 攻撃のコリジョンを出現させる
		/// </summary>
		/// <param name="durationSec">持続時間</param>
		/// <param name="spawnPos">出現位置</param>
		void SpawnCollision(float durationSec, const Vector3& spawnPos);

		/// <summary>
		/// 攻撃のコリジョンを消す
		/// </summary>
		void DespawnCollision();

		/// <summary>
		/// コリジョンの取得
		/// </summary>
		/// <returns></returns>
		const Collision::Shape* GetCollision()const { return m_collision.get(); }

		const AttackInfo& GetAttackInfo()const { return m_info; }

		/// <summary>
		/// 存在するか
		/// </summary>
		/// <returns></returns>
		bool GetIsExist()const { return m_isExist; }

	private:

		/// <summary>
		/// 攻撃の情報
		/// </summary>
		AttackInfo m_info;

		/// <summary>
		/// 持続時間
		/// </summary>
		float m_durationSec;

		/// <summary>
		/// 経過時間
		/// </summary>
		float m_elapsedSec;

		/// <summary>
		/// 存在するか
		/// </summary>
		bool m_isExist;

		/// <summary>
		/// 攻撃のコリジョン
		/// </summary>
		std::unique_ptr<Collision::Shape> m_collision;

	};

public:

	AttackCollision();
	~AttackCollision() { m_collisions.clear(); }

	void Update();
	void DrawCollision();

	/// <summary>
	/// 攻撃コリジョンを追加する
	/// </summary>
	/// <typeparam name="T"></typeparam>
	/// <typeparam name="...Args"></typeparam>
	/// <param name="...args"></param>
	template<class T, class ...Args>
	void AddCollision(const AttackInfo& attackInfo, Args && ...args);

	/// <summary>
	/// 登録したすべての攻撃コリジョンを取得する
	/// </summary>
	/// <returns></returns>
	std::vector<AttackData>& GetCollisionDatas() { return m_collisions; }

	/// <summary>
	/// 指定したコリジョン取得
	/// </summary>
	/// <param name="index"></param>
	/// <returns>範囲外を指定された場合空のDataを返す</returns>
	AttackData& GetCollisionData(int index);

private:

	/// <summary>
	/// 攻撃のコリジョン
	/// </summary>
	std::vector<AttackData>m_collisions;

};

template<class T, class ...Args>
inline void AttackCollision::AddCollision(const AttackInfo& attackInfo, Args && ...args)
{

	//コリジョンの基底クラスを継承しているか確認
	static_assert(std::is_base_of<Collision::Shape, T>::value, "");
	//コリジョンを追加する
	m_collisions.emplace_back(attackInfo, std::make_unique<T>(std::forward<Args>(args)...));

}
