#pragma once
#include"UIBase.h"

/// <summary>
/// UIのビルボードクラス
/// </summary>
class UIBillboard :UIBase
{

public:

	UIBillboard();
	UIBillboard(int graphHandle);
	~UIBillboard()override;

	void Init()override;
	void Draw()override;
	void End()override;

	/// <summary>
	/// 描画する画像の中心座標のXを設定する
	/// 画像の中心を座標の位置にしたいなら 0.5f
	/// </summary>
	/// <param name="centerX"></param>
	void SetDrawCenterX(float centerX) { m_drawCenterX = centerX; }

	/// <summary>
	/// 描画する画像の中心座標のYを設定する
	/// 画像の中心を座標の位置にしたいなら 0.5f
	/// </summary>
	/// <param name="centerY"></param>
	void SetDrawCenterY(float centerY) { m_drawCenterY = centerY; }

private:

	/// <summary>
	/// 描画する画像の中心座標
	/// </summary>
	float m_drawCenterX;

	/// <summary>
	/// 描画する画像の中心座標
	/// </summary>
	float m_drawCenterY;

};
