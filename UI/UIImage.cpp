#include "UIImage.h"
#include"UIBase.h"

#include<DxLib.h>


UIImage::UIImage()
{
}

UIImage::UIImage(int graphHandle) :
	UIBase(graphHandle)
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
