#pragma once
#include"SceneBase.h"
#include<string>
#include<array>

namespace Scene {

	/// <summary>
	/// リザルトシーンの種類
	/// </summary>
	enum class ResultType {
		Clear,		//クリア
		GameOver,	//ゲームオーバー
		MAX,
	};

}

/// <summary>
/// ゲームオーバーシーン
/// </summary>
class ResultScene :public SceneBase
{

public:

	ResultScene(Scene::ResultType);
	~ResultScene()override = default;

	void Init()override;
	SceneBase* Update(float deltaTime)override;
	void Draw()override;
	void End()override;

private:

	/// <summary>
	/// このシーンのコマンド
	/// </summary>
	enum class Command {
		ToTitle,		//タイトルシーンに接続
		RestartGame,	//ゲーム再プレイ

		MAX,
	};

	/// <summary>
	/// コマンド関連をまとめた構造体
	/// </summary>
	struct CommandData {
		/// <summary>
		/// 表示するメッセージ
		/// </summary>
		std::string message;
		/// <summary>
		/// メッセージのフォント
		/// </summary>
		int fontHandle;
		/// <summary>
		/// 設定されたコマンド
		/// </summary>
		Command command;

	};

	/// <summary>
	/// コマンドのデータリスト
	/// </summary>
	std::array<CommandData, static_cast<int>(Command::MAX)>m_commandList;

	/// <summary>
	/// 現在選択されているコマンドの番号
	/// </summary>
	int m_selectCommandIndex;

	/// <summary>
	/// リザルトのロゴ
	/// </summary>
	int m_resultLogo;

};
