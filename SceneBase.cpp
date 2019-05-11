//-----------------------------------------------------------------------------//
//			リファクタリング：済					チェック：未
//-----------------------------------------------------------------------------//

#include "Common.h"
#include "SceneBase.h"
#include "TitleScene.h"
#include "PlayScene.h"
#include "TitleScene.h"
#include "ResultScene.h"

SceneBase::SceneBase()
{
}

SceneBase::~SceneBase()
{
}

SceneBase * SceneBase::InitScene()
{
	return new TitleScene();
}
