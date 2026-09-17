#include "GameScene.h"
#include<memory>

#include"../Camera/Camera.h"
#include"../Scene/ResultScene.h"
#include"../System/Time.h"
#include"../UI/UIBillboard.h"
#include"../UI/UIManager.h"
#include"../World/GameObjectManager.h"
#include"../World/Chara/Player.h"
#include"../World/Chara/Enemy/EnemyBee.h"
#include"../World/Chara/Enemy/EnemyManager.h"
#include"../World/Map/Map.h"

GameScene::GameScene() :
	m_pPlayer(nullptr),
	m_pEnemyMgr(nullptr),
	m_pCamera(nullptr),
	m_pMap(nullptr),
	m_pUIMgr(nullptr)
{
}

void GameScene::Init()
{
	//インスタンスを生成
	m_pGameObjectMgr = std::make_unique<GameObjectManager>();
	m_pCamera = std::make_unique<Camera>();
	m_pPlayer = m_pGameObjectMgr->CreateObject<Player>(m_pCamera.get());
	m_pEnemyMgr = std::make_unique<EnemyManager>();
	m_pMap = std::make_unique<Map>();
	m_pUIMgr = std::make_unique<UIManager>();

	//初期化
	m_pCamera->Init();
	m_pEnemyMgr->Init(m_pGameObjectMgr.get());
	m_pMap->Init();

	m_pPlayer->SetEnemyManager(m_pEnemyMgr.get());
	m_pEnemyMgr->SetTargetPos(&m_pPlayer->GetPosition());

	//UIの初期化
	InitUI();

}

SceneBase* GameScene::Update(float deltaTime)
{

	m_pGameObjectMgr->Update(deltaTime);

	m_pCamera->SetTargetPos(m_pPlayer->GetPosition());
	m_pCamera->Update();

	if (m_pMap->IsGoal(m_pPlayer)) {

	}

	if (m_pPlayer->IsFInishedDeadAnimation()) {

	}

	m_pGameObjectMgr->CheckCollision();
	m_pGameObjectMgr->CheckAttackCollision();
	m_pMap->CheckHitMap(m_pGameObjectMgr.get());
	m_pUIMgr->Update(deltaTime);

	return this;
}

void GameScene::Draw()
{

	m_pMap->Draw();
	m_pGameObjectMgr->Draw();
	m_pUIMgr->Draw();

}

void GameScene::End()
{

	m_pCamera->End();
	m_pMap->End();
	m_pUIMgr->End();

	m_pGameObjectMgr->End();

}

void GameScene::InitUI()
{

	m_pUIMgr->Init();

	int attackUIGraph = LoadGraph(".\\Resource\\UI\\ImageNameHere.png");

	UIBillboard* attackUI = m_pUIMgr->CreateUI<UIBillboard>(attackUIGraph);
	attackUI->SetDrawCenterY(-1.0f);
	attackUI->SetScale(70);

	m_pPlayer->SetCanAttackUI(attackUI);

}
