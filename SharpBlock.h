#pragma once

//クラスの前方宣言
class BlockBase;
class EffectCreater;
class Player;

class SharpBlock : public BlockBase
{
public:
	SharpBlock(int sourceModelHandle, VECTOR startPos);
	~SharpBlock();
	//-----------------------------------------------------------------------------//
	//							パブリック関数
	//-----------------------------------------------------------------------------//
	void Update() override;
	void Attacked(Player & player) override;
	void OnBlock(Player& player) override;
};

