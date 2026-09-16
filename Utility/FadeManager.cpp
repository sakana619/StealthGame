#include "FadeManager.h"
#include"Color.h"

#include<DxLib.h>
#include"MyMath.h"
#include"../System/Game.h"

FadeManager::FadeManager() :
	m_color(Color::kBlack),
	m_bright(0),
	m_speed(0.0f),
	m_durationSec(0.0f),
	m_isFading(false)
{
}

FadeManager& FadeManager::GetInstance()
{
	static FadeManager instance;
	return instance;
}

void FadeManager::Update(float deltaTime)
{
	//フェード中でなければ処理しない
	if (!m_isFading)return;

	//明るさの更新
	m_bright += m_speed * deltaTime;

	//フェードの終了判定
	if (m_bright > 255) {
		//リセット
		m_isFading = false;
		m_speed = 0;

		StartFadeIn(m_durationSec, m_color);

	}
	else if (m_bright < 0) {
		//リセット
		m_isFading = false;
		m_speed = 0;

		m_bright = 0;

	}

}

void FadeManager::Draw()
{
	//フェード中でなければ処理しない
	if (!m_isFading)return;

	//透明度を有効にする
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_bright);
	//画面全体にフェードを描画
	DrawBox(0, 0, Game::kScreenWidth, Game::kScreenHeight, m_color, true);
	//描画が終わったらノーブレンドに戻す
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

}

void FadeManager::StartFadeIn(float durationSec, int color)
{
	//設定
	m_color = color;
	m_speed = 255 / durationSec;
	m_speed = -m_speed;
	m_durationSec = durationSec;
	m_isFading = true;

	//明るさを設定
	m_bright = 255;

}

void FadeManager::StartFadeOut(float durationSec, int color)
{
	//設定
	m_color = color;
	m_speed = 255 / durationSec;
	m_durationSec = durationSec;
	m_isFading = true;

	//明るさを設定
	m_bright = 0;

}
