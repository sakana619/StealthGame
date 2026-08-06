#include "DxLib.h"
#include"System/GameSetting.h"
#include"System/Game.h"
#include"System/Time.h"
#include"../Scene/SceneManager.h"

//========================================================
// WinMain関数　ここからプログラムが始まる
//========================================================
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{

	GameSetting::InitWindow();

	if (DxLib_Init() == -1) {	// DXライブラリ初期化処理

		return -1;				// 初期化に失敗したら強制終了
	}

	// 描画先を裏面にセット
	SetDrawScreen(DX_SCREEN_BACK);

	GameSetting* pGameSet;
	pGameSet = new GameSetting;
	pGameSet->InitDxLib3D();

	SceneManager* pSceneMgr;
	pSceneMgr = new SceneManager();
	pSceneMgr->Init();

	Time::Init();

	// メインループ
	while (ProcessMessage() == 0) {

		LONGLONG time = GetNowHiPerformanceCount();

		Time::Update();

		ClearDrawScreen();		// 画面の初期化
		clsDx();				// デバッグ文字の初期化

		printfDx("FPS %f\n", Time::GetFPS());
		printfDx("deltaTime %f\n", Time::GetDeltaTime());

		pSceneMgr->Update();
		pSceneMgr->Draw();

		// 描画先を切り替える
		ScreenFlip();

		// FPS調整
		// 1フレームあたりの経過時間が経過するため待機
		while (GetNowHiPerformanceCount() - time < Time::GetoneFramePerMicrosec()) {

		}

	}

	pSceneMgr->End();

	DxLib_End();				// DXライブラリの終了処理
	return 0;					// ソフトの終了 

}
