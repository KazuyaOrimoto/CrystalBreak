//-----------------------------------------------------------------------------//
//          リファクタリング：未                  チェック：未
//-----------------------------------------------------------------------------//

#include "Common.h"
#include "FireList.h"
#include "Stage.h"
#include "BlockBase.h"
#include "Fire.h"
#include "SoundManager.h"

//-----------------------------------------------------------------------------//
//								コンストラクタ
//-----------------------------------------------------------------------------//
FireList::FireList(Stage &stage)
{
	BlockMap blockMap;
	blockMap = stage.GetBlockMap();
	for (auto itr : blockMap)
	{
		if (itr.second->GetBlockName() == FIRE_CUBE)
		{
			fireBlockMap.insert(std::make_pair(itr.second->GetIndexPair(), itr.second));
		}
	}
	blockMap.clear();
	timeCount = 0;
	soundManager = SoundManager::GetInstance();
}

//-----------------------------------------------------------------------------//
//								デストラクタ
//-----------------------------------------------------------------------------//
FireList::~FireList()
{
	fireBlockMap.clear();
	for (auto itr : fireList)
	{
		delete(itr);
	}
	fireList.clear();
	fireBlockMap.clear();
	eraseList.clear();
}

//-----------------------------------------------------------------------------//
//								アップデート処理
//-----------------------------------------------------------------------------//
void FireList::Update(Stage &stage)
{
	timeCount++;
	if (timeCount > FIRE_CREATE_TIME)
	{
		CreateFireList(stage);
		timeCount = 0;
	}

	for (auto itr : fireBlockMap)
	{
		if (!itr.second->IsActive())
		{
			eraseList.push_back(itr.first);
		}
	}

	for (auto itr : eraseList)
	{
		fireBlockMap.erase(itr);
	}

	for (auto itr : fireList)
	{
		itr->Update();
	}

	std::vector<Fire*>::iterator itr = fireList.begin();
	while (itr != fireList.end())
	{
		if ((*itr)->IsActive() == false)
		{
			itr = fireList.erase(itr); 
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
void FireList::Draw()
{
	for (auto itr : fireList)
	{
		itr->Draw();
	}
}

FireVector FireList::GetFireList()
{
	return fireList;
}

//-----------------------------------------------------------------------------//
//								ファイアのリスト作成
//-----------------------------------------------------------------------------//
void FireList::CreateFireList(Stage &stage)
{
	for (auto itr : fireBlockMap)
	{
		if (needDrawModel(itr.second->GetPosition()))
		{
			if (stage.GetBlockName(itr.second->GetIndexPair().IndexPairRight()) == NO_BLOCK)
			{
				fireList.push_back(new Fire(itr.second->GetPosition(), RIGHT));
			}
			else if (stage.GetBlockName(itr.second->GetIndexPair().IndexPairLeft()) == NO_BLOCK)
			{
				fireList.push_back(new Fire(itr.second->GetPosition(), LEFT));
			}
		}
	}
}

bool FireList::needDrawModel(VECTOR position)
{
	VECTOR boxPos1 = VGet(position.x + MAGNIFICATION_RATE, position.y + MAGNIFICATION_RATE, position.z + MAGNIFICATION_RATE);
	VECTOR boxPos2 = VGet(position.x - MAGNIFICATION_RATE, position.y - MAGNIFICATION_RATE, position.z - MAGNIFICATION_RATE);
	bool needDraw = CheckCameraViewClip_Box(boxPos1, boxPos2);
	return !needDraw;
}