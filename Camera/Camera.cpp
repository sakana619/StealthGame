#include "Camera.h"
#include"../World/Component/Transform.h"
#include"../Utility/Vector3.h"

#include<DxLib.h>
#include<math.h>
#include"../System/Game.h"

namespace {

	constexpr float kLowAngleMost = MyMath::DegToRad(-30);
	constexpr float kHighAngleMost = MyMath::DegToRad(60);

	constexpr float kRotationSpeed = MyMath::DegToRad(2);

	constexpr float kDistaceToTarget = 500;

}

Camera::Camera():
	m_transform(),
	m_r(kDistaceToTarget),
	m_targetPos()
{
}

void Camera::Init()
{

	// カメラのクリッピング距離の設定
	SetCameraNearFar(5, 5);
	// カメラの視野角を設定
	SetupCamera_Perspective(60 * DX_PI_F / 180.0f);
	// カメラの視点、注視点の初期設定
	SetCameraPositionAndTarget_UpVecY(
		VGet(0.0f, 1700.0f, -400.0f),
		VGet(0.0f, 0.0f, -100.0f)
	);

	SetMouseDispFlag(false);

}

void Camera::Update(float deltaTime)
{

	UpdateAngle(deltaTime);
	UpdatePos(deltaTime);

}

void Camera::Draw()
{
}

void Camera::DebugDraw()
{
}

void Camera::End()
{
}

void Camera::UpdateAngle(float deltaTime)
{

	float rotationSpeed = kRotationSpeed * deltaTime;

	//矢印キーでの角度の変更
	if (CheckHitKey(KEY_INPUT_UP)) {
		m_transform.rotation.x += rotationSpeed;
		m_transform.rotation.x = MyMath::Clamp(m_transform.rotation.x, kLowAngleMost, kHighAngleMost);
	}
	if (CheckHitKey(KEY_INPUT_DOWN)) {
		m_transform.rotation.x -= rotationSpeed;
		m_transform.rotation.x = MyMath::Clamp(m_transform.rotation.x, kLowAngleMost, kHighAngleMost);
	}
	if (CheckHitKey(KEY_INPUT_LEFT)) {
		m_transform.rotation.y += rotationSpeed;
	}
	if (CheckHitKey(KEY_INPUT_RIGHT)) {
		m_transform.rotation.y -= rotationSpeed;
	}

	//マウスの座標を取得
	int mouseX, mouseY;
	GetMousePoint(&mouseX, &mouseY);
	//移動量を求める
	int difX = mouseX - Game::kScreenCenterX;
	int difY = mouseY - Game::kScreenCenterY;
	//移動量に合わせてカメラの移動
	m_transform.rotation.x += MyMath::DegToRad(difY) * 0.1f;
	m_transform.rotation.y += MyMath::DegToRad(difX) * 0.1f;
	//マウスカーソルをがはみ出ないようにする
	SetMousePoint(Game::kScreenCenterX, Game::kScreenCenterY);

	m_transform.rotation.y = MyMath::NormalizeRadAngle(m_transform.rotation.y);
	m_transform.rotation.x = MyMath::Clamp(m_transform.rotation.x, kLowAngleMost, kHighAngleMost);

}

void Camera::UpdatePos(float deltaTime)
{

	//
	float sinYaw = sinf(m_transform.rotation.y);
	float cosYaw = cosf(m_transform.rotation.y);

	//
	float sinPitch = sinf(m_transform.rotation.x);
	float cosPitch = cosf(m_transform.rotation.x);

	Vector3 rotatedPos{

		cosPitch * sinYaw * m_r,
		sinPitch * m_r,
		cosPitch * cosYaw * m_r

	};

	Vector3 cameraPos = rotatedPos + m_targetPos;

	SetCameraPositionAndTarget_UpVecY(cameraPos.ToVECTOR(), m_targetPos.ToVECTOR());

}
