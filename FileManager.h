#pragma once

class FileManager
{
public:
	//-----------------------------------------------------------------------------//
	//							パブリック関数
	//-----------------------------------------------------------------------------//
	static FileManager* GetInstance();
	static void CreateInstance();
	static void DeleteInstance();
	void LoadMap(int map[BLOCK_NUM_Y][BLOCK_NUM_X], const int stageNum);
	int GetTitleImage() { return titleImage; }
	int GetPushImage() { return pushImage; }
	int GetDemoPlayMovie() { return demoPlayMovie; }
	int GetTutorialGraph1() { return tutorialGraph1; }
	int GetTutorialGraph2() { return tutorialGraph2; }
	int GetNextGraph() { return nextGraph; }
	int GetGameEndLeftGraph() { return gameEndLeftGraph; }
	int GetGameEndRightGraph() { return gameEndRightGraph; }
	int GetGrayBlock() { return grayBlock; }
	int GetBrownBlock() { return brownBlock; }
	int GetFireBlock() { return fireBlock; }
	int GetSharpBlock() { return sharpBlock; }
	int GetCrumblyBlock() { return crumblyBlock; }
	int GetBackGround() { return background; }
	int GetBarrierItem() { return barrierItem; }
	int GetBombItem() { return bombItem; }
	int GetPlayerModel() { return playerModel; }
private:
	//-----------------------------------------------------------------------------//
	//							プライベート関数
	//-----------------------------------------------------------------------------//
	FileManager();
	~FileManager();
	//-----------------------------------------------------------------------------//
	//							プライベート変数
	//-----------------------------------------------------------------------------//
	static FileManager* fileManager;
	const string extension = ".csv";			//拡張子
	const string stage = "MapData/map";			//Mapのファイルが保存されている場所

	int titleImage;								//タイトルで表示する画像
	int pushImage;								//「push to start」の画像
	int demoPlayMovie;							//デモプレイの動画
	int tutorialGraph1;							//チュートリアル画像１枚目
	int tutorialGraph2;							//チュートリアル画像２枚目
	int nextGraph;								//「次へ」の画像
	int gameEndLeftGraph;						//ゲーム終了画像の左側
	int gameEndRightGraph;						//ゲーム終了画像の右側

	int grayBlock;								//グレーブロックのモデルハンドル
	int brownBlock;								//ブラウンブロックのモデルハンドル
	int fireBlock;								//ファイアブロックのモデルハンドル
	int sharpBlock;								//尖ったブロックのモデルハンドル
	int crumblyBlock;							//砕けやすいブロックのモデルハンドル
	int background;								//背景モデルのモデルハンドル
	int barrierItem;							//バリアアイテムのモデルハンドル
	int bombItem;								//爆弾アイテムのモデルハンドル

	int playerModel;							//プレイヤー用のモデルハンドル

};

