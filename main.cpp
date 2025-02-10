#include <Novice.h>
#include "definition.h"
#include "GameManager.h"


const char kWindowTitle[] = "LC1A_24_ヨコヤマ_タダノブ_タイトル";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, WINDOW_WIDTH, WINDOW_HEIGHT);
	GameManager* gm = new GameManager;

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		//  更新処理ここから
		gm->Update();

		//  描画処理ここから
		gm->Draw();

		// R
		if (GetHitKey::keys[DIK_R])
		{
			delete gm;
			gm = new GameManager;
		}
		if (gm->scene == RESULT)
		{
			if (GetHitKey::keys[DIK_SPACE])
			{
				delete gm;
				gm = new GameManager;
			}
		}

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (GetHitKey::keys[DIK_ESCAPE] == 0 && GetHitKey::preKeys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	// ライブラリの終了
	delete gm;
	Novice::Finalize();
	return 0;
}
