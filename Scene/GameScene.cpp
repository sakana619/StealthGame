#include "GameScene.h"
#include<memory>

#include"../Camera/Camera.h"
#include"../System/Time.h"
#include"../World/GameObjectManager.h"
#include"../World/Chara/Player.h"
#include"../World/Chara/Enemy/EnemyBee.h"
#include"../World/Chara/Enemy/EnemyManager.h"
#include"../World/Map/Map.h"
#include"../World/Map/MapData.h"

GameScene::GameScene() :
	m_pPlayer(nullptr),
	m_pEnemyMgr(nullptr),
	m_pCamera(nullptr),
	m_pMap(nullptr)
{}

void GameScene::Init()
{
	m_pGameObjectMgr = std::make_unique<GameObjectManager>();
	m_pCamera = std::make_unique<Camera>();
	//m_pPlayer = std::make_unique<Player>(m_pCamera.get());
	m_pPlayer = m_pGameObjectMgr->CreateObject<Player>(m_pCamera.get());
	m_pEnemyMgr = std::make_unique<EnemyManager>();
	m_pMap = std::make_unique<Map>();

	m_pCamera->Init();
	m_pEnemyMgr->Init(m_pGameObjectMgr.get());
	m_pMap->Init();

	m_pPlayer->SetEnemyManager(m_pEnemyMgr.get());
	m_pEnemyMgr->SetTargetPos(&m_pPlayer->GetPosition());

}

SceneBase* GameScene::Update()
{

	float deltaTime = Time::GetDeltaTime();

	m_pPlayer->Update(deltaTime);
	m_pCamera->SetTargetPos(m_pPlayer->GetPosition());
	m_pCamera->Update();

	m_pEnemyMgr->Update(deltaTime);

	m_pGameObjectMgr->CheckCollision();
	m_pGameObjectMgr->CheckAttackCollision();
	m_pMap->CheckHitMap(m_pGameObjectMgr.get());

	return nullptr;
}

void GameScene::Draw()
{

	VECTOR pos1;
	VECTOR pos2;

	float kLineAreaSize = 10000;
	float kLineNum = 50;

	pos1 = VGet(-kLineAreaSize / 2.0f, 0.0f, -kLineAreaSize / 2.0f);
	pos2 = VGet(-kLineAreaSize / 2.0f, 0.0f, kLineAreaSize / 2.0f);

	for (int i = 0; i < kLineNum; i++)
	{
		//DrawLine3D(pos1, pos2, 0xffffff);
		pos1.x += kLineAreaSize / static_cast<float>(kLineNum);
		pos2.x += kLineAreaSize / static_cast<float>(kLineNum);
	}

	pos1 = VGet(-kLineAreaSize / 2.0f, 0.0f, -kLineAreaSize / 2.0f);
	pos2 = VGet(kLineAreaSize / 2.0f, 0.0f, -kLineAreaSize / 2.0f);

	for (int i = 0; i < kLineNum; i++)
	{
		//DrawLine3D(pos1, pos2, 0xffffff);
		pos1.z += kLineAreaSize / static_cast<float>(kLineNum);
		pos2.z += kLineAreaSize / static_cast<float>(kLineNum);
	}

	m_pMap->Draw();
	m_pGameObjectMgr->Draw();

	printfDx("x : %f\n", m_pPlayer->GetPosition().x);
	printfDx("y : %f\n", m_pPlayer->GetPosition().y);
	printfDx("z : %f\n", m_pPlayer->GetPosition().z);

}

void GameScene::End()
{
	m_pPlayer->End();
	m_pEnemyMgr->End();
	m_pCamera->End();
	m_pMap->End();

	m_pGameObjectMgr->End();

}
