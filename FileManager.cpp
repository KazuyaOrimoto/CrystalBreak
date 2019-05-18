//-----------------------------------------------------------------------------//
//          リファクタリング：未                  チェック：未
//-----------------------------------------------------------------------------//

#include "Common.h"
#include "FileManager.h"

FileManager* FileManager::fileManager = NULL;

FileManager * FileManager::GetInstance()
{
	return fileManager;
}

void FileManager::CreateInstance()
{
	if (fileManager == NULL)
	{
		fileManager = new FileManager();
	}
}

void FileManager::DeleteInstance()
{
	if (fileManager != NULL)
	{
		delete(fileManager);
	}
}

void FileManager::LoadMap(int map[BLOCK_NUM_Y][BLOCK_NUM_X] ,const int stageNum)
{
	string num = std::to_string(stageNum);
	string fileName = stage + num + extension;
	ifstream stream(fileName);
	string line;
	const string delim = ",";
	int row = 0;
	int col;
	while (getline(stream,line))
	{
		col = 0;
		for (string::size_type spos, epos = 0;(spos = line.find_first_not_of(delim,epos)) != string::npos;)
		{
			string token = line.substr(spos,(epos = line.find_first_of(delim,spos))-spos);
			map[row][col++] = stoi(token);
		}
		++row;
	}
	stream.close();
}

FileManager::FileManager()
{
	titleImage = LoadGraph("Texture/Title.png");
	pushImage = LoadGraph("Texture/push.png");
	demoPlayMovie = LoadGraph("Movie/playmovie.mp4");
	tutorialGraph1 = LoadGraph("Texture/基本操作.png");
	tutorialGraph2 = LoadGraph("Texture/アイテム説明.png");
	nextGraph = LoadGraph("Texture/次へ.png");

	gameEndLeftGraph = LoadGraph("Texture/gameEndLeft.png");
	gameEndRightGraph = LoadGraph("Texture/gameEndRight.png");

	grayBlock = MV1LoadModel("model/grayBlockModel.mqo");
	brownBlock = MV1LoadModel("model/brownBlockModel.mqo");
	fireBlock = MV1LoadModel("model/fireBlock.mqo");
	sharpBlock = MV1LoadModel("model/SharpBlock.mqo");
	crumblyBlock = MV1LoadModel("model/CrumblyBlock.mqo");
	background = MV1LoadModel("model/backgroundModel.mqo");
	barrierItem = MV1LoadModel("model/BarrierItem.mqo");
	bombItem = MV1LoadModel("model/BombItem.mqo");

	playerModel = MV1LoadModel("model/RockSlime.mqo");
}

FileManager::~FileManager()
{
	DeleteGraph(titleImage);
	DeleteGraph(pushImage);
	DeleteGraph(demoPlayMovie);
	DeleteGraph(tutorialGraph1);
	DeleteGraph(tutorialGraph2);
	DeleteGraph(nextGraph);

	DeleteGraph(gameEndLeftGraph);
	DeleteGraph(gameEndRightGraph);

	MV1DeleteModel(grayBlock);
	MV1DeleteModel(brownBlock);
	MV1DeleteModel(fireBlock);
	MV1DeleteModel(background);
	MV1DeleteModel(sharpBlock);
	MV1DeleteModel(crumblyBlock);
	MV1DeleteModel(barrierItem);
	MV1DeleteModel(bombItem);
}

