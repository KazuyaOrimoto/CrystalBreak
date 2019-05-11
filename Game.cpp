//-----------------------------------------------------------------------------//
//			リファクタリング：済					チェック：済
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
	:nowScene(SceneBase::InitScene())
	, fps(new FPS())
{
	Score			::CreateInstance();					//Scoreクラスのインスタンスを作成
	EffectCreater	::CreateInstance();					//EffectCreaterクラスのインスタンスを作成
	SoundManager	::CreateInstance();					//SoundManagerクラスのインスタンスを作成
	FileManager		::CreateInstance();					//FileManagerクラスのインスタンスを作成
}

Game::~Game()
{
	EffectCreater	::DeleteInstance();					//Scoreクラスのインスタンスを削除
	Score			::DeleteInstance();					//EffectCreaterクラスのインスタンスを削除
	SoundManager	::DeleteInstance();					//SoundManagerクラスのインスタンスを削除
	FileManager		::DeleteInstance();					//FileManagerクラスのインスタンスを削除
	delete(fps);
	delete(nowScene);
}

void Game::GameLoop()
{
	while (IsContinueGame())
	{
		ClearDrawScreen();
		fps->Update();
		/*	現在のシーンのUpdateを実行後、次のシーンを一時保存	*/
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

void Game::SceneChange()
{
	delete(nowScene);
	nowScene = nextScene;
	nextScene = NULL;
}
