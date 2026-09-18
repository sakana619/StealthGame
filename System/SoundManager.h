#pragma once
#include<array>

namespace Sound {

	enum class BGM {

		TitleScene = 0,
		GameScene,
		ClearScene,
		GameOverScene,

		Max,

	};

	enum class SE {

		Max,

	};

}

class SoundManager
{

public:

	/// <summary>
	/// シングルトンのインスタンスを取得
	/// </summary>
	/// <returns></returns>
	static SoundManager& GetInstance();

	~SoundManager() = default;

	/// <summary>
	/// 初期化処理
	/// </summary>
	void Init();

	/// <summary>
	/// 終了処理
	/// </summary>
	void End();

	/// <summary>
	/// BGMの再生
	/// </summary>
	/// <param name="bgm"></param>
	void PlayBGM(Sound::BGM bgm);

	/// <summary>
	/// BGMの再生をストップ
	/// </summary>
	void StopBgm();

	/// <summary>
	/// SEの再生
	/// </summary>
	/// <param name="se">再生するSE</param>
	void PlaySe(Sound::SE se);

	/// <summary>
	/// フェードの更新
	/// </summary>
	void UpdateFade(float deltaTime);

private:

	SoundManager();

	//シングルトンパターンのクラスではコピーできないように『禁止』する
	//コピー禁止
	SoundManager(const SoundManager&) = delete;
	//コピー代入禁止
	SoundManager& operator=(const SoundManager&) = delete;
	//ムーブ禁止
	SoundManager(SoundManager&&) = delete;
	//ムーブ代入禁止
	SoundManager& operator=(const SoundManager&&) = delete;

	/// <summary>
	/// BGMの読み込み
	/// </summary>
	void LoadBgm();

	/// <summary>
	/// SEの読み込み
	/// </summary>
	void LoadSe();

	/// <summary>
	/// フェードイン中の処理
	/// </summary>
	void UpdateFadeIn(float deltaTime);

	/// <summary>
	/// フェードアウト中の処理
	/// </summary>
	void UpdateCrossFade(float deltaTime);

	/// <summary>
	/// フェードインに入る
	/// </summary>
	void StartFadeIn();

private:

	/// <summary>
	/// BGMのハンドル
	/// </summary>
	std::array<int, static_cast<int>(Sound::BGM::Max)>m_bgmHandles;

	/// <summary>
	/// SEのハンドル
	/// </summary>
	std::array<int, static_cast<int>(Sound::SE::Max)>m_seHandles;

	/// <summary>
	/// 読み込みしたか
	/// </summary>
	bool m_isLoaded;

	/// <summary>
	/// 現在の音量
	/// </summary>
	float m_currentVolume;

	/// <summary>
	/// 次に再生するBGMの音量
	/// </summary>
	float m_nextVolume;

	/// <summary>
	/// 現在再生中のBGM
	/// </summary>
	int m_currentBgmHandle;

	/// <summary>
	/// 次に再生するBGM
	/// </summary>
	int m_nextBgmHandle;

	//フェードの状態
	enum class FadeState {

		None,
		In,
		CrossFade

	};

	//今のフェードの状態
	FadeState m_fadeState;

};
