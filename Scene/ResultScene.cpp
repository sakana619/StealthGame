#include "ResultScene.h"
#include"SceneBase.h"

#include<DxLib.h>
#include<cassert>
#include"GameScene.h"
#include"TitleScene.h"
#include"../System/SoundManager.h"
#include"../Utility/Color.h"
#include"../Utility/Input.h"

namespace {

	const char* const kClearLogo = "";

	const char* const kGameOverLogo = "";

}

ResultScene::ResultScene(Scene::ResultType type) :
	m_commandList(),
	m_selectCommandIndex(0),
	m_resultLogo(-1)
{

	switch (type)
	{
	case Scene::ResultType::Clear:
		m_resultLogo = LoadGraph(kClearLogo);
		SoundManager::GetInstance().PlayBGM(Sound::BGM::ClearScene);
		break;

	case Scene::ResultType::GameOver:
		m_resultLogo = LoadGraph(kGameOverLogo);
		SoundManager::GetInstance().PlayBGM(Sound::BGM::GameOverScene);
		break;

	default:
		m_resultLogo = LoadGraph(kClearLogo);

		assert(false && "");

		break;
	}

}

void ResultScene::Init()
{
	//フォントの読み込み
	int fontHandle = CreateFontToHandle(NULL, 40, 3, DX_FONTTYPE_EDGE);

	//Command::ToTitleの設定
	int toTitleIndex = static_cast<int>(Command::ToTitle);
	m_commandList[toTitleIndex].command = Command::ToTitle;
	m_commandList[toTitleIndex].fontHandle = fontHandle;
	m_commandList[toTitleIndex].message = "タイトルへ";
	//Command::RestartGameの設定
	int restartGameIndex = static_cast<int>(Command::RestartGame);
	m_commandList[restartGameIndex].command = Command::RestartGame;
	m_commandList[restartGameIndex].fontHandle = fontHandle;
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

		int posY = 400 + i * 50;
		if (i == m_selectCommandIndex) {
			//選択中のコマンドの表示
			DrawString(50, posY, "->", Color::kWhite);
		}
		//メッセージの表示
		DrawFormatStringToHandle(80, posY, Color::kWhite, m_commandList[i].fontHandle, m_commandList[i].message.c_str());

	}

}

void ResultScene::End()
{

	for (auto& commandData : m_commandList) {
		//フォントハンドルの破棄
		DeleteFontToHandle(commandData.fontHandle);
	}

}
