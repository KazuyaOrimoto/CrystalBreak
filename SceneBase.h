#pragma once
class SceneBase
{
public:
	//-----------------------------------------------------------------------------//
	//							パブリック関数
	//-----------------------------------------------------------------------------//
    SceneBase();
    virtual ~SceneBase();
	static SceneBase* InitScene();				//最初に表示するシーンを返す
    virtual SceneBase* Update() = 0;
    virtual void Draw() = 0;
};

