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
	void Update(float deltaTime){}
	virtual void Draw() = 0;
	virtual void End() = 0;

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
	/// 表示状態の取得
	/// </summary>
	/// <returns></returns>
	bool GetIsVisible()const { return m_isVisible; }

	/// <summary>
	/// 座標の取得
	/// </summary>
	/// <returns></returns>
	const Vector3& GetPosition()const { return m_position; }

private:

	/// <summary>
	/// UIのハンドル
	/// </summary>
	int m_handle;

	/// <summary>
	/// 表示しているか
	/// </summary>
	bool m_isVisible;

	/// <summary>
	/// 座標
	/// </summary>
	Vector3 m_position;

};
