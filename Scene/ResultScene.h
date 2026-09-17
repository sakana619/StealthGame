#pragma once
#include"SceneBase.h"
#include<string>
#include<array>

namespace Scene {

	enum class ResultType {
		Clear,
		GameOver,
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

	//このシーンで出来ること
	enum class Command {
		ToTitle,		//タイトルシーンに接続
		RestartGame,	//ゲーム再プレイ

		MAX,
	};

	struct CommandData {

		std::string message;

		int fontHandle;

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

};
