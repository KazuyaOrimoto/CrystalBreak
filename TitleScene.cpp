﻿//-----------------------------------------------------------------------------//
//			リファクタリング：未					チェック：未
//-----------------------------------------------------------------------------//

#include "Common.h"
#include "SceneBase.h"
#include "TitleScene.h"
#include "InputManager.h"
#include "FileManager.h"
#include "PlayScene.h"
#include "Sky.h"
#include "EffectCreater.h"
#include "TutorialScene.h"

//-----------------------------------------------------------------------------//
//								コンストラクタ
//-----------------------------------------------------------------------------//
TitleScene::TitleScene()
{
    inputManager = InputManager::GetInstance();
    fileManager = FileManager::GetInstance();
    titleBackGroundGraph = fileManager->GetTitleImage();
    pushGraph = fileManager->GetPushImage();
    demoPlayMovie = fileManager->GetDemoPlayMovie();
    changingOpacityValue = 1;
    SceneChangeFlag = false;
    playMovie = false;
    playcount = 0;
    opacity = 0;
}

//-----------------------------------------------------------------------------//
//								デストラクタ
//-----------------------------------------------------------------------------//
TitleScene::~TitleScene()
{
    DeleteGraph(titleBackGroundGraph);
}

//-----------------------------------------------------------------------------//
//								アップデート処理
//-----------------------------------------------------------------------------//
SceneBase* TitleScene::Update()
{
    inputManager->Update();								//キーの入力情報の更新
    
    if (inputManager->PushStartButton())
    {
        return new TutorialScene();
    }
    
    GraphAnimation();									//画像のアニメーション
    
    needPlayingMovie = inputManager->PushAnyKey();
    
    if (needPlayingMovie)
    {
        PlayMovie();
    }
    else
    {
        playcount = 0;
    }
    
    return this;
}

//-----------------------------------------------------------------------------//
//								描画処理
//-----------------------------------------------------------------------------//
void TitleScene::Draw()
{
    if (playMovie)
    {
        DrawGraph(0,0, demoPlayMovie,FALSE);
    }
    else
    {
        SetDrawBlendMode(DX_BLENDMODE_ALPHA, ALPHA_MAX);
        DrawGraph(0, 0, titleBackGroundGraph, TRUE);
        SetDrawBlendMode(DX_BLENDMODE_ALPHA, ALPHA_MAX - opacity);
        DrawGraph(0, 0, pushGraph, TRUE);
    }
}

//-----------------------------------------------------------------------------//
//						画像のアニメーション処理
//-----------------------------------------------------------------------------//
void TitleScene::GraphAnimation()
{
    opacity += changingOpacityValue;
    bool switchFlag = (opacity < 0 || OPACITY_MAX < opacity);       //不透明度が0より小さいor上限より大きい
    if (switchFlag)
    {
        changingOpacityValue *= -1;
    }
}

//-----------------------------------------------------------------------------//
//						デモプレイ動画を流す
//-----------------------------------------------------------------------------//
void TitleScene::PlayMovie()
{
    playcount++;
    if (playcount > playMovieUpToTime)
    {
        playMovie = true;
    }
    else
    {
        playMovie = false;
    }
    
    if (playMovie)
    {
        PlayMovieToGraph(demoPlayMovie);
    }
    else
    {
        SeekMovieToGraph(demoPlayMovie, 0);                         //再生開始位置に戻す
    }
}
