#include "UIBase.h"
#include"../Utility/Vector3.h"

UIBase::UIBase() :
	m_handle(-1),
	m_isVisible(true),
	m_scale(1.0f),
	m_angleRad(0.0f)
{
}

UIBase::UIBase(int handle) :
	m_handle(handle),
	m_isVisible(true),
	m_scale(1.0f),
	m_angleRad(0.0f)
{
}
