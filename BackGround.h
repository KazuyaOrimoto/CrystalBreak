﻿#pragma once
class BackGround
{
public:
	BackGround(int sorceModelHandle,VECTOR position);
	~BackGround();
	void Draw();
	void NextStageCreate();
private:
	int modelHandle;
	VECTOR position;
};

