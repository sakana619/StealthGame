#pragma once

class SceneBase
{

public:

	SceneBase();

	virtual ~SceneBase() = default;

	virtual void Init() = 0;

	virtual SceneBase* Update() { return this; }

	virtual void Draw() = 0;

	virtual void End() = 0;

};

