//-----------------------------------------------------------------------------//
//          リファクタリング：未                  チェック：未
//-----------------------------------------------------------------------------//
#include "Common.h"
#include "BlockBase.h"
#include "Stage.h"
#include "UnbreakableBlock.h"
#include "BreakableBlock.h"
#include "FireBlock.h"
#include "BackGround.h"
#include "Player.h"
#include "CrumblyBlock.h"
#include "SharpBlock.h"
#include "FileManager.h"
#include "BarrierItemBlock.h"
#include "BombItemBlock.h"
#include "Camera.h"

//-----------------------------------------------------------------------------//
//								コンストラクタ
//-----------------------------------------------------------------------------//
Stage::Stage()
{
	fileManager = FileManager::GetInstance();
	LoadMap();

	//各モデルハンドルの取得
	grayBlock		= fileManager->GetGrayBlock();
	brownBlock		= fileManager->GetBrownBlock();
	fireBlock		= fileManager->GetFireBlock();
	sharpBlock		= fileManager->GetSharpBlock();
	crumblyBlock	= fileManager->GetCrumblyBlock();
	background		= fileManager->GetBackGround();
	barrierItem		= fileManager->GetBarrierItem();
	bombItem		= fileManager->GetBombItem();

	//一番上の段を壁で埋める
	for (int i = 0; i < BLOCK_NUM_X; i++)
	{
		map[0][i] = WALL;
	}

	CreateBlock(map);
	nextStageCreate = false;
	nextStageCreated = false;
	CreateBackGround();
}

//-----------------------------------------------------------------------------//
//								デストラクタ
//-----------------------------------------------------------------------------//
Stage::~Stage()
{
	for (auto itr : blockList)
	{
		delete(itr);
	}
	blockList.clear();
	for (auto itr : backGroundList)
	{
		delete(itr);
	}
	backGroundList.clear();

	blockMap.clear();
	MV1DeleteModel(grayBlock);
	MV1DeleteModel(brownBlock);
	MV1DeleteModel(fireBlock);
	MV1DeleteModel(background);
	MV1DeleteModel(sharpBlock);
	MV1DeleteModel(crumblyBlock);
	MV1DeleteModel(barrierItem);
	MV1DeleteModel(bombItem);
}

//-----------------------------------------------------------------------------//
//								アップデート処理
//-----------------------------------------------------------------------------//
void Stage::Update()
{
	for (auto itr : blockList)
	{
		//モデルを描画する必要があるか
		if (needDrawModel(itr->GetPosition()))
		{
			itr->Update();
		}
	}
	BlockVector::iterator itr = blockList.begin();
	while (itr != blockList.end())
	{
		if ((*itr)->IsActive() == false)
		{
			IndexPair deleteIndexPair = (*itr)->GetIndexPair();			//削除するブロックの要素位置
			map[deleteIndexPair.y][deleteIndexPair.x] = NO_BLOCK;		//要素位置のマップデータの書き換え
			blockMap.erase(deleteIndexPair);							//ブロックマップのリストから削除
			delete(*itr);												//インスタンスの削除
			itr = blockList.erase(itr);	
		}
		else
		{
			itr++;
		}
	}
}

//-----------------------------------------------------------------------------//
//								描画処理
//-----------------------------------------------------------------------------//
void Stage::Draw()
{
	for (auto itr : backGroundList)
	{
		itr->Draw();
	}
	for (auto itr : blockList)
	{
		if (needDrawModel(itr->GetPosition()))
		{
			itr->Draw();
		}
	}
}

//-----------------------------------------------------------------------------//
//								ブロックの名前を渡す
//-----------------------------------------------------------------------------//
BlockName Stage::GetBlockName(IndexPair fidingIndexPair)
{
	if (blockMap.count(fidingIndexPair) == 0)
	{
		return NO_BLOCK;
	}
	else
	{
		return blockMap.at(fidingIndexPair)->GetBlockName();
	}
	return NO_BLOCK;
}

//-----------------------------------------------------------------------------//
//								地面についているかの判定
//-----------------------------------------------------------------------------//
bool Stage::CheckOnGround(IndexPair nowIndexPair)
{
	if (nowIndexPair.y > 70)
	{
		nextStageCreate = true;
	}
	if (nextStageCreated)
	{
		if (10 < nowIndexPair.y && nowIndexPair.y < 12)
		{
			BlockVector::iterator itr = blockList.begin();
			for (itr; itr != blockList.begin() + beforeBlockNum; itr++)
			{
				delete(*itr);
			}
			blockList.erase(blockList.begin(), blockList.begin() + beforeBlockNum);
			nextStageCreated = false;
			beforeBlockNum = 0;
		}
	}
	IndexPair indexPairDown = nowIndexPair.IndexPairDown();
	if (blockMap.count(indexPairDown))
	{
		return true;
	}
	return false;
}

