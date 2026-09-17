#include "ResultScene.h"
#include"SceneBase.h"

#include<DxLib.h>
#include<cassert>
#include"GameScene.h"
#include"TitleScene.h"
#include"../Utility/Color.h"
#include"../Utility/Input.h"

namespace {



}

ResultScene::ResultScene(Scene::ResultType):
	m_commandList(),
	m_selectCommandIndex(0)
{
}

void ResultScene::Init()
{
	int toTitleIndex = static_cast<int>(Command::ToTitle);
	m_commandList[toTitleIndex].command = Command::ToTitle;
	m_commandList[toTitleIndex].message = "タイトルへ";

	int restartGameIndex = static_cast<int>(Command::RestartGame);
	m_commandList[restartGameIndex].command = Command::RestartGame;
	m_commandList[restartGameIndex].message = "もう一度プレイ";

}

SceneBase* ResultScene::Update(float deltaTime)
{

	//入力の受付
	if (Input::IsPressed(PAD_INPUT_UP)) {
		m_selectCommandIndex--;
		if (m_selectCommandIndex < 0) {
			m_selectCommandIndex = m_commandList.size() - 1;
		}
	}
	if (Input::IsPressed(PAD_INPUT_DOWN)) {
		m_selectCommandIndex++;
		if (m_selectCommandIndex >= m_commandList.size()) {
			m_selectCommandIndex = 0;
		}
	}

	//決定キーが入力されたら (スペースキー)
	if (Input::IsPressed(PAD_INPUT_10)) {
		//実行するコマンド
		Command command = m_commandList[m_selectCommandIndex].command;

		//コマンドの処理を実行
		switch (command)
		{
		case ResultScene::Command::ToTitle:
			return new TitleScene();
		case ResultScene::Command::RestartGame:
			return new GameScene();
		default:
			//ここに来たらコマンドの設定がされていない

			assert(false && "");
			//タイトルシーンに戻す
			return new TitleScene();

		}

	}

	return nullptr;

}

void ResultScene::Draw()
{

	for (int i = 0; i < m_commandList.size(); i++) {

		int posY = 400 + i * 30;
		if (i == m_selectCommandIndex) {
			DrawString(50, posY, "->", Color::kWhite);
		}

		//Scene名表示
		DrawString(80, posY, m_commandList[i].message.c_str(), Color::kWhite);

	}

}

void ResultScene::End()
{
}
