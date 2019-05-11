//-----------------------------------------------------------------------------//
//						必要なライブラリのインクルード
//-----------------------------------------------------------------------------//
#include "Common.h"
#include "SceneBase.h"
#include "PlayScene.h"
#include "Camera.h"
#include "Stage.h"
#include "Player.h"
#include "EnemyList.h"
#include "ActionManager.h"
#include "Score.h"
#include "FireList.h"
#include "Collision.h"
#include "EffectCreater.h"
#include "Sky.h"
#include "SoundManager.h"
#include "Dark.h"
#include "InputManager.h"
#include "FileManager.h"
#include "PlaySceneUI.h"
#include "Timer.h"
#include "ResultScene.h"

//-----------------------------------------------------------------------------//
//								コンストラクタ
//-----------------------------------------------------------------------------//
PlayScene::PlayScene()
{
	soundManager		= SoundManager::GetInstance();
	inputManager		= InputManager::GetInstance();
	score				= Score::GetInstance();
	fileManager			= FileManager::GetInstance();
	actionManager		= new ActionManager();
	camera				= new Camera();
	stage				= new Stage();
	player				= new Player(*actionManager);
	enemy				= new EnemyList(*actionManager, *stage);
	fireList			= new FireList(*stage);
	collision			= new Collision();
	sky					= new Sky();
	dark				= new Dark();
	playSceneUI			= new PlaySceneUI();
	timer				= new Timer();
	gameEndFlag			= false;
	gameEndSount		= false;
	gameEndGraphLeft	= fileManager->GetGameEndLeftGraph();
	gameEndGraphRight	= fileManager->GetGameEndRightGraph();
	screenHandle		= MakeScreen(SCREEN_W, SCREEN_H, TRUE);
	score->InitScore();
	soundManager->PlayBGM();
}

//-----------------------------------------------------------------------------//
//								デストラクタ
//-----------------------------------------------------------------------------//
PlayScene::~PlayScene()
{
	delete(camera);
	delete(stage);
	delete(actionManager);
	delete(player);
	delete(enemy);
	delete(fireList);
	delete(collision);
	delete(sky);
	delete(dark);
	delete(playSceneUI);
	delete(timer);
	EffectCreater* effect = EffectCreater::GetInstance();
	effect->AllStopEffect();
}

//-----------------------------------------------------------------------------//
//								アップデート処理
//-----------------------------------------------------------------------------//
SceneBase* PlayScene::Update()
{
	if (stage->NeedNextStageCreate())
	{
		NextStageCreate();
	}

	if (gameEndFlag)
	{
		IsGameEndFlag();
		if (gameEndCount % reciprocalNumber == 0)
		{
			UpdateProcess();
		}
	}
	else
	{
		UpdateProcess();
		gameEndFlag = CheckGameEndFlag();
	}

	if (gameEndCount > timeUpToGameTermination)
	{
		return new ResultScene(playSceneUI->GetScore(), playSceneUI->GetHeight());
	}
	return this;
}

//-----------------------------------------------------------------------------//
//								描画処理
//-----------------------------------------------------------------------------//
void PlayScene::Draw()
{
	SetDrawScreen(screenHandle);
	ClearDrawScreen();
	camera->SetPosition();

	sky->Draw();
	stage->Draw();
	player->Draw();
	enemy->Draw();
	fireList->Draw();
	score->Draw();
	DrawEffekseer3D();
	dark->Draw();

	SetDrawScreen(DX_SCREEN_BACK);
	camera->SetPosition();
	DrawGraph(mainScreenPosX, 0, screenHandle, FALSE);

	playSceneUI->Draw();
	if (gameEndFlag)
	{
		DrawGameEndGraph();
	}
}

//-----------------------------------------------------------------------------//
//						それぞれのクラスのアップデート処理
//-----------------------------------------------------------------------------//
void PlayScene::UpdateProcess()
{
	inputManager->Update();
	sky->Update();
	stage->Update();
	player->Update(*stage, *camera, *actionManager, *inputManager);
	enemy->Update(*stage, *actionManager);
	fireList->Update(*stage);
	dark->Update(*player);
	camera->Update();
	collision->CheckCollisionAll(*fireList, *stage, *player, *enemy);
	timer->Update();
	playSceneUI->Update(*player, *timer);
	score->Update();
	UpdateEffekseer3D();
}

//-----------------------------------------------------------------------------//
//							ゲーム終了画像の描画
//-----------------------------------------------------------------------------//
void PlayScene::DrawGameEndGraph()
{
	const int HALF_SCREEN_SIZE_X = SCREEN_SIZE_X / 2;
	if (gameEndCount * slideRange < HALF_SCREEN_SIZE_X)
	{
		DrawGraph(-HALF_SCREEN_SIZE_X + gameEndCount * slideRange, gameEndGraphPosY, gameEndGraphLeft, TRUE);
		DrawGraph(HALF_SCREEN_SIZE_X - gameEndCount * slideRange, gameEndGraphPosY, gameEndGraphRight, TRUE);
	}
	else
	{
		DrawGraph(0, gameEndGraphPosY, gameEndGraphLeft, TRUE);
		DrawGraph(HALF_SCREEN_SIZE_X - 1, gameEndGraphPosY, gameEndGraphRight, TRUE);
	}
}

//-----------------------------------------------------------------------------//
//							次のステージを作る処理
//-----------------------------------------------------------------------------//
void PlayScene::NextStageCreate()
{
	stage->NextStageCreate();
	actionManager->EnemyDataClear();
	player->NextStageCreate();
	enemy->NextStageCreate(*stage, *actionManager);
	camera->NextStageCreate();
	dark->Start();
	delete(fireList);
	fireList = new FireList(*stage);
}

//-----------------------------------------------------------------------------//
//					ゲーム終了フラグが立っているときの処理
//-----------------------------------------------------------------------------//
void PlayScene::IsGameEndFlag()
{
	gameEndCount++;
	if (!gameEndSount)
	{
		soundManager->GameEndSound();
		gameEndSount = true;
	}
}

//-----------------------------------------------------------------------------//
//					ゲーム終了フラグが立っているか
//-----------------------------------------------------------------------------//
bool PlayScene::CheckGameEndFlag()
{
	if (player->CheckGameEnd())
	{
		score->GameEnd();
		return true;
	}
	if (timer->CheckGameEndFlag())
	{
		player->GameEnd();
		return true;
	}
	return false;
}
