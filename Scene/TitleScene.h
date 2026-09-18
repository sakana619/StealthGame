#pragma once
#include"SceneBase.h"

/// <summary>
/// タイトルシーン
/// </summary>
class TitleScene :public SceneBase
{

public:

	TitleScene();
	~TitleScene()override = default;

	void Init()override;
	SceneBase* Update(float deltaTime)override;
	void Draw()override;
	void End()override;

private:

	/// <summary>
	/// タイトルロゴ
	/// </summary>
	int m_titleLogo;

	/// <summary>
	/// メッセージフォント
	/// </summary>
	int m_messageFont;

};
