#include "SoundManager.h"
#include<array>

#include"DxLib.h"
#include<cassert>
#include"../System/Game.h"

namespace {

    //SEのファイルパス

    //BGMのファイルパス
    const char* const kTitleBgmFilePath = "";
    const char* const kGameSceneBgmFilePath = "";
    const char* const kClearSceneBgmFilePath = "";
    const char* const kGameOverSceneBgmFilePath = "";

    //音量のデフォルト
    constexpr int kDefaultVolume = 160;

    //フェードの速度
    constexpr float kFadeSpeed = 120;

}

SoundManager::SoundManager() :
    m_bgmHandles(),
    m_seHandles(),
    m_isLoaded(false),
    m_currentVolume(kDefaultVolume),
    m_nextVolume(0),
    m_currentBgmHandle(-1),
    m_nextBgmHandle(-1),
    m_fadeState(FadeState::None)
{
    //初期化
    m_bgmHandles.fill(-1);
    //初期化
    m_seHandles.fill(-1);
}

SoundManager& SoundManager::GetInstance()
{
    //インスタンスを生成
    static SoundManager instance;

    return instance;

}

void SoundManager::Init()
{
    //読み込んでいたらスルー
    if (m_isLoaded)return;

    //音の読み込み
    LoadBgm();
    LoadSe();

    //読み込み完了
    m_isLoaded = true;

}

void SoundManager::End()
{
    //BGMの破棄
    for (auto& bgm : m_bgmHandles) {
        //BGMの破棄
        DeleteSoundMem(bgm);
        bgm = -1;
    }
    //SEの破棄
    for (auto& se : m_seHandles) {
        //SEの破棄
        DeleteSoundMem(se);
        se = -1;
    }

    m_isLoaded = false;

}

void SoundManager::PlayBGM(Sound::BGM bgm)
{

    int index = static_cast<int>(bgm);

    if (m_bgmHandles[index] == -1)return;

    //再生されていなかったらフェードイン
    if (m_currentBgmHandle == -1) {
        //BGMハンドルをセット
        m_currentBgmHandle = m_bgmHandles[index];

        //フェードインに入る
        StartFadeIn();

        return;
    }

    //次に再生するBGMをセット
    m_nextBgmHandle = m_bgmHandles[index];
    //次に再生するBGMの再生
    PlaySoundMem(m_nextBgmHandle, DX_PLAYTYPE_LOOP);

    //フェードアウトに入る
    m_fadeState = FadeState::CrossFade;

}

void SoundManager::StopBgm()
{
    //再生していなかったらスルー
    if (m_currentBgmHandle == -1)return;
    //BGMを停止
    StopSoundMem(m_currentBgmHandle);
    //再生されていない状態にする
    m_currentBgmHandle = -1;

}

void SoundManager::PlaySe(Sound::SE se)
{
    //SEの番号
    int index = static_cast<int>(se);

    //読み込みがされていなければリターン
    if (m_seHandles[index] == -1)return;

    //SEの再生
    PlaySoundMem(m_seHandles[index], DX_PLAYTYPE_BACK);

}

void SoundManager::UpdateFade(float deltaTime)
{

    if (m_fadeState == FadeState::None)return;

    switch (m_fadeState)
    {
    case SoundManager::FadeState::None:

        break;

    case SoundManager::FadeState::In:
        UpdateFadeIn(deltaTime);
        break;

    case SoundManager::FadeState::CrossFade:
        UpdateCrossFade(deltaTime);
        break;

    default:

        break;

    }

}

void SoundManager::LoadBgm()
{
    //BGMの読み込み
    m_bgmHandles[static_cast<int>(Sound::BGM::TitleScene)] = LoadSoundMem(kTitleBgmFilePath);
    m_bgmHandles[static_cast<int>(Sound::BGM::GameScene)] = LoadSoundMem(kGameSceneBgmFilePath);
    m_bgmHandles[static_cast<int>(Sound::BGM::ClearScene)] = LoadSoundMem(kClearSceneBgmFilePath);
    m_bgmHandles[static_cast<int>(Sound::BGM::GameOverScene)] = LoadSoundMem(kGameOverSceneBgmFilePath);

    //BGMの初期化
    for (auto& bgm : m_bgmHandles) {
        //読み込みが失敗していたら警告
        assert(bgm != -1);
        //音量の調整
        ChangeVolumeSoundMem(kDefaultVolume, bgm);

    }

}

void SoundManager::LoadSe()
{
    //SEの読み込み

    //SEの初期化
    for (auto& se : m_seHandles) {
        //読み込みが失敗していたら警告
        assert(se != -1);
        //音量の調整
        ChangeVolumeSoundMem(kDefaultVolume, se);
    }

}

void SoundManager::UpdateFadeIn(float deltaTime)
{

    //音量を少しずつ上げる
    m_currentVolume += kFadeSpeed * deltaTime;
    //音量を設定
    ChangeVolumeSoundMem(m_currentVolume, m_currentBgmHandle);

    //設定した音量になったら
    if (m_currentVolume >= kDefaultVolume) {
        //デフォルトの音量に設定する
        m_currentVolume = kDefaultVolume;
        //音量を設定
        ChangeVolumeSoundMem(m_currentVolume, m_currentBgmHandle);
        //フェード状態を変更
        m_fadeState = FadeState::None;

    }

}

void SoundManager::UpdateCrossFade(float deltaTime)
{
    //今のBGMを少しずつ下げる
    m_currentVolume -= kFadeSpeed * deltaTime;
    //次のBGMを少しずつ上げる
    m_nextVolume = kDefaultVolume - m_currentVolume;
    //音量を変更
    ChangeVolumeSoundMem(static_cast<int>(m_currentVolume), m_currentBgmHandle);
    ChangeVolumeSoundMem(static_cast<int>(m_nextVolume), m_nextBgmHandle);

    //音が0になったら
    if (m_currentVolume <= 0) {
        //古いBGMを停止
        StopSoundMem(m_currentBgmHandle);

        //次のBGMを現在BGMとしてセット
        m_currentBgmHandle = m_nextBgmHandle;
        m_nextBgmHandle = -1;

        //音量をデフォルトに設定
        m_currentVolume = kDefaultVolume;
        ChangeVolumeSoundMem(m_currentVolume, m_currentBgmHandle);
        //音量をリセット
        m_nextVolume = 0;

        //フェード状態を変更
        m_fadeState = FadeState::None; 

    }

}

void SoundManager::StartFadeIn()
{

    //音量を0にする
    m_currentVolume = 0;
    //音楽を再生
    PlaySoundMem(m_currentBgmHandle, DX_PLAYTYPE_LOOP);
    //フェードの状態を変更
    m_fadeState = FadeState::In;

}
