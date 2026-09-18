#include "TitleScene.h"
#include"SceneBase.h"

#include<DxLib.h>
#include"GameScene.h"
#include"../System/SoundManager.h"
#include"../Utility/Color.h"
#include"../Utility/Input.h"

namespace {
	//タイトルロゴのファイルパス
	const char* const kTitleLogoPath = "";

	//スタートのメッセージ
	const char* const kStartMessage = "スペースキーでスタート";

}

TitleScene::TitleScene() :
	m_titleLogo(-1),
	m_messageFont(-1)
{
}

void TitleScene::Init()
{

	//ウィンドウの名前を変える
	SetMainWindowText("TitleScene");

	//タイトルロゴの読み込み
	m_titleLogo = LoadGraph(kTitleLogoPath);

	//メッセージのフォントの読み込み


}

SceneBase* TitleScene::Update(float deltaTime)
{

	if (Input::IsPressed(PAD_INPUT_10)) {
		return new GameScene;
	}

	return this;

}

void TitleScene::Draw()
{
}

void TitleScene::End()
{
}
