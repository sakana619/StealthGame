#pragma once

#include"UIBase.h"

/// <summary>
/// ‰æ‘œ‚ÌUIƒNƒ‰ƒX
/// </summary>
class UIImage :UIBase
{

public:

	UIImage();
	~UIImage();

	void Init()override;
	void Update(float deltaTime) {}
	void Draw()override;
	void End()override;

private:



};
