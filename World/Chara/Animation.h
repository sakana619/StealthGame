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
		IdleGun,	//待機_銃を持っている
		IdleShoot,	//待機_銃を撃っている
		Jump,		//ジャンプした瞬間
		JumpIdle,	//ジャンプ中
		JumpLand,	//着地
		No,			//首をふる
		Punch,
		Run,
		RunGun,
		RunShoot,
		Walk,		//歩き
		WalkGun,	//歩き_
		Wave,		//手をふる
		Yes,		//頷く

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
