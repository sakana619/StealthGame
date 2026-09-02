#pragma once

namespace Animation
{

	enum class Player {

		Neutral = 0,
		Run,
		JumpIn,
		JumpLoop,
		JumpOut,
		Attack,
		Max

	};

	enum class EnemyBee {

		Bite = 0,
		Death,
		Flying,
		HitRecive,
		Max,

	};

	/// <summary>
	/// アニメーションのデータ
	/// </summary>
	struct AnimationData
	{
		int index;			//アニメーション番号
		bool isLoop;		//ループするか
		bool isForcePlay;	//割り込み可能か
	};

};
