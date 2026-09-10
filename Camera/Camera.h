#pragma once
#include"../World/Component/Transform.h"

class Camera
{

public:

	Camera();
	~Camera() = default;

	/// <summary>
	/// 初期化処理
	/// </summary>
	void Init();

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw();

	/// <summary>
	/// デバックの描画
	/// </summary>
	void DebugDraw();

	/// <summary>
	/// 終了処理
	/// </summary>
	void End();

	/// <summary>
	/// カメラのターゲット座標を設定する
	/// </summary>
	/// <param name="targetPos"></param>
	void SetTargetPos(const Vector3& targetPos) { m_targetPos = targetPos; }

	/// <summary>
	/// カメラのヨーのラジアン角を取得する関数
	/// </summary>
	/// <returns></returns>
	const float GetYaw()const { return m_transform.rotation.y; }

	/// <summary>
	/// カメラのピッチのラジアン角を取得する関数
	/// </summary>
	/// <returns></returns>
	const float GetPitch()const { return m_transform.rotation.x; }

private:

	/// <summary>
	/// カメラの角度の更新
	/// </summary>
	void UpdateAngle();

	/// <summary>
	/// カメラの座標の更新
	/// </summary>
	void UpdatePos();

private:

	Transform m_transform;

	/// <summary>
	/// 目標との距離 (半径)
	/// </summary>
	float m_r;
	/// <summary>
	/// 目標の座標
	/// </summary>
	Vector3 m_targetPos;

};
