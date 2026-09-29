#include "TitleScene.h"
#include"SceneBase.h"

#include<DxLib.h>
#include"GameScene.h"
#include"../System/SoundManager.h"
#include"../Utility/Color.h"
#include"../Utility/Input.h"

namespace {
	//タイトルロゴのファイルパス
	const char* const kTitleLogoPath = ".\\Resource\\UI\\TitleLogo.png";

	constexpr float kTitleLogoPosX = 400;
	constexpr float kTitleLogoPosY = 200;

	constexpr float kTitleLogoScale = 0.4f;

	//スタートのメッセージ
	const char* const kStartMessage = "スペースキーでスタート";

	constexpr float kMessagePosX = 120;
	constexpr float kMessagePosY = 400;

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
	m_messageFont = CreateFontToHandle(NULL, 50, 3, DX_FONTTYPE_EDGE);


	SoundManager::GetInstance().PlayBGM(Sound::BGM::TitleScene);

}

SceneBase* TitleScene::Update(float deltaTime)
{

	if (Input::IsPressed(PAD_INPUT_10)) {
		//決定音の再生
		SoundManager::GetInstance().PlaySe(Sound::SE::Decide);

		return new GameScene;
	}

	return this;

}

void TitleScene::Draw()
{
	//タイトルのロゴの描画
	DrawRotaGraph(kTitleLogoPosX, kTitleLogoPosY, kTitleLogoScale, 0.0f, m_titleLogo, TRUE);

	//メッセージの表示
	DrawFormatStringToHandle(kMessagePosX, kMessagePosY, Color::kWhite, m_messageFont, kStartMessage);

}

void TitleScene::End()
{
	//読み込んだロゴを破棄
	DeleteGraph(m_titleLogo);
	//読み込んだフォントを破棄
	DeleteFontToHandle(m_messageFont);

}
