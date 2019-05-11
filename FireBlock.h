#pragma once

//クラスの前方宣言
class BlockBase;

class FireBlock : public BlockBase
{
public:
	//-----------------------------------------------------------------------------//
	//							パブリック関数
	//-----------------------------------------------------------------------------//
	FireBlock(int sourceModelHandle, VECTOR startPos, Direction dir);
	~FireBlock();
	void Update() override;
	void Attacked(Player & player) override;
	void OnBlock(Player& player) override;
};

