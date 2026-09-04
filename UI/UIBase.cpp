#include "UIBase.h"

UIBase::UIBase() :
	m_handle(-1),
	m_isVisible(true)
{
}

UIBase::UIBase(int handle) :
	m_handle(handle),
	m_isVisible(true)
{
}
