//-----------------------------------------------------------------------------//
//          リファクタリング：済                  チェック：済
//-----------------------------------------------------------------------------//

#include "Common.h"
#include "Game.h"

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	/*                  初期設定                        */
	ChangeWindowMode(TRUE);                                     //ウィンドウモード：TRUE、フルスクリーン：FALSE
	DxLib_Init();                                               //ライブラリの初期化
	SetGraphMode(SCREEN_SIZE_X, SCREEN_SIZE_Y, COLOR_BIT);      //画面解像度とカラービット数の設定
	SetDrawScreen(DX_SCREEN_BACK);                              //裏の画面にグラフィック領域を指定

	/*                  ゲームの処理                    */
	Game* game = new Game();									//ゲームに使用するメモリの割り当て
	game->GameLoop();                                           //ゲームを開始
	delete(game);                                               //ゲームに使用したメモリの開放

	/*                  終了処理                        */
	DxLib_End();                                                //ライブラリの使用を終了
	return 0;
}
