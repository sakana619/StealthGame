#pragma once

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
	void Draw(){}
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
	/// 表示状態の取得
	/// </summary>
	/// <returns></returns>
	bool GetIsVisible()const { return m_isVisible; }

private:

	/// <summary>
	/// UIのハンドル
	/// </summary>
	int m_handle;

	/// <summary>
	/// 表示しているか
	/// </summary>
	bool m_isVisible;

};
