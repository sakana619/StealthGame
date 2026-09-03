#include "EnemyBee.h"
#include"EnemyBase.h"

#include<DxLib.h>
#include<math.h>
#include"../../../System/Time.h"

namespace {

	//蜂のファイルパス
	const char* const kModelPath = ".\\Resource\\chara\\Bee.mv1";

	constexpr Vector3 kInitPos{ -400.0f,0.0f,0.0f };

	constexpr Vector3 kInitScale{ 0.3f,0.3f,0.3f };

	constexpr Vector3 kCollisionOffSet{ 0.0f,20.0f,0.0f };
	constexpr Vector3 kCollisionSize{ 50.0f,50.0f,50.0f };

	// アニメーションの名前
	const char* const kAnimationName[] = {

		"MonsterArmature|Bite_Front",
		"MonsterArmature|Death",
		"MonsterArmature|Flying",
		"MonsterArmature|HitRecive"

	};

	constexpr Vector3 kMoveDirection = { 0.0f,0.0,1.0f };

	constexpr float kVisibleRange = 1000.0f;

	constexpr float kVisibleRadAngle = MyMath::DegToRad(30);

	constexpr float kMoveSpeed = 120.0f;

	constexpr float kMaxRotateSpeed = 120.0f;

}

EnemyBee::EnemyBee()
{
	m_visibleDistance = kVisibleRange;
	m_visibleRadAngle = kVisibleRadAngle;
}

void EnemyBee::Init()
{

	InitAnimation();

	AddCollision(std::make_unique<Collision::Sphere>(Vector3(0, 30, 0), 45.0f), CollisionType::Body);

	GameObject::m_transform.scale = Vector3{ 0.3f,0.3f,0.3f };

	m_transform.position = Vector3{ 1000,0,100 };

	MV1SetScale(GameObject::m_modelHandle, GameObject::m_transform.scale.ToVECTOR());

	m_pAttackCollision = std::make_unique<AttackCollision>();

	m_state = EnemyBase::State::Caution;

}

void EnemyBee::Update(float deltaTime)
{

	if (m_isDead) {
		m_transform.scale -= Vector3{ 0.01f,0.01f ,0.01f };
		m_transform.scale.x = MyMath::Clamp(m_transform.scale.x, 0.0f, 1.0f);
		m_transform.scale.y = MyMath::Clamp(m_transform.scale.y, 0.0f, 1.0f);
		m_transform.scale.z = MyMath::Clamp(m_transform.scale.z, 0.0f, 1.0f);
	}

	if (m_anim->GetIsPlayAnimation()) {
		m_anim->Update(deltaTime);
	}

	m_pAttackCollision->Update();

	m_transform.position += m_unresolveKnockback;

	printfDx(" aaa %d\n", m_nextPatrolIndex);

	switch (m_state) {

		case EnemyBase::State::Patrol:
			UpdatePatrol(deltaTime);
			break;

		case EnemyBase::State::Caution:
			UpdateCaution(deltaTime);
			break;

		case EnemyBase::State::Combat:
			UpdateCombat(deltaTime);
			break;

	}

	//コリジョンの設定
	for (const auto& collision : m_collisions) {
		collision.shape->SetCenterPos(m_transform.position);
	}

	//プレイヤーへの方向
	Vector3 dif = *m_pTargetPos - GameObject::m_transform.position;

	//プレイヤーとの距離の2乗
	float rangeSq = dif.GetSqLength();

	//見える範囲内かチェック
	if (CheckInViewRange(rangeSq)) {

		//視界角の中にプレイヤーがいるかチェックする
		if (CheckInViewRadAngle()) {
			printfDx("視界の中\n");

			m_state = EnemyBase::State::Combat;
			
		}

	}

	CheckBehind();

}

void EnemyBee::Draw()
{
	for (auto& collision : m_collisions) {
		collision.shape->DrawCollisionShape();
	}

	m_pAttackCollision->DrawCollision();

	EnemyBase::Draw();
	MV1SetScale(m_modelHandle, m_transform.scale.ToVECTOR());

	DrawView();

}

void EnemyBee::End()
{

	EnemyBase::End();

}

void EnemyBee::ResolveCollision(const Collision::Result result, const CollisionData& myData, const CollisionData& otherData, CollisionTag other)
{
	//当たっていなければ即時リターン
	if (!result.isHit)return;

}

void EnemyBee::Death()
{

	m_anim->PlayAnimation(m_animData[static_cast<int>(Animation::EnemyBee::Death)]);

}

