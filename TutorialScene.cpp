//-----------------------------------------------------------------------------//
//          リファクタリング：未                  チェック：未
//-----------------------------------------------------------------------------//

#include "Common.h"
#include "SceneBase.h"
#include "TitleScene.h"
#include "InputManager.h"
#include "FileManager.h"
#include "PlayScene.h"
#include "TutorialScene.h"

//-----------------------------------------------------------------------------//
//								コンストラクタ
//-----------------------------------------------------------------------------//
TutorialScene::TutorialScene()
{
	inputManager	= InputManager::GetInstance();
	fileManager		= FileManager::GetInstance();
	tutorialGraph1	= fileManager->GetTutorialGraph1();
	tutorialGraph2	= fileManager->GetTutorialGraph2();
	nextGraph		= fileManager->GetNextGraph();
	wasPushStartButton = true;
	needChangeTutorialGraph = true;
	opacity = 0;
	changingOpacityValue = 1;
}

//-----------------------------------------------------------------------------//
//								デストラクタ
//-----------------------------------------------------------------------------//
TutorialScene::~TutorialScene()
{
}

//-----------------------------------------------------------------------------//
//								アップデート処理
//-----------------------------------------------------------------------------//
SceneBase * TutorialScene::Update()
{
	inputManager->Update();						//キーの入力情報の更新

	bool needChangeGraph = inputManager->PushStartButton() && !wasPushStartButton;

	if (needChangeGraph)
	{
		//チュートリアル画像を変える必要があるなら
		if (needChangeTutorialGraph)
		{
			wasPushStartButton = true;
			needChangeTutorialGraph = false;
		}
		else
		{
			return new PlayScene();
		}
	}
	else if(!inputManager->PushStartButton())
	{
		wasPushStartButton = false;
	}
	
	return this;
}

//-----------------------------------------------------------------------------//
//								描画処理
//-----------------------------------------------------------------------------//
void TutorialScene::Draw()
{
	//通常の描画
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, ALPHA_MAX);
	if (needChangeTutorialGraph)
	{
		DrawGraph(0, 0, tutorialGraph1, TRUE);
	}
	else
	{
		DrawGraph(0, 0, tutorialGraph2, TRUE);
	}

	//透明度の違う描画
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, ALPHA_MAX - opacity);
	DrawGraph(0, 0, nextGraph, TRUE);
}

//-----------------------------------------------------------------------------//
//						画像のアニメーション処理
//-----------------------------------------------------------------------------//
void TutorialScene::GraphAnimation()
{
	opacity += changingOpacityValue;
	bool switchFlag = (opacity < 0 || OPACITY_MAX < opacity);		//不透明度が0より小さいor上限より大きい
	if (switchFlag)
	{
		changingOpacityValue *= -1;
	}
}
