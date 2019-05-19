//-----------------------------------------------------------------------------//
//          リファクタリング：未                  チェック：未
//-----------------------------------------------------------------------------//

#pragma once

//クラスの前方宣言
class BlockBase;
class BackGround;
class Player;
class FileManager;
class Camera;

const int MAP_SEGMENT_X = 9;
const int MAP_SEGMENT_Y = 10;
const int STAGE_MAX = 6;

class Stage
{
public:
	//-----------------------------------------------------------------------------//
	//							パブリック関数
	//-----------------------------------------------------------------------------//
	Stage();
	~Stage();
	void Update();
	void Draw();
	bool CheckOnGround(IndexPair nowIndexPair);
	bool CanMove(IndexPair pair, Direction findingDirection);
	void BreakBlock(IndexPair breakingIndexPair, Player & player);
	BlockName GetBlockName(IndexPair nowIndexPair);
	BlockMap GetBlockMap();
	BlockContainer GetBlockList();
	void OnGroundStage(IndexPair nowIndexPair, Player& player);
	void GetMapData(int mapData[BLOCK_NUM_Y][BLOCK_NUM_X]);
	bool needDrawModel(VECTOR position);
	bool NeedNextStageCreate();											//次のステージを作る必要性があるか
	void NextStageCreate();
	void LoadMap();
private:
	//-----------------------------------------------------------------------------//
	//							プライベート関数
	//-----------------------------------------------------------------------------//
	void CreateBlock(int createMapData[BLOCK_NUM_Y][BLOCK_NUM_X]);
	void CreateBackGround();
	//-----------------------------------------------------------------------------//
	//							プライベート変数
	//-----------------------------------------------------------------------------//
	BlockContainer blockList;
	BlockMap blockMap;
	std::vector<BackGround*> backGroundList;
	int map[BLOCK_NUM_Y][BLOCK_NUM_X];
	int grayBlock;
	int brownBlock;
	int fireBlock;
	int background;
	int sharpBlock;
	int crumblyBlock;
	int barrierItem;
	int bombItem;

	FileManager* fileManager;

	bool nextStageCreate;
	bool nextStageCreated;
	int beforeBlockNum = 0;
	const int backGroundNum = 50;
	
};
