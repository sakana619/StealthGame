#include "TitleScene.h"
#include"SceneBase.h"

#include<DxLib.h>
#include"GameScene.h"

namespace {

	const char* const kTitleLogoPath = "";

}

TitleScene::TitleScene() :
	m_titleLogo(-1)
{
}

void TitleScene::Init()
{
}

SceneBase* TitleScene::Update()
{

	if (CheckHitKeyAll()) {
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