void EnemyBee::InitAnimation()
{

	GameObject::m_modelHandle = MV1LoadModel(kModelPath);

	m_anim = std::make_unique<AnimationController>(m_modelHandle);

	const int animNum = static_cast<int>(Animation::EnemyBee::Max);

	m_animData.resize(animNum);

	for (int i = 0; i < animNum; i++) {
		
		m_animData[i].index = i;
		m_animData[i].isForcePlay = false;
		m_animData[i].isLoop = false;

	}

	int flyingIndex = static_cast<int>(Animation::EnemyBee::Flying);

	m_animData[flyingIndex].isLoop = true;

	m_anim->PlayAnimation(m_animData[flyingIndex]);

}

void EnemyBee::UpdatePatrol(float deltaTime)
{
	//次の巡回座標を取得
	Vector3 nextPos = m_patrolPositions[m_nextPatrolIndex];
	//角度の更新
	UpdateForward(kMoveDirection, m_transform.rotation.y);
	//移動量を取得
	float moveAmount = kMoveSpeed * Time::GetDeltaTime();
	//移動
	m_transform.Translate(m_forward * moveAmount);

	//次の巡回座標に着いたら
	if (IsArrivedNextPos(nextPos, moveAmount)) {
		//座標のずれをなくす
		m_transform.position = nextPos;
		//巡回が戻りなら
		if (m_isBack) {
			//戻る
			m_nextPatrolIndex--;

			//最初の地点に来たら
			if (m_nextPatrolIndex <= 0) {
				m_nextPatrolIndex = 0;
				m_isBack = false;
			}

		}
		else
		{
			//巡回位置を更新
			m_nextPatrolIndex++;
			//最後の地点なら
			if (m_nextPatrolIndex >= m_patrolPositions.size() - 1) {
				//巡回を戻りにする
				m_nextPatrolIndex = m_patrolPositions.size() - 1;
				m_isBack = true;
			}

		}
		//状態の変更
		m_state = EnemyBase::State::Caution;
	}

}

void EnemyBee::UpdateCaution(float deltaTime)
{
	//次の目的地
	Vector3 nextPos = m_patrolPositions[m_nextPatrolIndex];
	//次の目的地との差
	Vector3 dif = nextPos - m_transform.position;
	//次の目的地への角度
	float targetAngle = atan2f(-dif.x, -dif.z);
	targetAngle = MyMath::NormalizeRadAngle(targetAngle);

	m_transform.rotation.y = MyMath::NormalizeRadAngle(m_transform.rotation.y);

	//次の目的地への角度と現在の角度の差
	float difAngle = targetAngle - m_transform.rotation.y;
	difAngle = MyMath::NormalizeRadAngle(difAngle);

	printfDx("%f\n", MyMath::RadToDeg(difAngle));

	float rotateSpeed = kMaxRotateSpeed * deltaTime;

	//difAngleが0より小さいか判定
	if (difAngle < 0) {
		//少しづつ目的の角度に近づける
		m_transform.rotation.y += MyMath::Max(difAngle, MyMath::DegToRad(-2));
	}
	else {
		//少しづつ目的の角度に近づける
		m_transform.rotation.y += MyMath::Min(difAngle, MyMath::DegToRad(2));
	}

	//正面ベクトルの更新
	UpdateForward(kMoveDirection, m_transform.rotation.y);

	//角度の差がほぼなくなったら
	if (MyMath::Abs(difAngle) < MyMath::Epsilon) {
		//角度の差をなくす
		m_transform.rotation.y = targetAngle;
		//ステータスを変更
		m_state = EnemyBase::State::Patrol;

	}

}

void EnemyBee::UpdateCombat(float deltaTime)
{
	//目標とのベクトルの差を求める
	Vector3 dif = *m_pTargetPos - m_transform.position;
	//目標への角度を求める
	float targetAngle = atan2f(-dif.x, -dif.z);
	//目標の角度に設定
	m_transform.rotation.y = targetAngle;
	//正面の方向を変更
	UpdateForward(kMoveDirection, targetAngle);
	//正面に進む
	m_transform.Translate(m_forward);

	m_pAttackCollision->GetCollisionData(0).SpawnCollision(0.1f, m_transform.position);

	if (dif.GetLength() < 150) {
		m_anim->PlayAnimation(m_animData[static_cast<int>(Animation::EnemyBee::Bite)]);
	}

	//視界の外に出たら
	if (CheckInViewRange(dif.GetSqLength())) return;

	int nearestPatrolIndex = 0;
	float nearestLengthSq = (m_patrolPositions[nearestPatrolIndex] - m_transform.position).GetSqLength();
	//一番近い巡回の座標を求める
	for (int i = 0; i < m_patrolPositions.size(); i++) {

		Vector3 checkPos = m_patrolPositions[i];
		float distanceSq = (checkPos - m_transform.position).GetSqLength();
		//一番近い座標なら
		if (nearestLengthSq > distanceSq) {
			//値を更新
			nearestLengthSq = distanceSq;
			nearestPatrolIndex = i;

		}

	}

	m_nextPatrolIndex = nearestPatrolIndex;
	m_state = EnemyBase::State::Caution;

}

