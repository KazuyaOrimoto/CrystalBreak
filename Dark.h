//-----------------------------------------------------------------------------//
//          リファクタリング：未                  チェック：未
//-----------------------------------------------------------------------------//

#pragma once

class EffectCreater;
class SoundManager;
class Player;

class Dark
{
public:
	Dark();
	~Dark();
	void Update(Player& player);
	void Draw();
	void Start();
private:
	int generationCount;
	int playerDieCount;
	bool swallowPlayer; //プレイヤーを飲み込むフラグ
	EffectCreater* effectCreater;
	SoundManager* soundManager;
	float beforePlayerHight;
	VECTOR darkPosition;
	bool start;
	int warningGraph;
	bool warning;
};

