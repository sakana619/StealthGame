#include "Time.h"

#include<DxLib.h>
#include<cassert>
#include"../Utility/MyMath.h"

LONGLONG Time::m_prevTime = 0.0f;
float Time::m_deltaTime = 0.0f;
float Time::m_unscaledDeltaTime = 0.0f;
float Time::m_timeScale = 1.0f;
float Time::m_fpsTimer = 0.0f;
int Time::m_fpsCount = 0;
float Time::m_fps = 0.0f;
int Time::m_oneFramePerMicrosec = 1000000 / 60;

namespace {

	constexpr float kCountPerSecond = 1000000.0f;

	constexpr float kMaxDeltaTime = 0.1f;

}

void Time::Init()
{

	m_prevTime = GetNowHiPerformanceCount();

}

void Time::Update()
{
	//現在の時間
	LONGLONG currentTime = GetNowHiPerformanceCount();
	//経過時間を求める
	LONGLONG dif = currentTime - m_prevTime;
	//更新
	m_prevTime = currentTime;

	//秒に直す
	float deltaTime = dif / kCountPerSecond;
	//最大値以内に収める
	deltaTime = MyMath::Min(deltaTime, kMaxDeltaTime);

	//タイムスケールに依存しない経過時間を更新
	m_unscaledDeltaTime = deltaTime;
	//タイムスケールを掛ける
	m_deltaTime = deltaTime * m_timeScale;

	//経過時間を加算
	m_fpsTimer += m_unscaledDeltaTime;
	//フレームを加算
	m_fpsCount++;

	//1秒経過
	if (m_fpsTimer >= 1.0f) {
		//FPSを設定
		m_fps = m_fpsCount;
		//リセット
		m_fpsCount = 0;
		m_fpsTimer = 0;
	}

}

void Time::SetTimeScale(float timeScale)
{

	if (timeScale < 0) {
		assert(false && "Time::SetTimeScale : timeScale < 0");
		timeScale = 0;
	}
	m_timeScale = timeScale;

}

void Time::SetFPS(int FPS)
{

	if (FPS <= 0) {
		assert(false && "Time::SetFPS : FPS < 0");
		FPS = 1;
	}

	m_oneFramePerMicrosec = kCountPerSecond / FPS;
}
