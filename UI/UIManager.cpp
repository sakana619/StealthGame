#include "UIManager.h"
#include<vector>
#include<memory>
#include<type_traits>

#include"UIBase.h"

UIManager::UIManager()
{
}

UIManager::~UIManager()
{
}

void UIManager::Init()
{

}

void UIManager::Update(float deltaTime)
{

	for (const auto& ui : m_UIList) {
		ui->Update(deltaTime);
	}

}

void UIManager::Draw()
{

	for (const auto& ui : m_UIList) {
		if (!ui->GetIsVisible())continue;
		ui->Draw();
	}

}

void UIManager::End()
{

	for (const auto& ui : m_UIList) {
		ui->End();
	}

}
