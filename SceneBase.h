//-----------------------------------------------------------------------------//
//			リファクタリング：済					チェック：未
//-----------------------------------------------------------------------------//

#pragma once

/**
	@brief	すべてのシーンの基底クラス
*/
class SceneBase
{
public:
    SceneBase();
    virtual ~SceneBase();
/**
	@brief	ゲーム起動後の最初のシーンを返す関数
	@return	シーンのインスタンス
*/
	static SceneBase* InitScene();
/**
	@brief	Updateの純粋仮想関数
	@return 次に実行するシーンのインスタンス
*/
    virtual SceneBase* Update() = 0;
/**
	@brief	Drawの純粋仮想関数
*/
    virtual void Draw() = 0;
};

