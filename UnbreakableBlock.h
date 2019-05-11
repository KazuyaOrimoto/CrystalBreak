#pragma once

//クラスの前方宣言
class BlockBase;

class UnbreakableBlock : public BlockBase
{
public:
	//-----------------------------------------------------------------------------//
	//							パブリック関数
	//-----------------------------------------------------------------------------//
	UnbreakableBlock(int sourceModelHandle, VECTOR startPos);
	~UnbreakableBlock();
	void Update() override;
	void Attacked(Player & player) override;
	void OnBlock(Player& player) override;
};

