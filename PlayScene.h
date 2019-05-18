//-----------------------------------------------------------------------------//
//          リファクタリング：未                  チェック：未
//-----------------------------------------------------------------------------//

#pragma once

//クラスの前方宣言
class SceneBase;
class Camera;
class Stage;
class Player;
class EnemyList;
class ActionManager;
class Score;
class FireList;
class Collision;
class Sky;
class SoundManager;
class Dark;
class InputManager;
class FileManager;
class PlaySceneUI;
class Timer;

class PlayScene : public SceneBase
{
public:
	//-----------------------------------------------------------------------------//
	//							パブリック関数
	//-----------------------------------------------------------------------------//
	PlayScene();
	~PlayScene()		override;
	SceneBase* Update() override;
	void Draw()			override;
private:
	//-----------------------------------------------------------------------------//
	//							プライベート関数
	//-----------------------------------------------------------------------------//
	void IsGameEndFlag();										//ゲームエンドフラグが立っていたら
	bool CheckGameEndFlag();									//ゲーム終了フラグが立っているか調べる
	void UpdateProcess();										//アップデート処理をまとめて行う
	void DrawGameEndGraph();									//ゲーム終了画像の描画
	void NextStageCreate();										//次のステージの作成
	//-----------------------------------------------------------------------------//
	//							プライベート定数
	//-----------------------------------------------------------------------------//
	const int		mainScreenPosX = -200;						//ゲームのメイン画面を表示するPositionX
	const int		gameEndGraphPosY = 357;						//ゲーム終了の画像のPositionY
	const int		slideRange = 20;							//ゲーム終了画像を１フレームにスライドさせる幅
	const int		reciprocalNumber = 7;						//ゲーム終了フラグがたったとき、ゲームのアップデート処理を何フレームに１回やるか
	const int		timeUpToGameTermination = 5 * 60;			//ゲーム終了のフラグが立ってからシーンを変えるまでの時間
	//-----------------------------------------------------------------------------//
	//							プライベート変数
	//-----------------------------------------------------------------------------//
	bool			gameEndFlag;								//ゲーム終了フラグ
	int				gameEndCount;								//ゲーム終了フラグが立ってからのカウンター

	bool			gameEndSount;								//ゲーム終了時のサウンド
	int				gameEndGraphLeft;							//ゲーム終了画像の左側
	int				gameEndGraphRight;							//ゲーム終了画像の右側
	int				screenHandle;								//スクリーンハンドル

	Camera*			camera;
	Stage*			stage;
	Player*			player;
	EnemyList*		enemy;
	Score*			score;
	FireList*		fireList;
	Collision*		collision;
	Sky*			sky;
	Dark*			dark;
	PlaySceneUI*	playSceneUI;
	Timer*			timer;
	ActionManager*	actionManager;
	SoundManager*	soundManager;
	FileManager*	fileManager;
	InputManager*	inputManager;
};
