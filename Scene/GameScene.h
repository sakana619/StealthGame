#pragma once
#include"../Scene/SceneBase.h"
#include<memory>

class Player;
class GameObjectManager;
class EnemyManager;
class Camera;
class Map;
class UIManager;

class GameScene :public SceneBase
{

public:

	GameScene();
	~GameScene()override = default;

	/// <summary>
	/// 初期化
	/// </summary>
	void Init();

	/// <summary>
	/// 更新処理
	/// </summary>
	/// <returns></returns>
	SceneBase* Update();

	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw();

	/// <summary>
	/// 終了処理
	/// </summary>
	void End();

private:

	/// <summary>
	/// UIの初期化
	/// </summary>
	void InitUI();

private:

	Player* m_pPlayer;

	/// <summary>
	/// ゲームオブジェクト管理クラス
	/// </summary>
	std::unique_ptr<GameObjectManager>m_pGameObjectMgr;

	/// <summary>
	/// 敵管理クラスのポインタ
	/// </summary>
	std::unique_ptr<EnemyManager>m_pEnemyMgr;
	/// <summary>
	/// カメラクラスのポインタ
	/// </summary>
	std::unique_ptr<Camera>m_pCamera;
	/// <summary>
	/// マップ管理クラスのポインタ
	/// </summary>
	std::unique_ptr<Map>m_pMap;
	/// <summary>
	/// UI管理クラス
	/// </summary>
	std::unique_ptr<UIManager>m_pUIMgr;

};
