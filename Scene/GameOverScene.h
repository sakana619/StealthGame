#pragma once
#include"SceneBase.h"

/// <summary>
/// ゲームオーバーシーン
/// </summary>
class GameOverScene :public SceneBase
{

public:

	GameOverScene();
	~GameOverScene()override = default;

	void Init()override;
	SceneBase* Update(float deltaTime)override;
	void Draw()override;
	void End()override;

private:

};
