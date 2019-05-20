//-----------------------------------------------------------------------------//
//          リファクタリング：未                  チェック：未
//-----------------------------------------------------------------------------//
#pragma once

class Scenebase;
class InputManager;
class Sky;
class EffectCreater;
class TitleSceneSlime;
class FileManager;

/**
    @brief	タイトルシーンクラス
*/
class TitleScene : public SceneBase
{
public:
	TitleScene()				{};
	~TitleScene()      override	{};
    /**
        @brief	現在のシーンのアップデート処理をまとめて行う
        @return 次のフレームで実行するシーンのインスタンス
    */
    SceneBase* Update() override;
    /**
        @brief	現在のシーンの描画処理
    */
    void Draw()         override;
private:
    /**
        @brief	表示している画像のアニメーション処理
    */
	void GraphAnimation();
    /**
        @brief	デモムービーを流す処理
    */
	void PlayMovie();

	InputManager*		inputManager;						//入力管理クラスのポインタ
	FileManager*		fileManager;						//ファイル管理クラスのポインタ
	int					titleBackGroundGraph;				//タイトルの背景画像
	int					pushStartGraph;						//PushStartの画像
	int					pushStartOpacity;					//不透明度
	int					changingOpacityValue;
	int					demoPlayMovie;
	int					playcount;
	bool				playMovie;
	bool				SceneChangeFlag;
	bool				needPlayingMovie;
	static const int    OPACITY_MAX = 80;                    //タイトルでアニメーションさせる画像の不透明度の上限値（0~255）
	static const int    PLAY_MOVIE_UP_TO_TIME = 60 * 5;      //デモプレイムービーを流すまでの時間
};
