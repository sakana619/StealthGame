#include "UIImage.h"
#include"UIBase.h"

#include<DxLib.h>


UIImage::UIImage() :
	m_scale(1.0f),
	m_angleRad(0.0f)
{
}

UIImage::UIImage(int graphHandle) :
	UIBase(graphHandle),
	m_scale(1.0f),
	m_angleRad(0.0f)
{
}

UIImage::~UIImage()
{
}

void UIImage::Init()
{
}

void UIImage::Draw()
{

	DrawRotaGraph(m_position.x, m_position.y, m_scale, m_angleRad, m_handle, TRUE);

}

void UIImage::End()
{
	DeleteGraph(m_handle);
}
