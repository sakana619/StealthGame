#pragma once
#include"Color.h"

/// <summary>
/// フェード管理クラス
/// </summary>
class FadeManager
{

public:

	static FadeManager& GetInstance();

	void Update(float deltaTime);
	void Draw();

	/// <summary>
	/// フェードインの開始
	/// </summary>
	/// <param name="durationSec"></param>
	/// <param name="color"></param>
	void StartFadeIn(float durationSec, int color = Color::kBlack);

	/// <summary>
	/// フェードアウトの開始
	/// </summary>
	/// <param name="durationSec"></param>
	/// <param name="color"></param>
	void StartFadeOut(float durationSec, int color = Color::kBlack);

	/// <summary>
	/// フェード中か取得
	/// </summary>
	/// <returns></returns>
	bool IsFading()const { return m_isFading; }

	/// <summary>
	/// フェードアウト中か取得
	/// </summary>
	/// <returns></returns>
	bool IsFadingOut()const { return m_speed > 0; }

private:

	FadeManager();
	~FadeManager() = default;

	// コピー禁止
	FadeManager(const FadeManager&) = delete;
	// コピー代入禁止
	FadeManager& operator=(const FadeManager&) = delete;
	// ムーブ禁止
	FadeManager(FadeManager&&) = delete;
	// ムーブ代入禁止
	FadeManager& operator=(const FadeManager&&) = delete;

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

	/// <summary>
	/// フェードの時間
	/// </summary>
	float m_durationSec;

	/// <summary>
	/// フェード中かどうか
	/// </summary>
	bool m_isFading;

};
