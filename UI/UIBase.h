#pragma once

#include"../Utility/Vector3.h"

/// <summary>
/// UIの基底クラス
/// </summary>
class UIBase
{

public:

	UIBase();
	UIBase(int handle);
	virtual ~UIBase() = default;

	virtual void Init() = 0;
	virtual void Update(float deltaTime){}
	virtual void Draw() = 0;
	virtual void End() = 0;

	/// <summary>
	/// 表示状態の取得
	/// </summary>
	/// <returns></returns>
	bool GetIsVisible()const { return m_isVisible; }

	/// <summary>
	/// 座標の取得
	/// </summary>
	/// <returns></returns>
	const Vector3& GetPosition()const { return m_position; }

	/// <summary>
	/// ハンドルを設定
	/// </summary>
	/// <param name="handle"></param>
	void SetHandle(int handle) { m_handle = handle; }

	/// <summary>
	/// 表示状態の設定
	/// </summary>
	/// <param name="visible"></param>
	void SetVisible(bool visible) { m_isVisible = visible; }

	/// <summary>
	/// 座標の設定
	/// </summary>
	/// <param name="position"></param>
	void SetPosition(const Vector3& position) { m_position = position; }

	/// <summary>
	/// 表示サイズの変更
	/// </summary>
	/// <param name="scale"></param>
	void SetScale(float scale) { m_scale = scale; }

	/// <summary>
	/// 標準角度の変更
	/// </summary>
	/// <param name="angle">ラジアン角指定の角度</param>
	void SetAngle(float angle) { m_angleRad = angle; }

protected:

	/// <summary>
	/// UIのハンドル
	/// </summary>
	int m_handle;

	/// <summary>
	/// 表示しているか
	/// </summary>
	bool m_isVisible;

	/// <summary>
	/// 画像表示サイズ
	/// </summary>
	float m_scale;

	/// <summary>
	/// 画像表示角度
	/// </summary>
	float m_angleRad;

	/// <summary>
	/// 座標
	/// </summary>
	Vector3 m_position;

};
