#include "Player.h"
#include"CharacterBase.h"

#include<DxLib.h>
#include<cassert>
#include<math.h>
#include<memory>
#include"AnimationController.h"
#include"../../Camera/Camera.h"
#include"Enemy/EnemyBase.h"
#include"Enemy/EnemyManager.h"
#include"../Component/Collision.h"
#include"../../System/Time.h"

namespace {

	const char* const kModelPath = ".\\Resource\\Hero.x";	// プレイヤーモデルのファイルパス

	//アニメーションの名前
	const char* const kAnimationName[] = {
		"Neutral",
		"Run",
		"JumpIn",
		"JumpLoop",
		"JumpOut",
		"Attack1",
	};

}

Player::Player():
	m_pCamera(nullptr)
{
}

Player::Player(Camera* pCamera) :
	m_isDodging(false),
	m_pCamera(pCamera)
{
}

void Player::Init()
{

	AddCollision(std::make_unique<Collision::AABB>(Vector3(0, 100, 0), Vector3(100, 200, 100)), CollisionType::Body);
	AddCollision(std::make_unique<Collision::AABB>(Vector3(0, -1, 0), Vector3(100, 14, 100)), CollisionType::Foot);

	m_pAttackCollision = std::make_unique<AttackCollision>();
	m_pAttackCollision->AddCollision<Collision::AABB>(Vector3::Zero, Vector3(100, 100, 100));

	m_collisionTag = CollisionTag::Player;

	GameObject::m_modelHandle = MV1LoadModel(kModelPath);

	//アニメーションデータの移動量を無効
	int moveAnimFrameIndex = MV1SearchFrame(m_modelHandle, "root");
	MV1SetFrameUserLocalMatrix(
		m_modelHandle,
		moveAnimFrameIndex,
		MV1GetFrameLocalMatrix(m_modelHandle, moveAnimFrameIndex)
	);

	m_anim = std::make_unique<AnimationController>(m_modelHandle);

	int animNum = static_cast<int>(Animation::Player::Max);
	m_animData.resize(animNum);

	for (int i = 0; i < animNum; i++) {
		m_animData[i].index = MV1GetAnimIndex(m_modelHandle, kAnimationName[i]);
	}

	m_animData[static_cast<int>(Animation::Player::Neutral)].isLoop = true;
	m_animData[static_cast<int>(Animation::Player::Run)].isLoop = true;
	m_animData[static_cast<int>(Animation::Player::JumpIn)].isLoop = false;
	m_animData[static_cast<int>(Animation::Player::JumpLoop)].isLoop = true;
	m_animData[static_cast<int>(Animation::Player::JumpOut)].isLoop = false;
	m_animData[static_cast<int>(Animation::Player::Attack)].isLoop = false;

	m_animData[static_cast<int>(Animation::Player::Neutral)].isForcePlay = false;
	m_animData[static_cast<int>(Animation::Player::Run)].isForcePlay = false;
	m_animData[static_cast<int>(Animation::Player::JumpIn)].isForcePlay = false;
	m_animData[static_cast<int>(Animation::Player::JumpLoop)].isForcePlay = false;
	m_animData[static_cast<int>(Animation::Player::JumpOut)].isForcePlay = false;
	m_animData[static_cast<int>(Animation::Player::Attack)].isForcePlay = true;

	m_anim->PlayAnimation(m_animData[static_cast<int>(Animation::Player::Neutral)]);

	m_transform.position = Vector3(1000, 500, 1000);

}

void Player::Update(float deltaTime)
{

	UpdateAnimation();

	Dodge();

	//if (m_isDodging)return;

	Move();

	m_fallSpeed -= 13;
	m_transform.position.y += m_fallSpeed;

	for (auto& collision : m_collisions) {
		collision.shape->SetCenterPos(m_transform.position);
	}

	if (m_pAttackCollision)m_pAttackCollision->Update();

	if (CheckHitKey(KEY_INPUT_R)) {

		m_pAttackCollision->GetCollisionDatas()[0].SpawnCollision(3.0f, m_transform.position);

	}

	if (!m_pEnemyManager) return;

	//一番近い敵を取得
	EnemyBase* nearestEnemy = m_pEnemyManager->GetNearestEnemy(GameObject::m_transform.position);

	if (!nearestEnemy)return;

	Vector3 nearestEnemyPos = nearestEnemy->GetPosition();

	//距離の差を求める
	Vector3 dif = nearestEnemyPos - GameObject::m_transform.position;
	//距離の差が大きかったらリターン
	if (dif.GetSqLength() > 400 * 400)return;

	//敵へのベクトル
	Vector3 enemyToPlayer = GameObject::m_transform.position - nearestEnemyPos;
	enemyToPlayer = enemyToPlayer.GetNormalize();
	//一番近い敵の正面方向と一番近い敵へのベクトルで内積を求める
	float dot = Vector3::Dot(nearestEnemy->GetForward(), enemyToPlayer);

	//敵の後ろにいたら
	if (dot < -cosf(MyMath::DegToRad(75))) {

		if (CheckHitKey(KEY_INPUT_L)) {
			//アニメーションの再生
			m_anim->PlayAnimation(m_animData[static_cast<int>(Animation::Player::Attack)]);
			//敵にダメージ
			nearestEnemy->Damage(1);
			//方向を合わせる
			m_transform.rotation.y = atan2f(-(nearestEnemyPos.x - m_transform.position.x), -(nearestEnemyPos.z - m_transform.position.z));
		}

	}

}

