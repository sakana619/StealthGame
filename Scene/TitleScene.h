#pragma once
#include"SceneBase.h"

/// <summary>
/// タイトルシーン
/// </summary>
class TitleScene :public SceneBase
{

public:

	TitleScene();
	~TitleScene() = default;

	void Init()override;
	SceneBase* Update(float deltaTime)override;
	void Draw()override;
	void End()override;

private:


	int m_titleLogo;

};
