#pragma once

typedef __int64 LONGLONG;

class Time
{

public:

	static void Init();
	static void Update();

	/// <summary>
	/// 1F前の時間を取得
	/// </summary>
	/// <returns></returns>
	static LONGLONG GetPrevTime() { return m_prevTime; }

	/// <summary>
	/// タイムスケールに依存した経過時間
	/// </summary>
	/// <returns></returns>
	static float GetDeltaTime() { return m_deltaTime; }

	/// <summary>
	/// タイムスケールに依存しない経過時間
	/// </summary>
	/// <returns></returns>
	static float GetUnscaledDeltaTime() { return m_unscaledDeltaTime; }

	static float GetTimeScale(){ return m_timeScale; }

	static int GetoneFramePerMicrosec() { return m_oneFramePerMicrosec; }

	static float GetFPS() { return m_fps; }

	static void SetTimeScale(float timeScale);

	static void SetFPS(int FPS);

private:

	/// <summary>
	/// 1F前の時間
	/// </summary>
	static LONGLONG m_prevTime;

	/// <summary>
	/// 1F前からのタイムスケールに依存した経過時間
	/// </summary>
	static float m_deltaTime;

	/// <summary>
	/// 1F前からのタイムスケールに依存しない経過時間
	/// </summary>
	static float m_unscaledDeltaTime;

	/// <summary>
	/// 時間が経過するスケール
	/// </summary>
	static float m_timeScale;

	/// <summary>
	/// FPS計測タイマー
	/// </summary>
	static float m_fpsTimer;

	/// <summary>
	/// FPSを数える
	/// </summary>
	static int m_fpsCount;

	static float m_fps;

	static int m_oneFramePerMicrosec;

};
