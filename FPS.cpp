﻿//-----------------------------------------------------------------------------//
//          リファクタリング：未                  チェック：未
//-----------------------------------------------------------------------------//

#include "common.h"
#include "FPS.h"

//-----------------------------------------------------------------------------//
//								コンストラクタ
//-----------------------------------------------------------------------------//
FPS::FPS()
{
	fpsCountStartTime = 0;
	fpsCount = 0;
    fps = 0;
}

//-----------------------------------------------------------------------------//
//								デストラクタ
//-----------------------------------------------------------------------------//
FPS::~FPS()
{
}

//-----------------------------------------------------------------------------//
//								アップデート処理
//-----------------------------------------------------------------------------//
void FPS::Update()
{
    //1フレーム目なら時刻を記憶
    if (fpsCount == 0)
    {
		fpsCountStartTime = GetNowCount();								//基準となる時間を決める
    }
    //60フレーム目なら平均を計算する
    if (fpsCount == tmp)
    {
        int nowTime = GetNowCount();									//今の時間を設定
        fps = 1000.f / ((nowTime - fpsCountStartTime) / (float)tmp);	//１フレームにかかった時間を計算
		fpsCount = 0;													//フレームのカウントを初期化
    }
	else
	{
		fpsCount++;
	}
}

//-----------------------------------------------------------------------------//
//								待機処理
//-----------------------------------------------------------------------------//
void FPS::Wait()
{
    int tookTime = GetNowCount() - fpsCountStartTime;					//かかった時間
    int waitTime = fpsCount * 1000 / setFps - tookTime;					//待つべき時間
    if (waitTime > 0)
    {
        Sleep(waitTime);												//待つべき時間待機する
    }
}