#pragma once

//クラスの前方宣言
class Scenebase;
class InputManager;
class Sky;
class EffectCreater;
class TitleSceneSlime;
class FileManager;

class TitleScene : public SceneBase
{
public:
	//-----------------------------------------------------------------------------//
	//							パブリック関数
	//-----------------------------------------------------------------------------//
    TitleScene();
    ~TitleScene()override;
    SceneBase* Update() override;
    void Draw() override;
private:
	//-----------------------------------------------------------------------------//
	//							プライベート関数
	//-----------------------------------------------------------------------------//
	void GraphAnimation();
	void PlayingMovie();
	//-----------------------------------------------------------------------------//
	//							プライベート変数
	//-----------------------------------------------------------------------------//
	InputManager* inputManager;
	FileManager* fileManager;
	int titleGraph;
	int pushGraph;
	int opacity;									//不透明度
	int changingOpacityValue;
	int demoPlayMovie;
	int playcount;
	bool playMovie;
	bool SceneChangeFlag;
	bool needPlayingMovie;
	const int OPACITY_MAX = 80;						//タイトルでアニメーションさせる画像の不透明度の上限値（0~255）
	const int playMovieUpToTime = 60 * 5;			//デモプレイムービーを流すまでの時間
};