//-----------------------------------------------------------------------------//
//								動けるかどうか
//-----------------------------------------------------------------------------//
bool Stage::CanMove(IndexPair pair, Direction findingDirection)
{
	IndexPair sarchIndex;
	switch (findingDirection)
	{
	case RIGHT:
	{
		//渡された要素位置の横に何もなければ
		sarchIndex = pair.IndexPairRight();
		if (blockMap.count(sarchIndex) == 0)
		{
			//渡された要素位置の右下にブロックがあれば
			sarchIndex = pair.IndexPairRight().IndexPairDown();
			if (blockMap.count(sarchIndex))
			{
				return true;
			}
		}
		break;
	}
	case LEFT:
	{
		//渡された要素位置の横に何もなければ
		sarchIndex = pair.IndexPairLeft();
		if (blockMap.count(sarchIndex) == 0)
		{
			//渡された要素位置の左下にブロックがあれば
			sarchIndex = pair.IndexPairLeft().IndexPairDown();
			if (blockMap.count(sarchIndex))
			{
				return true;
			}
		}
		break;
	}
	default:
	{
		break;
	}
	}
	return false;
}

//-----------------------------------------------------------------------------//
//								ブロックを壊す処理
//-----------------------------------------------------------------------------//
void Stage::BreakBlock(IndexPair breakingIndexPair, Player & player)
{

	if (blockMap.count(breakingIndexPair))
	{
		blockMap.at(breakingIndexPair)->Attacked(player);
	}
	else
	{
		return;
	}
	map[breakingIndexPair.y][breakingIndexPair.x] = NO_BLOCK;
}

//-----------------------------------------------------------------------------//
//								ブロックのリストを渡す
//-----------------------------------------------------------------------------//
BlockMap Stage::GetBlockMap()
{
	return blockMap;
}

BlockVector Stage::GetBlockList()
{
	return blockList;
}

void Stage::OnGroundStage(IndexPair nowIndexPair, Player& player)
{
	IndexPair serchIndexPair = nowIndexPair.IndexPairDown();
	if (blockMap.count(serchIndexPair) == 0)
	{
		return;
	}
	blockMap.at(serchIndexPair)->OnBlock(player);
}

void Stage::GetMapData(int mapData[BLOCK_NUM_Y][BLOCK_NUM_X])
{
	for (int i = 0; i < BLOCK_NUM_X; i++)
	{
		for (int j = 0; j < BLOCK_NUM_Y; j++)
		{
			mapData[j][i] = map[j][i];
		}
	}
}

//-----------------------------------------------------------------------------//
//								ブロックを作成
//-----------------------------------------------------------------------------//
void Stage::CreateBlock(int createMapData[BLOCK_NUM_Y][BLOCK_NUM_X])
{
	IndexPair mapIndex;

	for (int i = 0; i < BLOCK_NUM_X; i++)
	{
		for (int j = 0; j < BLOCK_NUM_Y; j++)
		{
			mapIndex.x = i;
			mapIndex.y = j;
			switch (createMapData[j][i])
			{
			case NO_BLOCK:
			{
				//何もなし
				break;
			}
			case WALL:
			{
				//壊せないブロック
				blockList.push_back(new UnbreakableBlock(grayBlock, VGet(float(i * BLOCK_SIZE), float(-j * BLOCK_SIZE), 0.0f)));
				blockMap.insert(std::make_pair(mapIndex, blockList[blockList.size() - 1]));
				break;
			}
			case BLOCK:
			{
				//壊せるブロック
				blockList.push_back(new BreakableBlock(brownBlock, VGet(float(i * BLOCK_SIZE), float(-j * BLOCK_SIZE), 0.0f)));
				blockMap.insert(std::make_pair(mapIndex, blockList[blockList.size() - 1]));
				break;
			}
			case CRUMBLY_BLOCK:
			{
				//乗ると崩れるブロック
				blockList.push_back(new CrumblyBlock(crumblyBlock, VGet(float(i * BLOCK_SIZE), float(-j * BLOCK_SIZE), 0.0f)));
				blockMap.insert(std::make_pair(mapIndex, blockList[blockList.size() - 1]));
				break;
			}
			case FIRE_CUBE:
			{
				//炎を吐くブロック
				if (createMapData[j][i + 1] == NO_BLOCK)
				{
					blockList.push_back(new FireBlock(fireBlock, VGet(float(i * BLOCK_SIZE), float(-j * BLOCK_SIZE), 0.0f), RIGHT));
				}
				else
				{
					blockList.push_back(new FireBlock(fireBlock, VGet(float(i * BLOCK_SIZE), float(-j * BLOCK_SIZE), 0.0f), LEFT));
				}
				blockMap.insert(std::make_pair(mapIndex, blockList[blockList.size() - 1]));
				break;
			}
			case SHARP_BLOCK:
			{
				//乗ると死ぬブロック
				blockList.push_back(new SharpBlock(sharpBlock, VGet(float(i * BLOCK_SIZE), float(-j * BLOCK_SIZE), 0.0f)));
				blockMap.insert(std::make_pair(mapIndex, blockList[blockList.size() - 1]));
				break;
			}
			default:
			{
				break;
			}
			}
		}
	}
}

