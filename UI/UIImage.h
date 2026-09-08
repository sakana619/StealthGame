#pragma once

#include"UIBase.h"

/// <summary>
/// 画像のUIクラス
/// </summary>
class UIImage :UIBase
{

public:

	UIImage();
	UIImage(int graphHandle);
	~UIImage();

	void Init()override;
	void Update(float deltaTime) {}
	void Draw()override;
	void End()override;

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

private:

	/// <summary>
	/// 画像表示サイズ
	/// </summary>
	float m_scale;

	/// <summary>
	/// 画像表示角度
	/// </summary>
	float m_angleRad;

};
