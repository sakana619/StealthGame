#include "SceneManager.h"
#include<cassert>

#include"DxLib.h"
#include"GameScene.h"
#include"ResultScene.h"
#include"TitleScene.h"
#include"SceneBase.h"
#include"../System/Game.h"
#include"../System/SoundManager.h"
#include"../System/Time.h"
#include"../Utility/Color.h"
#include"../Utility/FadeManager.h"
#include"../Utility/Input.h"

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
	m_pScene = new ResultScene(Scene::ResultType::Clear);
	//m_pScene = new TitleScene();

	//BGMの読み込み
	//SoundManager::GetInstance().Init();

	assert(m_pScene);
	//シーンの初期化
	m_pScene->Init();

}

void SceneManager::Update()
{
	//経過時間を取得
	float deltaTime = Time::GetDeltaTime();

	//入力情報の更新
	Input::Update();

	//シーンの切り替え、更新
	SceneBase* pScene = m_pScene->Update(deltaTime);

	//現在のシーンと違って次のシーンがなかったらtrue
	bool isSceneChange = m_pScene != pScene && pScene != nullptr && m_pNextScene == nullptr;

	//シーンが切り替わっていたら
	if (isSceneChange) {
		//次のシーンを設定
		m_pNextScene = pScene;
		//フェードアウトの開始
		FadeManager::GetInstance().StartFadeOut(1.0f, Color::kBlack);

	}
	//フェード処理の更新
	FadeManager::GetInstance().Update(deltaTime);

	//BGMフェードの更新
	SoundManager::GetInstance().UpdateFade(deltaTime);

	//次のシーンがあってフェードアウトが終わっていれば
	if (m_pNextScene && !FadeManager::GetInstance().IsFadingOut()) {

		//終了
		m_pScene->End();
		delete m_pScene;
		//シーンの切り替え
		m_pScene = m_pNextScene;
		//リセット
		m_pNextScene = nullptr;
		//初期化
		m_pScene->Init();

	}

}

void SceneManager::Draw()
{
	//シーンの描画
	m_pScene->Draw();
	//フェードの描画
	FadeManager::GetInstance().Draw();
}

void SceneManager::End()
{
	//シーンの破棄
	m_pScene->End();
	delete m_pScene;
	m_pScene = nullptr;

	if (m_pNextScene) {
		m_pNextScene->End();
		m_pNextScene = nullptr;
	}

	delete m_pNextScene;

	//サウンドの破棄
	SoundManager::GetInstance().End();

}
