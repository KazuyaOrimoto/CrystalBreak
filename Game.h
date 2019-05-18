//-----------------------------------------------------------------------------//
//			リファクタリング：済					チェック：済
//-----------------------------------------------------------------------------//

#pragma once

class FPS;
class SceneBase;

/**
    @brief  ゲーム全体をまとめるクラス
*/
class Game
{
public:
    Game();
    ~Game();
/**
    @brief  ゲームのループを回す
*/
    void GameLoop();

private:
/**
    @brief  ゲームの継続判定
    @return true:継続、false:終了
*/
    bool IsContinueGame();

/**
    @brief  シーンを変更
*/
	void SceneChange();	

    FPS         *fps;                       //FPSクラスのポインタ
    SceneBase   *nowScene, *nextScene;      //シーンクラスのポインタ
};
