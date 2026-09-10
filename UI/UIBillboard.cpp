#include "UIBillboard.h"
#include"UIBase.h"

#include<DxLib.h>

UIBillboard::UIBillboard() :
	m_drawCenterX(0.5f),
	m_drawCenterY(0.5f)
{
}

UIBillboard::UIBillboard(int graphHandle) :
	UIBase(graphHandle),
	m_drawCenterX(0.5f),
	m_drawCenterY(0.5f)
{
}

UIBillboard::~UIBillboard()
{
}

void UIBillboard::Init()
{
}

void UIBillboard::Draw()
{

	DrawBillboard3D(m_position.ToVECTOR(), m_drawCenterY, m_drawCenterY, m_scale, m_angleRad, m_handle, TRUE);

}

void UIBillboard::End()
{
}
