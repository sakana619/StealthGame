#pragma once
#include"Animation.h"

class AnimationController
{

public:

	AnimationController(int modelHandle);
	~AnimationController() = default;

	void Update();

	/// <summary>
	/// アニメーションの再生
	/// </summary>
	/// <param name="animData"></param>
	void PlayAnimation(const Animation::AnimationData& animData);

	void DebugDraw();

	/// <summary>
	/// アニメーションの再生を停止
	/// </summary>
	void StopAnimation();

	int GetAttachAnimationIndex()const { return m_attachIndex; }

	/// <summary>
	/// アニメーションの再生時間を取得
	/// </summary>
	/// <returns></returns>
	float GetAnimationTime()const { return m_time; }

	/// <summary>
	/// アニメーション再生中か取得
	/// </summary>
	/// <returns></returns>
	bool GetIsPlayAnimation()const { return m_isPlaying; }

	bool GetIsForcePlay()const { return m_isForcePlay; }

private:

	/// <summary>
	/// アニメーションを再生させるモデルハンドル
	/// </summary>
	int m_modelHandle;

	/// <summary>
	/// モデルにアタッチするアニメーション番号
	/// </summary>
	int m_attachIndex;

	/// <summary>
	/// 現在の再生中のアニメーション番号
	/// </summary>
	int m_currentAnimIndex;

	/// <summary>
	/// 再生中のアニメーションの再生時間
	/// </summary>
	float m_time;

	/// <summary>
	/// 再生中のアニメーションの総尺
	/// </summary>
	float m_totalTime;

	/// <summary>
	/// 再生中のアニメーションがループするか
	/// </summary>
	bool m_isLoop;

	/// <summary>
	/// アニメーションが再生中かどうか
	/// </summary>
	bool m_isPlaying;

	/// <summary>
	/// 割り込み不可かどうか
	/// </summary>
	bool m_isForcePlay;

};
