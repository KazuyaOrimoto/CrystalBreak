#pragma once

//クラスの前方宣言
class BlockBase;
class EffectCreater;

class BombItemBlock : public BlockBase
{
public:
	//-----------------------------------------------------------------------------//
	//							パブリック関数
	//-----------------------------------------------------------------------------//
	BombItemBlock(int sourceModelHandle, VECTOR startPos);
	~BombItemBlock();
	void Update() override;
	void Attacked(Player & player) override;
	void OnBlock(Player& player)override;
private:
	int playingHandle;
	int playingHandleBlock;
};

