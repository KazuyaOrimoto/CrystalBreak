//-----------------------------------------------------------------------------//
//          リファクタリング：未                  チェック：未
//-----------------------------------------------------------------------------//
#include "Common.h"
#include "SceneBase.h"
#include "ResultScene.h"
#include "InputManager.h"
#include "TitleScene.h"

ResultScene::ResultScene(int score, int height)
	:score(score), height(height)
{
	inputManager = InputManager::GetInstance();
	resultGraph = LoadGraph("Texture/ResultScene.png");
	SetFontSize(200);
	sumScore = score + height;
	LoadDivGraph("Texture/Number_40.png", 10, 10, 1, 108, 123, numberGraph40);
	LoadDivGraph("Texture/Number_48.png", 10, 10, 1, 130, 148, numberGraph48);
	previewScore = 0;
	previewHeight = 0;
	previewSumScore = 0;
	drawEnd = false;
}

ResultScene::~ResultScene()
{
}

SceneBase * ResultScene::Update()
{
	inputManager->Update();

	if (!drawEnd)
	{
		if (score != previewScore)
		{
			int distance = score - previewScore;
			if (123 < distance)
			{
				previewScore += 123;
			}
			else
			{
				previewScore += distance;
			}
		}
		else if (height != previewHeight)
		{
			int distance = height - previewHeight;
			if (123 < distance)
			{
				previewHeight += 123;
			}
			else
			{
				previewHeight += distance;
			}
		}
		else if (sumScore != previewSumScore)
		{
			int distance = sumScore - previewSumScore;
			if (1237 < distance)
			{
				previewSumScore += 357;
			}
			else
			{
				previewSumScore += distance;
			}
		}
		else
		{
			drawEnd = true;
		}
	}
	else
	{
		if (inputManager->PushStartButton())
		{
			return new TitleScene();
		}
	}

	return this;
}

void ResultScene::Draw()
{
	DrawGraph(0, 0, resultGraph, FALSE);
	DrawNumber(numberGraph40, 1215, 350, previewScore, 5);
	DrawNumber(numberGraph40, 1215, 550, previewHeight, 5);
	DrawNumber(numberGraph48, 1100, 793, previewSumScore, 6);
}

void ResultScene::DrawNumber(int graphHandle[], int x, int y, int number, int length)
{
	int drawCount = 0;
	int sizeX, sizeY;
	GetGraphSize(graphHandle[0], &sizeX, &sizeY);
	drawCount = (int)log10(number) + 1;
	int zeroDrawCount = length - (drawCount);
	for (int i = length; i > 0; i--)
	{
		if (zeroDrawCount)
		{
			zeroDrawCount--;
			DrawGraph(x + (sizeX * (length - i)), y, graphHandle[0], TRUE);
		}
		else
		{
			int num = number;
			for (int j = 0; j < i; j++)
			{
				if (j != i - 1)
				{
					num /= 10;
				}
				else
				{
					num %= 10;
				}
			}
			DrawGraph(x + (sizeX * (length - i)), y, graphHandle[num], TRUE);
			drawCount--;
		}
	}
}
