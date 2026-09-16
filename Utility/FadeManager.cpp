#include "FadeManager.h"
#include"Color.h"


FadeManager& FadeManager::GetInstance() 
{

	static FadeManager instance;
	return instance;
}

FadeManager::FadeManager()
{
}

void FadeManager::StartFadeIn(float duration, int color)
{
}

void FadeManager::StartFadeOut(float duration, int color)
{
}

bool FadeManager::IsFading() const
{
	return false;
}
