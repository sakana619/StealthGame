#pragma once

class SceneBase
{

public:

	SceneBase();

	virtual ~SceneBase() = default;

	virtual void Init() = 0;

	virtual SceneBase* Update(float deltaTime) { return this; }

	virtual void Draw() = 0;

	virtual void End() = 0;

protected:

	/// <summary>
	/// ƒV[ƒ“‚Ì‘JˆÚ‚ª‚ ‚é‚©”»’è
	/// </summary>
	bool m_isSceneChanging;

};

