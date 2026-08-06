#pragma once

class SceneBase;

class SceneManager
{

public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	SceneManager();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~SceneManager();

	/// <summary>
	/// 初期化
	/// </summary>
	void Init();

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw();

	/// <summary>
	/// 終了処理
	/// </summary>
	void End();

private:

	/// <summary>
	/// 現在のシーン
	/// </summary>
	SceneBase* m_pScene;

	/// <summary>
	/// 次のシーン
	/// </summary>
	SceneBase* m_pNextScene;

};

