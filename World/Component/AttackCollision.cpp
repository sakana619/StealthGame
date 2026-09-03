#include "AttackCollision.h"
#include"Collision.h"
#include"../../Utility/Vector3.h"
#include<memory>
#include<vector>

#include<DxLib.h>
#include<cassert>
#include"../../System/Time.h"
#include"../../Utility/MyMath.h"

AttackCollision::AttackData::AttackData(const AttackInfo& attackInfo, std::unique_ptr<Collision::Shape> collision) :
	m_info(attackInfo),
	m_durationSec(0.0f),
	m_elapsedSec(0.0f),
	m_isExist(false),
	m_collision(std::move(collision))
{
}

void AttackCollision::AttackData::Update(float deltaTime)
{
	if (!m_isExist || !m_collision)return;

	//経過時間を加算
	m_elapsedSec += deltaTime;

	//持続時間内なら処理しない
	if (m_elapsedSec <= m_durationSec)return;
	//コリジョンを削除
	DespawnCollision();

}

void AttackCollision::AttackData::DrawCollision()
{
	if (!m_isExist || !m_collision)return;

	//コリジョンの色 残り時間が減るほど赤くなる
	float redValue = MyMath::Rate(m_elapsedSec, m_durationSec);

	m_collision->DrawCollisionShape(GetColor(255 * redValue, 0, 0));
}

void AttackCollision::AttackData::SpawnCollision(float durationSec, const Vector3& spawnPos)
{
	//設定
	m_durationSec = durationSec;
	m_collision->SetCenterPos(spawnPos);
	//リセット
	m_elapsedSec = 0;
	m_isExist = true;

}

void AttackCollision::AttackData::DespawnCollision()
{
	m_isExist = false;
	m_elapsedSec = 0;
	m_durationSec = 0;
}

AttackCollision::AttackCollision()
{
}

void AttackCollision::Update()
{
	float deltaTime = Time::GetDeltaTime();
	//すべてのコリジョンを更新
	for (int i = 0; i < m_collisions.size(); i++) {
		m_collisions[i].Update(deltaTime);
	}

}

void AttackCollision::DrawCollision()
{
	//すべてのコリジョンを描画
	for (int i = 0; i < m_collisions.size(); i++) {
		m_collisions[i].DrawCollision();
	}

}

AttackCollision::AttackData& AttackCollision::GetCollisionData(int index)
{
	//範囲外チェック
	if (index < 0 || index >= m_collisions.size()) {
		assert(false && "AttackCollision::GetCollisionData index out of range");
		static AttackData empty;
		return empty;
	}

	return m_collisions[index];

}
