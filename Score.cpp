//-----------------------------------------------------------------------------//
//          リファクタリング：未                  チェック：未
//-----------------------------------------------------------------------------//
#include "Common.h"
#include "Score.h"

Score* Score::score = NULL;

//-----------------------------------------------------------------------------//
//								インスタンスを渡す
//-----------------------------------------------------------------------------//
Score * Score::GetInstance()
{
	return score;
}

//-----------------------------------------------------------------------------//
//								インスタンスを作る
//-----------------------------------------------------------------------------//
void Score::CreateInstance()
{
	if (score == NULL)
	{
		score = new Score();
	}
}

//-----------------------------------------------------------------------------//
//								インスタンスを削除
//-----------------------------------------------------------------------------//
void Score::DeleteInstance()
{
	if (score != NULL)
	{
		delete(score);
	}
}

//-----------------------------------------------------------------------------//
//								アップデート処理
//-----------------------------------------------------------------------------//
void Score::Update()
{
	if (gameEndFlag)
	{
		scorePoint = earnScorePoint;
		height = earnHeight;
		return;
	}

}

//-----------------------------------------------------------------------------//
//								スコアを初期化
//-----------------------------------------------------------------------------//
void Score::InitScore()
{
	scorePoint = 0;
	height = 0;
	earnScorePoint = 0;
	earnHeight = 0;
	gameEndFlag = false;
}
//-----------------------------------------------------------------------------//
//								スコアを加算
//-----------------------------------------------------------------------------//
void Score::AddScore(int addScore)
{
	//ゲームの終了フラグが立ってるときはスコアの加算を受け付けない
	if (gameEndFlag)
	{
		return;
	}
	earnScorePoint += addScore;
}

void Score::AddHeight(int addHeight)
{
	//ゲームの終了フラグが立ってるときはスコアの加算を受け付けない
	if (gameEndFlag)
	{
		return;
	}
	earnHeight += addHeight;
}

//-----------------------------------------------------------------------------//
//								スコアを描画
//-----------------------------------------------------------------------------//
void Score::Draw()
{
}

//-----------------------------------------------------------------------------//
//								コンストラクタ
//-----------------------------------------------------------------------------//
Score::Score()
{
}

//-----------------------------------------------------------------------------//
//								デストラクタ
//-----------------------------------------------------------------------------//
Score::~Score()
{
}

void Score::scoreAnimation()
{
	//早いアニメーションを開始する数値
	const int fastAnimation = 400;
	//早いアニメーションをする際に加算する値
	const int fastAnimationNum = 7;
	//通常時のアニメーションをする際に加算する値
	const int normalAnimationNum = 3;

	//表示しているスコアと獲得スコアが一致しないとき
	if (scorePoint != earnScorePoint)
	{
		int pointDifference = earnScorePoint - scorePoint;		//表示しているスコアと獲得スコアの差を計算
		if (pointDifference >= fastAnimation)
		{
			scorePoint += fastAnimationNum;
		}
		else
		{
			if (pointDifference > normalAnimationNum)
			{
				scorePoint += normalAnimationNum;
			}
			else
			{
				scorePoint += pointDifference;
			}
		}
	}

	//表示しているスコアと獲得スコアが一致しないとき
	if (height != earnHeight)
	{
		int heightDifference = earnHeight - height;				//表示しているスコアと獲得スコアの差を計算
		if (heightDifference >= fastAnimation)
		{
			height += fastAnimationNum;
		}
		else
		{
			if (heightDifference > normalAnimationNum)
			{
				height += normalAnimationNum;
			}
			else
			{
				height += heightDifference;
			}
		}
	}
}
