#pragma once

#include"UIBase.h"

/// <summary>
/// ‰æ‘œ‚ÌUIƒNƒ‰ƒX
/// </summary>
class UIImage :UIBase
{

public:

	UIImage();
	UIImage(int graphHandle);
	~UIImage()override;

	void Init()override;
	void Draw()override;
	void End()override;

};