void Stage::CreateBackGround()
{
	for (int i = 1; i < backGroundNum; i++)
	{
		backGroundList.push_back(new BackGround(background, VGet(8.0 * MAGNIFICATION_RATE, -8.0f * MAGNIFICATION_RATE * i + NEXT_STAGE_CREATE_ADD_POSITION, 1.0f * MAGNIFICATION_RATE)));
	}
}

bool Stage::needDrawModel(VECTOR position)
{
	VECTOR boxPos1 = VGet(position.x + MAGNIFICATION_RATE, position.y + MAGNIFICATION_RATE, position.z + MAGNIFICATION_RATE);
	VECTOR boxPos2 = VGet(position.x - MAGNIFICATION_RATE, position.y - MAGNIFICATION_RATE, position.z - MAGNIFICATION_RATE);
	bool needDraw = CheckCameraViewClip_Box(boxPos1, boxPos2);
	return !needDraw;
}

//次のステージを作る必要性があるか
bool Stage::NeedNextStageCreate()
{
	if (nextStageCreate)
	{
		nextStageCreate = false;
		return true;
	}
	else
	{
		return false;
	}
}

void Stage::NextStageCreate()
{
	for (int i = 0; i < BLOCK_NUM_X; i++)
	{
		for (int j = 0; j < BLOCK_NUM_Y; j++)
		{
			map[j][i] = 0;
		}
	}
	for (auto itr : blockList)
	{
		itr->NextStageCreate();
	}
	LoadMap();
	blockMap.clear();
	nextStageCreated = true;
	beforeBlockNum = (int)blockList.size();
	CreateBlock(map);
	for (int i = 0; i < CREATE_ITEM_NUM; i++)
	{
		if (i == CREATE_ITEM_NUM -1)
		{
			break;
		}
		int ItemCreateNum = GetRand((int)blockMap.size() - 1);
		int accessNum = ItemCreateNum + beforeBlockNum - 3;

		if (blockList[accessNum]->GetBlockName() == BLOCK)
		{
			IndexPair indexData = blockList[accessNum]->GetIndexPair();
			blockMap.erase(indexData);
			blockList.erase(blockList.begin() + accessNum);
			int rand = GetRand(1);
			if (rand)
			{
				blockList.push_back(new BarrierItemBlock(barrierItem, VGet(float(indexData.x * BLOCK_SIZE), float(indexData.y * -BLOCK_SIZE), 0.0f)));
				blockMap.insert(std::make_pair(indexData, blockList[blockList.size() - 1]));;
			}
			else
			{
				blockList.push_back(new BombItemBlock(bombItem, VGet(float(indexData.x * BLOCK_SIZE), float(indexData.y * -BLOCK_SIZE), 0.0f)));
				blockMap.insert(std::make_pair(indexData, blockList[blockList.size() - 1]));
			}
		}
	}

}

void Stage::LoadMap()
{
	int mapData[MAP_SEGMENT_Y][MAP_SEGMENT_X] = {0};
	bool needMapLoad;
	bool startCreated = false;
	int stageNum;
	int mapX = 0, mapY = 0;
	for (int y = 0; y < BLOCK_NUM_Y; y++)
	{
		if (!startCreated)
		{
			//10マス目以上、終わりから10マス目以下のとき
			needMapLoad = (15 <= y && y <= 55);
			if (needMapLoad)
			{
				startCreated = true;
			}
		}
		for (int x = 0; x < BLOCK_NUM_X; x++)
		{
			if (needMapLoad)
			{
				stageNum = GetRand(STAGE_MAX - 1);
				fileManager->LoadMap(mapData, stageNum);
				mapX = 0;
				mapY = 0;
				needMapLoad = false;
			}
			if (x == 0 || x == MAP_SEGMENT_X - 1)
			{
				map[y][x] = WALL;
			}
			else if (12 <= y && y <= 14)
			{
				map[y][x] = BLOCK;
			}
			else if (y < MAP_SEGMENT_Y || BLOCK_NUM_Y - MAP_SEGMENT_Y < y)
			{
				map[y][x] = NO_BLOCK;
			}
			else
			{
				map[y][x] = mapData[mapY][mapX];
			}
			mapX++;
			if (mapX == MAP_SEGMENT_X)
			{
				mapX = 0;
				mapY++;
			}
			if (mapY == MAP_SEGMENT_Y)
			{
				if (20 <= y && y < 60)
				{
					needMapLoad = true;
				}
			}
		}

	}
}