void EnemyBee::CheckBehind()
{

	//プレイヤーへの方向
	Vector3 dif = *m_pTargetPos - GameObject::m_transform.position;
	//プレイヤーとの距離の2乗
	float range = dif.GetSqLength();

	if (range > 400 * 400)return;

	Vector3 toPlayer = dif.GetNormalize();

	//正面方向とプレイヤー方向の内積
	float dot = Vector3::Dot(m_forward, toPlayer);

	if (dot < -cos(MyMath::DegToRad(75))) {

		printfDx("Behind\n");

	}

}

void EnemyBee::UpdateForward(Vector3 moveDirection,float forward)
{
	//正面の角度
	float yaw = forward;

	float sin = sinf(yaw);
	float cos = cosf(yaw);

	//進行方向に合わせて回転した正面ベクトルを計算する
	m_forward = {
		moveDirection.x * -cos - moveDirection.z * sin,
		0.0f,
		moveDirection.x * sin + moveDirection.z * -cos
	};

	m_forward = m_forward.GetNormalize();

}

Vector3 EnemyBee::UpdateView()
{

	GameObject::m_transform.rotation.y += MyMath::DegToRad(1);
	m_transform.rotation.y = MyMath::NormalizeRadAngle(m_transform.rotation.y);

	//正面の角度
	float forward = GameObject::m_transform.rotation.y;

	//sin
	float sin = sinf(forward);
	//cos
	float cos = cosf(forward);

	//移動ベクトルを回転させる (forwardのベクトル)
	Vector3 moveDirection{
		kMoveDirection.x * -cos - kMoveDirection.z * sin,
		0.0f,
		kMoveDirection.x * sin + kMoveDirection.z * -cos
	};

	moveDirection = moveDirection.GetNormalize();

	//距離の差を求める
	Vector3 dif = GameObject::m_transform.position - *m_pTargetPos;

	float difRange = dif.GetSqLength();

	//プレイヤーが視界の距離の範囲内にいたら
	if (difRange < kVisibleRange * kVisibleRange) {

		//距離の差から角度の差を求める
		float difAngle = atan2f(dif.x, dif.z);

		float normalizeRad = MyMath::NormalizeRadAngle(forward - difAngle);
		normalizeRad = MyMath::Abs(normalizeRad);

		//プレイヤーが視野角に収まっているか調べる
		if (normalizeRad < kVisibleRadAngle) {

			printfDx("生けてる\n");
			printfDx("生けてる\n");
			printfDx("生けてる\n");

		}

		//printfDx("\n");
		//printfDx("normalizeRad %f\n", MyMath::RadToDeg(normalizeRad));

		//printfDx("difAngle %f\n", MyMath::RadToDeg(difAngle));

	}

	//移動
	//m_transform.Translate(moveDirection);

	return moveDirection;

}

void EnemyBee::DrawView()
{

	Vector3 direction = Vector3::Zero;

	float forwardRad = GameObject::m_transform.rotation.y;

	direction.x = -sinf(forwardRad + kVisibleRadAngle);
	direction.z = -cosf(forwardRad + kVisibleRadAngle);

	direction *= kVisibleRange;

	Vector3 rightLine = m_transform.position + direction;

	DrawLine3D(rightLine.ToVECTOR(), m_transform.position.ToVECTOR(), 0xff0000);

	direction.x = -sinf(forwardRad - kVisibleRadAngle);
	direction.z = -cosf(forwardRad - kVisibleRadAngle);

	direction *= kVisibleRange;

	Vector3 leftLine = m_transform.position + direction;

	DrawLine3D(leftLine.ToVECTOR(), m_transform.position.ToVECTOR(), 0xff0000);

	DrawLine3D(rightLine.ToVECTOR(), leftLine.ToVECTOR(), 0x0000ff);

	direction.x = -sinf(forwardRad);
	direction.z = -cosf(forwardRad);

	direction *= kVisibleRange;

	Vector3 centerLine = m_transform.position + direction;

	DrawLine3D(centerLine.ToVECTOR(), m_transform.position.ToVECTOR(), 0x000000);
	DrawLine3D(centerLine.ToVECTOR(), leftLine.ToVECTOR(), 0x00ff00);
	DrawLine3D(centerLine.ToVECTOR(), rightLine.ToVECTOR(), 0x00ff00);

}
