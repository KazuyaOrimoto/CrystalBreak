//-----------------------------------------------------------------------------//
//          リファクタリング：済                  チェック：済
//-----------------------------------------------------------------------------//

#include "common.h"
#include "Game.h"
#include "SceneBase.h"
#include "FPS.h"
#include "Score.h"
#include "EffectCreater.h"
#include "SoundManager.h"
#include "FileManager.h"

Game::Game()
    : nowScene(NULL)
    , fps(NULL)
{
    Score           ::CreateInstance();                 //Scoreクラスのインスタンスを作成
    EffectCreater   ::CreateInstance();                 //EffectCreaterクラスのインスタンスを作成
    SoundManager    ::CreateInstance();                 //SoundManagerクラスのインスタンスを作成
    FileManager     ::CreateInstance();                 //FileManagerクラスのインスタンスを作成
	nowScene = SceneBase::InitScene();
	fps = new FPS();
}

Game::~Game()
{
    EffectCreater   ::DeleteInstance();                 //Scoreクラスのインスタンスを削除
    Score           ::DeleteInstance();                 //EffectCreaterクラスのインスタンスを削除
    SoundManager    ::DeleteInstance();                 //SoundManagerクラスのインスタンスを削除
    FileManager     ::DeleteInstance();                 //FileManagerクラスのインスタンスを削除
    delete(fps);
    delete(nowScene);
}

/**
	@brief  ゲームのループを回す
*/
void Game::GameLoop()
{
	while (IsContinueGame())
	{
        ClearDrawScreen();
        fps->Update();
        /*  現在のシーンのUpdateを実行後、次のシーンを一時保存    */
        nextScene = nowScene->Update();
        nowScene->Draw();
        fps->Wait();
        ScreenFlip();
        if (nowScene != nextScene)
        {
            SceneChange();
        }
	}
}

/**
	@brief  ゲームの継続判定
	@return true:継続、false:終了
*/
bool Game::IsContinueGame()
{
    if (ProcessMessage())
    {
        return false;
    }
    if (CheckHitKey(KEY_INPUT_ESCAPE))
    {
        return false;
    }
    return true;
}

/**
	@brief  シーンを変更
*/
void Game::SceneChange()
{
    delete(nowScene);
    nowScene = nextScene;
    nextScene = NULL;
}
