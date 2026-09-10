#pragma once
#include"UIBillboard.h"

/// <summary>
/// UŒ‚‰Â”\‚ğ’m‚ç‚¹‚éUI
/// </summary>
class CanAttackUI :UIBillboard
{

public:

	CanAttackUI();
	CanAttackUI(int graphHandle);
	~CanAttackUI()override;

	void Init()override;
	void Draw()override;
	void End()override;



};