void Player::Draw()
{

	GameObject::Draw();
	for (auto& collision : m_collisions) {

		int color = collision.type == CollisionType::Body ? 0xffffff : 0x000000;

		collision.shape->DrawCollisionShape(color);
	}
	m_pAttackCollision->DrawCollision();
}

void Player::End()
{

	GameObject::End();

}

void Player::ResolveCollision(const Collision::Result result, const CollisionData& myData, const CollisionData& otherData, CollisionTag other)
{
	//衝突していないなら即時リターン
	if (!result.isHit)return;

	//押し戻し量
	Vector3 push = result.normal * result.penetration;

	//下方向に当たっていれば
	if (result.normal.y > 0 && myData.type == CollisionType::Foot) {
		m_fallSpeed = 0;
		m_transform.position.y += push.y;
	}

	if (MyMath::Abs(result.normal.z) > 0 && myData.type == CollisionType::Body) {
		m_transform.position.z += push.z;
	}

	if (MyMath::Abs(result.normal.x) > 0 && myData.type == CollisionType::Body) {
		m_transform.position.x += push.x;
	}

	for (auto& collision : m_collisions) {
		collision.shape->SetCenterPos(m_transform.position);
	}

}

void Player::SetEnemyManager(EnemyManager* pEnemyManager)
{

	assert(pEnemyManager);
	if (!pEnemyManager)return;
	m_pEnemyManager = pEnemyManager;

}

Vector3 Player::GetInputVectorRotedByCamera()
{

	Vector3 moveDirection = Vector3::Zero;

	if (CheckHitKey(KEY_INPUT_W)) {
		moveDirection.z += 1;
	}

	if (CheckHitKey(KEY_INPUT_S)) {
		moveDirection.z -= 1;
	}

	if (CheckHitKey(KEY_INPUT_A)) {
		moveDirection.x -= 1;
	}

	if (CheckHitKey(KEY_INPUT_D)) {
		moveDirection.x += 1;
	}

	if (moveDirection.GetSqLength() == 0)return Vector3::Zero;

	//カメラのヨーのラジアン角
	const float cameraYaw = m_pCamera->GetYaw();
	//移動方向から角度を求める
	float targetRad = atan2f(moveDirection.x, moveDirection.z);
	//カメラの水平角度に合わせて移動する
	targetRad += cameraYaw;

	targetRad = MyMath::NormalizeRadAngle(targetRad);

	//目標角度との差を求める
	float angleDifference = targetRad - GameObject::m_transform.rotation.y;
	//ラジアン角の正規化
	angleDifference = MyMath::NormalizeRadAngle(angleDifference);

	//線形補間
	m_transform.rotation.y += angleDifference * 0.1f;
	m_transform.rotation.y = MyMath::NormalizeRadAngle(m_transform.rotation.y);

	//移動量を正規化
	moveDirection = moveDirection.GetNormalize();

	Vector3 rotateInCameraVector = Vector3::Zero;

	float sinYaw = sinf(cameraYaw);
	float cosYaw = cosf(cameraYaw);

	rotateInCameraVector.x = moveDirection.x * -cosYaw - moveDirection.z * sinYaw;
	rotateInCameraVector.y = 0.0f;
	rotateInCameraVector.z = moveDirection.x * sinYaw + moveDirection.z * -cosYaw;

	return rotateInCameraVector;

}

void Player::UpdateAnimation()
{

	//アニメーションの再生がされていないなら待機アニメーションの再生
	if (!m_anim->GetIsPlayAnimation()) m_anim->PlayAnimation(m_animData[static_cast<int>(Animation::Player::Neutral)]);

	//割り込み不可能なアニメーションなら
	if (m_anim->GetIsForcePlay()) {
		m_anim->Update();
		//リターン
		return;
	}


	State nextState = State::Idle;
	int nextAnimIndex = static_cast<int>(Animation::Player::Neutral);

	//移動があったら
	if (GetInputVectorRotedByCamera().GetSqLength() != 0) {
		//次のアニメーションを走りアニメーションに設定
		nextState = State::Run;
		nextAnimIndex = static_cast<int>(Animation::Player::Run);
	}

	//アニメーションの変更があったら
	if (nextState != m_state) {
		//アニメーションの変更
		m_state = nextState;
		m_anim->PlayAnimation(m_animData[nextAnimIndex]);
	}

	//アニメーションの更新
	m_anim->Update();

}

void Player::Move()
{
	const float kMoveSpeed = 500.0f;
	GameObject::m_transform.position += GetInputVectorRotedByCamera() * kMoveSpeed * Time::GetDeltaTime();
}

void Player::Dodge()
{

	static Vector3 moveVector = Vector3::Zero;

	static float speed = 0;

	//printfDx("%f\n", speed);

	if (m_isDodging) {

		GameObject::m_transform.Translate(moveVector);

		moveVector *= speed;

		speed *= 0.05f;

		if (speed <= 0) {
			m_isDodging = false;
		}

		return;

	}

	if (CheckHitKey(KEY_INPUT_0)) {

		m_isDodging = true;

		speed = 100.0f;

		//プレイヤーの向き
		const float forward = GameObject::m_transform.rotation.y;

		const Vector3 moveDirection = Vector3::ZAxis;

		//forwardの
		float sin = sinf(forward);
		float cos = cosf(forward);

		moveVector = Vector3::Zero;

		moveVector = {
			moveDirection.x * -cosf(forward) - moveDirection.z * sinf(forward),
			0.0f,
			moveDirection.x * sinf(forward) + moveDirection.z * -cosf(forward)
		};

		moveVector = moveVector.GetNormalize();

		//moveVector *= 100;

		GameObject::m_transform.Translate(moveVector);

	}

}
