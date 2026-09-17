#pragma once
#include"SceneBase.h"

/// <summary>
/// ゲームオーバーシーン
/// </summary>
class GameClearScene :public SceneBase
{

public:

	GameClearScene();
	~GameClearScene()override = default;

	void Init()override;
	SceneBase* Update(float deltaTime)override;
	void Draw()override;
	void End()override;

private:

};
