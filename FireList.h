#pragma once

//クラスの前方宣言
class Stage;
class Fire;
class SoundManager;

class FireList
{
public:
	//-----------------------------------------------------------------------------//
	//							パブリック関数
	//-----------------------------------------------------------------------------//
	FireList(Stage &stage);
	~FireList();
	void Update(Stage &stage);
	void Draw();
	FireVector GetFireList();
	bool needDrawModel(VECTOR position);
private:
	//-----------------------------------------------------------------------------//
	//							プライベート関数
	//-----------------------------------------------------------------------------//
	void CreateFireList(Stage &stage);							//ファイアを作る
	//-----------------------------------------------------------------------------//
	//							プライベート変数
	//-----------------------------------------------------------------------------//
											//ブロックリスト
	BlockMap fireBlockMap;										//ファイアブロックのMap
	FireVector fireList;										//ファイアのリスト
	std::vector<IndexPair> eraseList;							//Mapから消すブロックの要素位置のリスト
	SoundManager* soundManager;
	int timeCount;								
};

