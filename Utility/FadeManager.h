#pragma once
#include"Color.h"

/// <summary>
/// フェード管理クラス
/// </summary>
class FadeManager
{

public:

	static FadeManager& GetInstance();


private:

	FadeManager();
	~FadeManager() = default;

	/// <summary>
	/// フェードインの開始
	/// </summary>
	/// <param name="color"></param>
	void StartFadeIn(float duration, int color = Color::kBlack);

	/// <summary>
	/// フェードアウトの開始
	/// </summary>
	/// <param name="color"></param>
	void StartFadeOut(float duration, int color = Color::kBlack);

	/// <summary>
	/// フェード中か取得
	/// </summary>
	/// <returns></returns>
	bool IsFading()const;

private:

	/// <summary>
	/// フェードの色
	/// </summary>
	int m_color;

	/// <summary>
	/// フェードの明るさ
	/// </summary>
	int m_bright;

	/// <summary>
	/// フェードの速度
	/// </summary>
	float m_speed;

};
