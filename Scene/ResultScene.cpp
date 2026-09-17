#include "ResultScene.h"
#include"SceneBase.h"

#include<DxLib.h>
#include"../Utility/Color.h"

namespace {



}

ResultScene::ResultScene(Scene::ResultType):
	m_commandList(),
	m_selectCommandIndex(0)
{
}

void ResultScene::Init()
{
}

SceneBase* ResultScene::Update(float deltaTime)
{
	return nullptr;
}

void ResultScene::Draw()
{

	DrawString(30, 30, "ResultScene", Color::kWhite);

}

void ResultScene::End()
{
}
