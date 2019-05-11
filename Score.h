#pragma once

class Score
{
public:
	//-----------------------------------------------------------------------------//
	//							パブリック関数
	//-----------------------------------------------------------------------------//
	static Score* GetInstance();					//インスタンスを渡す
	static void CreateInstance();					//インスタンス作成
	static void DeleteInstance();
	void Update();
	void InitScore();								//スコアを初期化
	void AddScore(int addScore);					//スコアを加算
	void AddHeight(int addHeight);
	void Draw();
	int GetScore() { return scorePoint; }
	int GetHeight() { return height; }
	void GameEnd(){gameEndFlag = true;}
private:
	//-----------------------------------------------------------------------------//
	//							プライベート関数
	//-----------------------------------------------------------------------------//
	Score();
	~Score();
	void scoreAnimation();							//スコアのカウントアップアニメーション処理関数
	//-----------------------------------------------------------------------------//
	//							プライベート変数
	//-----------------------------------------------------------------------------//
	static Score* score;							//自分のインスタンス
	int scorePoint;									//スコア
	int earnScorePoint;
	int height;
	int earnHeight;
	bool gameEndFlag;
};

