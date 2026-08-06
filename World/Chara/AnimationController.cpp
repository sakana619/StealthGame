#include "AnimationController.h"
#include"../../System/Time.h"

#include<DxLib.h>

namespace {

	const float kAnimationSpeed = 1;

}

AnimationController::AnimationController(int modelHandle) :
	m_modelHandle(modelHandle),
	m_attachIndex(-1),
	m_currentAnimIndex(-1),
	m_time(0),
	m_totalTime(0),
	m_isLoop(false),
	m_isPlaying(false),
	m_isForcePlay(false)
{
}

void AnimationController::Update()
{

	if (!m_isPlaying)return;

	m_time += Time::GetDeltaTime() * 30;

	if (m_totalTime <= m_time) {
		//再生時間をリセット
		m_time -= m_totalTime;

		if (!m_isLoop) {
			m_isPlaying = false;
			m_isForcePlay = false;
			m_currentAnimIndex = -1;
		}

	}

	MV1SetAttachAnimTime(m_modelHandle, m_attachIndex, m_time);

}

void AnimationController::PlayAnimation(const Animation::AnimationData& animData)
{

	if (m_isForcePlay || m_currentAnimIndex == animData.index)return;

	//リセット
	m_time = 0.0f;
	if (m_attachIndex != -1)MV1DetachAnim(m_modelHandle, m_attachIndex);

	m_attachIndex = MV1AttachAnim(m_modelHandle, animData.index, -1, false);

	//アニメーションのトータル時間を取得
	m_totalTime = MV1GetAttachAnimTotalTime(m_modelHandle, m_attachIndex);
	//m_totalTime = MV1GetAnimTotalTime(m_modelHandle, animData.index);

	//アニメーションの再生
	m_isPlaying = true;

	//アニメーションデータを設定
	m_currentAnimIndex = animData.index;
	m_isForcePlay = animData.isForcePlay;
	m_isLoop = animData.isLoop;

}

void AnimationController::DebugDraw()
{

	printfDx("Animation time : %f\n", m_time);
	printfDx("Animation totalTime : %f\n", m_totalTime);
	printfDx("Animation isPlaying : %d\n", m_isPlaying);
	printfDx("Animation attachIndex : %d\n", m_attachIndex);
	printfDx("Animation currentAnimIndex : %d\n", m_currentAnimIndex);

	//printfDx("Animation isLoop : ");
	//printfDx(m_isLoop ? "TRUE\n" : "FALSE\n");

}

void AnimationController::StopAnimation()
{
	//リセット
	m_time = 0.0f;
	m_totalTime = 0.0f;
	m_currentAnimIndex = -1;
	if (m_attachIndex != -1)MV1DetachAnim(m_modelHandle, m_attachIndex);
	m_attachIndex = -1;
	m_isForcePlay = false;
	m_isLoop = false;
	m_isPlaying = false;
}
