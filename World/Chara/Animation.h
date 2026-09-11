#pragma once

/// <summary>
/// アニメーション
/// </summary>
namespace Animation
{
	/// <summary>
	/// プレイヤーのアニメーション
	/// </summary>
	enum class Player {
		Death = 0,	//死亡
		Duck,		//お辞儀
		HitRect,	//被ダメージ
		Idle,		//待機
		IdleGun,	//待機_銃を
		IdleShoot,	//待機
		Jump,
		JumpIdle,
		JumpLand,
		No,
		Punch,
		Run,
		RunGun,
		RunShoot,
		Walk,
		WalkGun,
		Wave,
		Yes,

		Max,

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
