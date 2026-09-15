#include "SceneManager.h"
#include<cassert>

#include"DxLib.h"
#include"../System/Game.h"
#include"GameScene.h"
#include"TitleScene.h"
#include"SceneBase.h"

SceneManager::SceneManager() :
	m_pScene(nullptr),
	m_pNextScene(nullptr)
{
}

SceneManager::~SceneManager()
{
	delete m_pScene;
}

void SceneManager::Init()
{

	//m_pScene = new GameScene();
	m_pScene = new TitleScene();

	assert(m_pScene);
	//シーンの初期化
	m_pScene->Init();

}

void SceneManager::Update()
{

	//シーンの切り替え、更新
	SceneBase* pScene = m_pScene->Update();

	//シーンが切り替わっていたら
	if (m_pScene != pScene && pScene != nullptr) {

		//終了
		m_pScene->End();
		delete m_pScene;

		m_pScene = pScene;
		m_pScene->Init();

	}

}

void SceneManager::Draw()
{
	//シーンの描画
	m_pScene->Draw();

}

void SceneManager::End()
{

	m_pScene->End();
	delete m_pScene;
	m_pScene = nullptr;

}
